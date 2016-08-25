#ifndef _COMMONS_H_
#define _COMMONS_H_

#include "iostream"

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


#endif // _COMMONS_H_