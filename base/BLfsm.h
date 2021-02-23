#ifndef BLFSM_H_
#define BLFSM_H_
#include    "base/BLbase.h"

#ifdef __cplusplus
extern "C" {
#endif
typedef struct {
    int8_t evt; // event type, positive value: no param, engative value: with param
} BLfsmevt_t, *pBLfsmevt_t;
typedef const BLfsmevt_t *pcBLfsmevt_t;

typedef struct {
    BLfsmevt_t base;
    const void* param;
} BLfsmevtex_t, *pBLfsmevtex_t;
typedef const BLfsmevtex_t *pcBLfsmevtex_t;

struct BLfsm;

/*!
\brief FSM action (enter, do, exit) handler
\return EXIT_SUCCESS or EXIT_FAILURE
*/
typedef int (*BLfsm_ah_f)(struct BLfsm* fsm);
int BLfsm_ah_do_nothing(struct BLfsm* fsm);

typedef enum {
    BLfsm_result_ignore,
    BLfsm_result_no_transit,
    BLfsm_result_transit,
    BLfsm_result_error,
} BLfsm_result_t;
/*!
\brief FSM event handler
*/
typedef BLfsm_result_t (*BLfsm_eh_f)(struct BLfsm* fsm, pcBLfsmevt_t ev);
BLfsm_result_t BLfsm_eh_do_nothing(struct BLfsm* fsm, pcBLfsmevt_t ev);

typedef struct {
    BLfsm_ah_f ah_enter;
    BLfsm_ah_f ah_exit;
    BLfsm_eh_f eh;
} BLfsmstate_t, *pBLfsmstate_t;
typedef const BLfsmstate_t *pcBLfsmstate_t;

typedef struct BLfsm {
    pcBLfsmstate_t state;
    pcBLfsmevt_t latest_evt;
    void* context;
} BLfsm_t, *pBLfsm_t;
typedef const BLfsm_t *pcBLfsm_t;

/*!
\brief execute a state transition.
*/
int  BLfsm_execute(pBLfsm_t fsm, pcBLfsmevt_t ev);
#ifdef __cplusplus
}
#endif
#endif /* BLFSM_H_ */