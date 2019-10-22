#ifndef _HSM_H
#define _HSM_H

typedef struct Hsm Hsm;

typedef enum HsmHandlerReturn {
    HSM_HANDLER_RETURN_IGNORED,
    HSM_HANDLER_RETURN_CONSUMED,
    HSM_HANDLER_RETURN_DEFERRED
} HsmHandlerReturn;

typedef enum HsmEvent {
    HSM_EVENT_NONE,
    HSM_EVENT_ENTRY,
    HSM_EVENT_INIT,
    HSM_EVENT_EXIT,
    HSM_EVENT_FIRST_APPLICATION,
} HsmEvent;

typedef enum HsmEventResult {
    HSM_EVENT_RESULT_IGNORED = 0,
    HSM_EVENT_RESULT_CONSUMED,
    HSM_EVENT_RESULT_DEFERRED,
} HsmEventResult;

typedef enum HsmResult {
    HSM_RESULT_EVENT_CONSUMED,
    HSM_RESULT_DO_ERROR_FIRST = 100,
    HSM_RESULT_DO_ERROR_NULL_STATE_POINTER = HSM_RESULT_DO_ERROR_FIRST,
    HSM_RESULT_DO_ERROR_NULL_EVENT_POINTER,
    HSM_RESULT_PROCESS_TRANSIT_ERROR_FIRST = 200,
    HSM_RESULT_PROCESS_TRANSIT_ERROR_NULL_STATE = HSM_RESULT_PROCESS_TRANSIT_ERROR_FIRST,
    HSM_RESULT_PROCESS_TRANSIT_ERROR_NULL_TRANSIT,
} HsmResult;

typedef struct HsmTransit {
    Hsm *target;
} HsmTransit;

typedef HsmHandlerReturn (*HsmHandler)(Hsm *self, HsmEvent *event, HsmTransit *transit);

struct Hsm {
    Hsm *parent;
    HsmHandler handler;
    Hsm *active;
};

#endif // _HSM_H

