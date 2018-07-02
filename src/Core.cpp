/*
 * This file is part of the VSS-Joystick project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */

#include <Communications/CommandSender.h>
#include "Core.h"

Core::Core(){
}

void Core::init(vss::ExecutionConfig executionConfig){
    this->executionConfig = executionConfig;

	joystickThread = new thread( bind( &Core::joystickThreadWrapper, this ));
	communicationThread = new thread( bind( &Core::communicationThreadWrapper, this ));

	joystickThread->join();
	communicationThread->join();
}

void Core::joystickThreadWrapper(){
	joystickReader.init();
}

void Core::communicationThreadWrapper(){
	if(executionConfig.environmentType == vss::EnvironmentType::Simulation)
        runSimulation();
	else
	    runReal();
}

void Core::runSimulation() {
    commandSender = new vss::CommandSender();
    commandSender->createSocket(vss::TeamType::Yellow);

    while(true) {
        vss::Command command;
        vss::WheelsCommand wheelsCommand;
        left = joystickReader.getAxisLeft();

        wheelsCommand.leftVel = static_cast<float>((left.axis[Y] + left.axis[X] * 0.2) * 0.5);
        wheelsCommand.rightVel = static_cast<float>((left.axis[Y] - left.axis[X] * 0.2) * 0.5);

        command.commands.push_back(wheelsCommand);

        commandSender->sendCommand(command);

        usleep( 1000 );
    }
}

void Core::runReal() {
    while(true) {
        left = joystickReader.getAxisLeft();

        //! your own transmission module here

        usleep( 33000 );
    }
}
