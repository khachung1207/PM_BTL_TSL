#ifndef PM_H_
#define PM_H_

#include "usbstk5515.h"

/* ------------------------------------------------------------------------ *
 * PM parameters
 * ------------------------------------------------------------------------ */
#define PM_SAMPLES_PER_SECOND   48000
#define PM_GAIN_IN_DB           5

/* Carrier frequency in Hz */
#define PM_CARRIER_FREQ         10000

/* Carrier amplitude scale
   Keep this modest to avoid clipping after phase modulation */
#define PM_CARRIER_AMPLITUDE    20000

/* Phase sensitivity coefficient
   Higher value -> stronger phase deviation
   Suggested test range: 4, 8, 12, 16 */
#define PM_KP                   8

/* Input normalization shift
   Input sample is Int16, roughly in range [-32768, 32767]
   We scale it down before converting to frequency deviation */
#define PM_MSG_SHIFT            8

/* Safety clamp for instantaneous frequency */
#define PM_FREQ_MIN             10
#define PM_FREQ_MAX             16000

/* ------------------------------------------------------------------------ *
 * Prototypes
 * ------------------------------------------------------------------------ */
void PM_init(void);
Int16 PM_process(Int16 msg_sample);

#endif /* PM_H_ */