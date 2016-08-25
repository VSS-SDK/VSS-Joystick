/*
 * This file is part of the VSS-Joystick project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */


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