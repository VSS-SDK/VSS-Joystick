/*
 * This file is part of the VSS-Joystick project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */

#include "Core.h"

Core::Core(){
	//! Simulador é definido como destino DEFAULT
	type = SIMULATOR;
}

void Core::init( int type, string ip ){
	this->type = type;
	//! É recebido o IP da maquina onde o VSS-Simulator está rodando, por padrão esse valor é localhost ou 127.0.0.1
	this->ip = "tcp://" + ip + ":5556";
	//cout << this->ip << endl;

	joystickThread = new thread( bind( &Core::joystickThreadWrapper, this ));
	communicationThread = new thread( bind( &Core::communicationThreadWrapper, this ));

	joystickThread->join();
	communicationThread->join();
}

void Core::joystickThreadWrapper(){
	joystickReader.init();
}

void Core::communicationThreadWrapper(){
	JoyAxis left;

	//! Caso o destino seja o VSS-Simulator o trecho de código já está bem definido
	if(type == SIMULATOR) {
		//! A interface de comunicação com o VSS-Simulator é criada
		interface.createSendCommandsTeam1( &global_commands, ip );

		//! Loop infinito que envia os dados
		while(true) {
			//! O pacote é limpo
			global_commands = vss_command::Global_Commands();
			global_commands.set_is_team_yellow( true );

			//! É pego os valores do joystick
			left = joystickReader.getAxisLeft();

			//! É adicionado um comando de robô ao pacote
			vss_command::Robot_Command *robot = global_commands.add_robot_commands();
			robot->set_id( 0 );

			//! É definido a velocidade da roda esquerda do robô com base dos valores do analógico
			robot->set_left_vel( (left.axis[Y] + left.axis[X] * 0.2) * 0.5 );
			//! É definido a velocidade da roda direita do robô com base dos valores do analógico
			robot->set_right_vel( (left.axis[Y] - left.axis[X] * 0.2) * 0.5 );

			// É adicionado outros robôs ao pacote
			for(int i = 1; i < 3; i++) {
				vss_command::Robot_Command *robot = global_commands.add_robot_commands();
				robot->set_id( i );
				robot->set_left_vel( 0 );
				robot->set_right_vel( 0 );
			}

			//! O comando é enviado
			interface.sendCommandTeam1();
			usleep( 1000 );
		}
	}else{

		while(true) {
			left = joystickReader.getAxisLeft();
			// left.show();
			//! cout << left[X] << " " << left[Y] << end;

			//! your own transmission module here

			usleep( 33000 );
		}
	}
}
