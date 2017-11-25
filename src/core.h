/*
 * This file is part of the VSS-Joystick project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */

#ifndef _CORE_H_
#define _CORE_H_

#include "iostream"

#include "../VSS-Interface/interface.h"
#include "reader_control_joy.h"

#include "thread"
#include "unistd.h"

using namespace std;

//! Essa classe é responsável por tratar de obter os dados de um jostick e enviar os comandos para o VSS-Simulator e robôs reais
class Core {
protected:

	//! Interpretador de comandos de um joytick USB
	ReaderControlJoy rc_joy;
	//! Interface de comunicação com o VSS-Simulator
	Interface interface;
	//! Ip do VSS-Simulator
	string ip;

	//! Thread para obter os dados do joystick
	thread *thread_joy;
	//! Thread para enviar os dados para o VSS-Simualtor ou robôs reais
	thread *thread_com;

	//! Tipo define o destino da mensagem: SIMULATOR OR REAL
	int type;
	//! Valores obtidos na leitura do analógico esquerdo de um joystick
	JoyAxis left;
	//! Comandos para serem enviados ao VSS-Simulator
	vss_command::Global_Commands global_commands;

public:

	//! Construtor DEFAULT
	Core();

	//! Método responsável pela inicialização da comunicação e leitura do joystick
	void init( int type, string ip );
	//! Thread de leitura do joystick
	void joy_thread();
	//! Thread de comunicação com o VSS-Simulator ou Robôs reais
	void com_thread();
};

#endif // _CORE_H_
