//
// Created by llzz53 on 2026/1/27.
//

#ifndef LLZJ_ROBOT_PROJECT_VER001_SERVO_PAW_H
#define LLZJ_ROBOT_PROJECT_VER001_SERVO_PAW_H



typedef enum {
    GRIP=0,
    RELEASE
}paw_motion;

typedef enum {
    PAW_READY=0,
    PAW_RUNNING=1,
}paw_state;

void servo_paw_update();
void servo_paw_grip();
void servo_paw_release();



void servo_paw_set_state(paw_state);
paw_state servo_paw_get_state();

void servo_paw_init();
#endif //LLZJ_ROBOT_PROJECT_VER001_SERVO_PAW_H
