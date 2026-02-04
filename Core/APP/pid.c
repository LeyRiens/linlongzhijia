//
// Created by llzz53 on 2026/1/10.
//

#include "pid.h"
#include <math.h>

#include "motor_chassis.h"


/////////µÈ´ýÊµÎïµ÷ÊÔPID²ÎÊý/////////

#define KP 1.0f
#define KI 1.0f
#define KD 1.0f
#define PID_I_BAND 5.0f
#define PID_I_MAX 20.0f




float pid_error_last[4];
float pid_error_sum[4];


void pid_cal(void)
{
    float pid_error_current[4];
    float pid_pterm[4], pid_iterm[4], pid_dterm[4],pid_term[4];
    for (int i = 0; i < 4; i++)
    {
        pid_error_current[i] = motor_get_target_speed(i) - motor_get_current_speed(i);


        pid_pterm[i] = KP * pid_error_current[i];


        if (fabs(pid_iterm[i]) < PID_I_BAND)
        {
            pid_iterm[i] += KI * pid_error_current[i];
            if (fabs(pid_iterm[i]) > PID_I_MAX)
            {
                pid_iterm[i] = (pid_iterm[i] > 0) ? PID_I_MAX : -PID_I_MAX;
            }
        }
        else
        {
            pid_iterm[i] = 0.0f;
        }


        pid_dterm[i] = KD * (pid_error_current[i] - pid_error_last[i]);


        pid_term[i] = pid_pterm[i] + pid_iterm[i] + pid_dterm[i];


        pid_error_last[i] = pid_error_current[i];


        motor_final_output_set(（fabs）(uint16_t)pid_term[i], i);
    }
}
