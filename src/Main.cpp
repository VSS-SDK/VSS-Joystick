/*
 * This file is part of the VSS-Joystick project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */

#include "Core.h"
#include "Domain/ExecutionConfig.h"
#include "Interfaces/IStdinInterpreter.h"
#include "Interfaces/IFluentStdinInterpreterBuilder.h"
#include "Builders/FluentStdinInterpreterBuilder.h"
#include "Interpreters/StdinInterpreter.h"

vss::ExecutionConfig loadExecutionConfig(int argc, char** argv){
    auto fluentStdinInterpreterBuilder = new vss::FluentStdinInterpreterBuilder();

    fluentStdinInterpreterBuilder
            ->enableBlueCommandCommunicationPort()
            ->enableBlueCommandSenderAddress()
            ->enableYellowCommandCommunicationPort()
            ->enableYellowCommandSenderAddress()
            ->enableTeamType()
            ->enableEnvironmentType();

    auto stdinInterpreter = fluentStdinInterpreterBuilder->buildInterpreter();

    return stdinInterpreter->extractExecutionConfig(argc, argv);
}

int main( int argc, char** argv ){
    auto executionConfig = loadExecutionConfig(argc, argv);

    Core core;
    core.init(executionConfig);
}