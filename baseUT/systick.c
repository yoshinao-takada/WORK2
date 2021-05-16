#include    "base/BLsystick.h"
#include    "base/BLbase.h"

int systick();


int systick()
{
    int err = EXIT_SUCCESS;
    do {
        BLsystick_samplecontext_t context = { 0, stdout };
        BLsystick_t st;
        BLsystick_acttime_setbyfloat(&st.new, 0.3f);
        st.systick_args = (void*)&context;
        st.systick_handler = BLsystick_samplecallback;
        if (EXIT_SUCCESS != (err = BLsystick_set(&st)))
        {
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        for (int i = 0; i < 4; i ++)
        {
            sleep(10);
            printf("%s, %d, main thread, i = %d\n", __FUNCTION__, __LINE__, i);
        }
    } while (0);
    return err;
}