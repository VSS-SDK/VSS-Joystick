#include "iostream"
#include "unistd.h"
#include "math.h"
#include "thread"

#include "joystick/joystick.hh"
#include "VSS-Interface/interface.h"

using namespace std;

#define MAX_VAL 32767.0
enum { X = 0, Y = 1 };

struct JoyAxis{
    float axis[2];
    JoyAxis(){
        axis[X] = axis[Y] = 0;
    };
    JoyAxis(int x, int y){
        axis[X] = x;
        axis[Y] = y;
    };
    JoyAxis(JoyAxis *joy){
        axis[X] = joy->axis[X];
        axis[Y] = joy->axis[Y];
    };
    void show(){
        cout << "(" << axis[X] << ", " << axis[Y] << ")" << endl;
    }
};

class Dualshock3{
protected:
    Joystick joystick;
    JoyAxis left, right;
    int flush_left_x, flush_left_y;
    int flush_right_x, flush_right_y;
    thread *left_thread_x, *left_thread_y;
    thread *right_thread_x, *right_thread_y;
    thread *send_command;

public:
    Dualshock3(){
        flush_left_x = flush_left_y = flush_right_x = flush_right_y = 0;
    };

    void init(){
        if(joystick.isFound()){
            left_thread_x = new thread(bind(&Dualshock3::thread_left_x, this));
            left_thread_y = new thread(bind(&Dualshock3::thread_left_y, this));
            //right_thread_x = new thread(bind(&Dualshock3::thread_right_x, this));
            //right_thread_y = new thread(bind(&Dualshock3::thread_right_y, this));
            send_command = new thread(bind(&Dualshock3::thread_send, this));

            left_thread_x->join();
            left_thread_y->join();
            //right_thread_x->join();
            //right_thread_y->join();
            send_command->join();
        }
    }

    void thread_send(){
        while(true){
            //normalize();

            cout << "left" << endl;
            left.show();
            cout << "right" << endl;
            right.show();
            //cout << "flush" << flush_left_x << endl;
            usleep(10000);
        }
    }

    void thread_left_x(){
        while(true){
            JoystickEvent event;
            joystick.sample(&event);
            if (event.isAxis() && event.number == 0){
                left.axis[X] = event.value;
            }else{
                //left.axis[X] = 0;
                usleep(1000);
            }
        }
    }

    void thread_left_y(){
        while(true){
            JoystickEvent event;
            joystick.sample(&event);
            if (event.isAxis() && event.number == 1){
                left.axis[Y] = event.value;
            }else{
                //left.axis[Y] = 0;
                usleep(1000);
            }
        }
    }

    void thread_right_x(){
        while(true){
            JoystickEvent event;
            joystick.sample(&event);
            if (event.isAxis() && event.number == 2){
                right.axis[X] = event.value;
            }else{
                right.axis[X] = 0;
                usleep(1000);
            }
        }
    }

    void thread_right_y(){
        while(true){
            JoystickEvent event;
            if (joystick.sample(&event)){
                if (event.isAxis() && event.number == 3){
                    right.axis[Y] = event.value;
                }
            }else{
                usleep(1000);
            }
        }
    }

    void normalize(){
        left.axis[X] = left.axis[X]/MAX_VAL * 100.0;
        left.axis[Y] = left.axis[Y]/MAX_VAL * -100.0;

        right.axis[X] = right.axis[X]/MAX_VAL * 100.0;
        right.axis[Y] = right.axis[Y]/MAX_VAL * -100.0;
    }
};

int main(){
    Dualshock3 ds3;
    ds3.init();
}