/*
 * This file is part of the VSS-Joystick project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */

#include "JoystickReader.h"

// verify your joystick number
JoystickReader::JoystickReader() {
	delay = 1000;
};

void JoystickReader::init(){
	Joystick joystick( "/dev/input/js0" );

	//! Caso um joystick esteja conectado.
	if(joystick.isFound()) {
		while(true) {
			usleep( delay );

			JoystickEvent event;
			if(joystick.sample( &event )) {

				//! Caso o evento enviado pelo joystick seja uma nova leitura do eixo X do analógico esquerdo
				if (event.isAxis() && event.number == 0) {
					left.axis[X] = event.value;

					//! Normaliza o valor para algo entre 0 e 200
					left.axis[X] = left.axis[X] / MAX_VAL * 200.0;
				}

				//! Leitura de evento caso seja do eixo Y no analogico esquerdo
				if (event.isAxis() && event.number == 1) {
					left.axis[Y] = event.value;

					//! Normaliza o valor para algo entre 0 e 200
					left.axis[Y] = left.axis[Y] / MAX_VAL * -200.0;
				}
			}
		}
	}
}

JoyAxis JoystickReader::getAxisLeft(){
	return left;
}

void JoystickReader::show(){
	cout << "left";
	left.show();
}
