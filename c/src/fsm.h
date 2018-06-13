#ifndef DQLITE_FSM_H
#define DQLITE_FSM_H

#define DQLITE__FSM_NULL -1
#define DQLITE__FSM_STOP -1

/* Specific state in a FSM */
struct dqlite__fsm_state {
	int         id;   /* State ID */
	const char *name; /* State name */
};

/* Event firing a state transition in a FSM */
struct dqlite__fsm_event {
	int         id;   /* Event ID */
	const char *name; /* Event name */
};

/* Handler fired upon a state transition */
typedef int (*dqlite__fsm_handler)(void *arg);

/* State transition in a FSM transition after an event is fired */
struct dqlite__fsm_transition {
	int                 event_id;      /* Event triggering the transition */
	dqlite__fsm_handler handler;       /* Handler to invoke  */
	int                 next_state_id; /* ID of the next state (if the handler succeeds) */
};

/* A finite state machine transitioning between states upon events */
struct dqlite__fsm {
	/* read-only */
	struct dqlite__fsm_state       *states;       /* Array of valid states */
	struct dqlite__fsm_event       *events;       /* Array of valid events */
	struct dqlite__fsm_transition **transitions;  /* Map state IDs to valid transitions */

	/* private */
	int states_count;  /* Length of the states array */
	int events_count;  /* Length of the events array */
	int curr_state_id; /* ID of the current state of the FSM */
	int next_state_id; /* ID of the next state of the FSM */
};

/* FSM lifecycle */

void dqlite__fsm_init(
	struct dqlite__fsm *f,
	struct dqlite__fsm_state *states,
	struct dqlite__fsm_event *events,
	struct dqlite__fsm_transition **transitions
	);

void dqlite__fsm_close(struct dqlite__fsm *f);

/* Trigger a state transition in a FSM */
int dqlite__fsm_step(struct dqlite__fsm *f, int event_id, void *arg);

/* Return the name of the current state */
const char *dqlite__fsm_state(struct dqlite__fsm *f);

#endif /* DQLITE_FSM_H */