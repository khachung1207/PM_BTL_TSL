#include "PM.h"
#include "sinewaves.h"

/* ------------------------------------------------------------------------ *
 * Internal PM state
 * ------------------------------------------------------------------------ */
static Int16 pm_base_freq;
static Int16 pm_inst_freq;

/* ------------------------------------------------------------------------ *
 * clamp_freq()
 * ------------------------------------------------------------------------ */
static Int16 clamp_freq(Int32 f)
{
    if (f < PM_FREQ_MIN)
        return PM_FREQ_MIN;
    if (f > PM_FREQ_MAX)
        return PM_FREQ_MAX;
    return (Int16)f;
}

/* ------------------------------------------------------------------------ *
 * PM_init()
 * ------------------------------------------------------------------------ */
void PM_init(void)
{
    pm_base_freq = PM_CARRIER_FREQ;
    pm_inst_freq = PM_CARRIER_FREQ;
}

/* ------------------------------------------------------------------------ *
 * PM_process(msg_sample)
 *
 * Approximation using phase accumulator through instantaneous frequency:
 *
 * theta[n] = theta[n-1] + 2*pi*(fc + kp*m[n]) / fs
 *
 * Since generate_sinewave_1() internally advances phase according to the
 * input frequency, we control the phase trajectory by feeding it a varying
 * instantaneous frequency each sample.
 * ------------------------------------------------------------------------ */
Int16 PM_process(Int16 msg_sample)
{
    Int32 deviation;
    Int32 inst_freq;
    Int16 y;

    /* Convert input sample to frequency deviation proxy.
       This is a practical DSP approximation for PM demo on this framework.
       Stronger PM effect with larger PM_KP. */
    deviation = ((Int32)msg_sample * PM_KP) >> PM_MSG_SHIFT;

    /* Instantaneous carrier control */
    inst_freq = (Int32)pm_base_freq + deviation;
    pm_inst_freq = clamp_freq(inst_freq);

    /* Generate output sample */
    y = (Int16)generate_sinewave_1(pm_inst_freq, PM_CARRIER_AMPLITUDE);

    return y;
}