/*
 * This file is part of the VSS-Joystick project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */


#ifndef _DUALSHOCK3_H_
#define _DUALSHOCK3_H_

#include "unistd.h"
#include "math.h"
#include "thread"

#include "commons.h"
#include "joystick/joystick.hh"

class Dualshock3{
protected:
    Joystick joystick;
    JoyAxis left, right;

    int delay;
    bool on_left_x, on_left_y;
    int count_left_x, count_left_y;
    int count_right_x, count_right_y;

    thread *left_thread_x, *left_thread_y;
    thread *right_thread_x, *right_thread_y;
    thread *send_command;

public:
    Dualshock3();

    void init();

    void thread_left_x();
    void thread_left_y();
    JoyAxis get_axis_left();

    void thread_right_x();
    void thread_right_y();
    JoyAxis get_axis_right();
    
    void show();
};

#endif // _DUALSHOCK3_H_