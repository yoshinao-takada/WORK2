#include    "base/BLfsm.h"
#include    <errno.h>

int  BLfsm_execute(pBLfsm_t fsm, pcBLfsmevt_t ev)
{
    int err = EXIT_SUCCESS;
    do {
        pcBLfsmstate_t prev_state = fsm->state;
        BLfsm_result_t result = fsm->state->eh(fsm, ev);
        if (result == BLfsm_result_transit)
        {
            prev_state->ah_exit(fsm);
            fsm->latest_evt = ev;
            fsm->state->ah_enter(fsm);
        }
        else
        {
            fsm->latest_evt = ev;
        }
    } while (0);
    return err;
}

int BLfsm_ah_do_nothing(struct BLfsm* fsm)
{
    return 0;
}

BLfsm_result_t BLfsm_eh_do_nothing(struct BLfsm* fsm, pcBLfsmevt_t ev)
{
    return BLfsm_result_ignore;
}
