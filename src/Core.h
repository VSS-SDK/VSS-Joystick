/*
 * This file is part of the VSS-Joystick project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */

#ifndef _CORE_H_
#define _CORE_H_

#include <iostream>
#include <thread>
#include <unistd.h>
#include <functional>
#include "JoystickReader.h"
#include "Interfaces/ICommandSender.h"
#include "Domain/ExecutionConfig.h"

using namespace std;

class Core {
public:
    Core();
    void init(vss::ExecutionConfig);

protected:
    void joystickThreadWrapper();
    void communicationThreadWrapper();

    bool hasCustomAddress(vss::ExecutionConfig);
    void createCustomSocket();
    void runSimulation();
    void runReal();

    JoystickReader joystickReader;
    vss::ICommandSender *commandSender;

    thread *joystickThread;
    thread *communicationThread;

    vss::ExecutionConfig executionConfig;
    JoyAxis left;
};

#endif // _CORE_H_
