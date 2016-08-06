#include "iostream"
#include "joystick/joystick.hh"
#include "unistd.h"

using namespace std;

int main(){
    Joystick joystick;

    if(!joystick.isFound()){
        cerr << "Joystick not found" << endl;
    }

    while (true){
        // Restrict rate
        usleep(1000);

        // Attempt to sample an event from the joystick
        JoystickEvent event;
        if (joystick.sample(&event))
        {
            if (event.isAxis() && event.number >= 0 && event.number <= 3)
            {
                printf("Axis %u is at position %d\n", event.number, event.value);
            }
        }
    }
}