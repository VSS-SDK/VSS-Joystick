/*
 * This file is part of the VSS-Joystick project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */

#ifndef _READER_CONTROL_JOY_H_
#define _READER_CONTROL_JOY_H_

#include "unistd.h"
#include "math.h"
#include "thread"

#include "commons.h"
#include "joystick/joystick.hh"

//! Essa classe é responsável por interpretar os valores obtidos de qualquer joystick usb
class ReaderControlJoy {
protected:

	//! Classe de acesso a um jostick
	Joystick joystick;
	//! Valores dos eixos X e Y do analógico esquerdo
	JoyAxis left;
	//! Delay entre as leituras
	int delay;

	//! Threads de leitura do eixo X e Y do analógico esquerdo
	thread *analog_left_thread;

public:

	//! Construtor DEFAULT
	ReaderControlJoy();

	//! Método responsável por inicializar o interpretador
	void init();

	//! Método reponsável por efetuar as leituras do analógico esquerdo
	void func_analog_left();

	//! Método responsável por retornar as leituras do analógico esquerdo
	JoyAxis get_axis_left();

	//! Método que pode ser utilizado para imprimir os valores do joystick no terminal
	void show();
};

#endif // _DUALSHOCK3_H_
