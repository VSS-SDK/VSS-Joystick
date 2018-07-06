/*
 * This file is part of the VSS-Joystick project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */

#include <Communications/CommandSender.h>
#include "Domain/Constants.h"
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

    if(hasCustomAddress(executionConfig))
        createCustomSocket();
    else
        commandSender->createSocket(executionConfig.teamType);

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

void Core::createCustomSocket() {
    if (executionConfig.teamType == vss::Yellow)
        commandSender->createSocket(executionConfig.cmdYellowSendAddr);
    else
        commandSender->createSocket(executionConfig.cmdBlueSendAddr);
}

void Core::runReal() {
    while(true) {
        left = joystickReader.getAxisLeft();

        std::cout << "Send commands to real robots" << std::endl;

        usleep( 500000 );
    }
}

bool Core::hasCustomAddress(vss::ExecutionConfig executionConfig) {
    if(executionConfig.cmdYellowSendAddr.getIp() != vss::DEFAULT_CMD_SEND_ADDR)
        return true;

    if(executionConfig.cmdBlueSendAddr.getIp() != vss::DEFAULT_CMD_SEND_ADDR)
        return true;

    if(executionConfig.cmdYellowSendAddr.getPort() != vss::DEFAULT_CMD_YELLOW_PORT)
        return true;

    if(executionConfig.cmdBlueSendAddr.getPort() != vss::DEFAULT_CMD_BLUE_PORT)
        return true;

    return false;
}
