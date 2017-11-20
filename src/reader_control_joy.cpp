/*
 * This file is part of the VSS-Joystick project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */


#include "reader_control_joy.h"
#include "functional"

// verify your joystick number
ReaderControlJoy::ReaderControlJoy() {
    joystick = Joystick(0);
    delay = 500;
};

void ReaderControlJoy::init(){
    //! Caso um joystick esteja conectado.
    if(joystick.isFound()){
        // É criado duas threads para leitura dos valores do joystick
        analog_left_thread = new thread(bind(&ReaderControlJoy::func_analog_left, this));

        analog_left_thread->join();
    }
}

void ReaderControlJoy::func_analog_left(){
    //! Loop contendo a leitura do eixo X do analógico esquerdo
    while(true){

        JoystickEvent event;
        joystick.sample(&event);
        //! Caso o evento enviado pelo joystick seja uma nova leitura do eixo X do analógico esquerdo
        if (event.isAxis() && event.number == 0){
            //! Lê o valor obtido
            left.axis[X] = event.value;

            //! Normaliza o valor para algo entre 0 e 200
            left.axis[X] = left.axis[X]/MAX_VAL * 200.0;
        }

        //! Leitura de evento caso seja do eixo Y no analogico esquerdo
        if (event.isAxis() && event.number == 1){
             //! Lê o valor obtido
            left.axis[Y] = event.value;

            //! Normaliza o valor para algo entre 0 e 200
            left.axis[Y] = left.axis[Y]/MAX_VAL * -200.0;
        }

        usleep(delay);
    }
}

JoyAxis ReaderControlJoy::get_axis_left(){
    return left;
}

void ReaderControlJoy::show(){
    cout << "left";
    left.show();
}
