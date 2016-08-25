#include "dualshock3.h"

Dualshock3::Dualshock3(){
    delay = 500;
    count_left_x = count_left_y = 0;
    count_right_x = count_right_y = 0;
};

void Dualshock3::init(){
    if(joystick.isFound()){
        left_thread_x = new thread(bind(&Dualshock3::thread_left_x, this));
        left_thread_y = new thread(bind(&Dualshock3::thread_left_y, this));
        right_thread_x = new thread(bind(&Dualshock3::thread_right_x, this));
        right_thread_y = new thread(bind(&Dualshock3::thread_right_y, this));

        left_thread_x->join();
        left_thread_y->join();
        right_thread_x->join();
        right_thread_y->join();
    }
}


void Dualshock3::thread_left_x(){
    while(true){
        JoystickEvent event;
        joystick.sample(&event);
        if (event.isAxis() && event.number == 0){
            left.axis[X] = event.value;
            count_left_x = 0;
            count_left_y = 0;
        }else{
            count_left_x++;

            if(count_left_x > 500 && fabs(left.axis[X]) < MAX_VAL/2.0){
                left.axis[X] = 0;
            }
        }

        // normalize value 0 to 100
        left.axis[X] = left.axis[X]/MAX_VAL * 100.0;

        usleep(delay);
    }
}

void Dualshock3::thread_left_y(){
    while(true){
        JoystickEvent event;
        joystick.sample(&event);
        if (event.isAxis() && event.number == 1){
            left.axis[Y] = event.value;
            count_left_x = 0;
            count_left_y = 0;
        }else{
            count_left_y++;
            
            if(count_left_y > 500 && fabs(left.axis[Y]) < MAX_VAL/2.0){
                left.axis[Y] = 0;
            }
        }

        // normalize value 0 to 100
        left.axis[Y] = left.axis[Y]/MAX_VAL * -100.0;

        usleep(delay);
    }
}

void Dualshock3::thread_right_x(){
    while(true){
        JoystickEvent event;
        joystick.sample(&event);
        if (event.isAxis() && event.number == 2){
            right.axis[X] = event.value;
            count_right_x = 0;
        }else{
            count_right_x++;

            if(count_right_x > 500 && fabs(right.axis[X]) < MAX_VAL/2.0){
                count_right_x = 0;
                right.axis[X] = 0;
            }
        }

        // normalize value 0 to 100
        right.axis[X] = right.axis[X]/MAX_VAL * 100.0;

        usleep(delay);
    }
}

void Dualshock3::thread_right_y(){
    while(true){
        JoystickEvent event;
        joystick.sample(&event);
        if (event.isAxis() && event.number == 3){
            right.axis[Y] = event.value;
            count_right_y = 0;
        }else{
            count_right_y++;
            
            if(count_right_y > 500 && fabs(right.axis[Y]) < MAX_VAL/2.0){
                count_right_y = 0;
                right.axis[Y] = 0;
            }
        }

        // normaliza value 0 to 100
        right.axis[Y] = right.axis[Y]/MAX_VAL * -100.0;

        usleep(delay);
    }
}

JoyAxis Dualshock3::get_axis_left(){
    return left;
}

JoyAxis Dualshock3::get_axis_right(){
    return right;
}

void Dualshock3::show(){
    cout << "left";
    left.show();

    cout << "right";
    right.show();
}
