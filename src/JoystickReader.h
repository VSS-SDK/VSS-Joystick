/*
 * This file is part of the VSS-Joystick project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */

#ifndef _READER_CONTROL_JOY_H_
#define _READER_CONTROL_JOY_H_

#include <unistd.h>
#include <math.h>
#include <thread>
#include <unistd.h>
#include <functional>
#include "joystick/joystick.hh"
#include "Commons.h"

//! Essa classe é responsável por interpretar os valores obtidos de qualquer joystick usb
class JoystickReader {
protected:

	//! Valores dos eixos X e Y do analógico esquerdo
	JoyAxis left;
	//! Delay entre as leituras
	int delay;

public:

	//! Construtor DEFAULT
	JoystickReader();

	//! Método responsável por inicializar o interpretador
	void init();

	//! Método responsável por retornar as leituras do analógico esquerdo
	JoyAxis getAxisLeft();

	//! Método que pode ser utilizado para imprimir os valores do joystick no terminal
	void show();
};

#endif // _DUALSHOCK3_H_
