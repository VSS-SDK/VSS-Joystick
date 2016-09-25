/*
 * This file is part of the VSS-Joystick project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */

#include "iostream"

#include "VSS-Interface/interface.h"
#include "dualshock3.h"

#include "thread"
#include "unistd.h"
#include "boost.h"

using namespace std;

class Core{
protected:
    Dualshock3 ds3;
    Interface interface;    // send data to VSS-Simulator
    string ip;

    thread *thread_ds3, *thread_com;

    int type; // SIMULATOR OR REAL
    JoyAxis left, right;
    vss_command::Global_Commands global_commands;

public:
    Core(){
        type = SIMULATOR;
    } 

    void init(int type, string ip){
        this->type = type;
        this->ip = "tcp://" + ip + ":5556";
        cout << this->ip << endl;

        thread_ds3 = new thread(bind(&Core::ds3_thread, this));
        thread_com = new thread(bind(&Core::com_thread, this));

        thread_ds3->join();
        thread_com->join();
    }

    void ds3_thread(){
        ds3.init();
    }

    void com_thread(){
        if(type == SIMULATOR){
            interface.createSendCommandsTeam1(&global_commands, ip);
            
            while(true){
                // flush and init the packet
                global_commands = vss_command::Global_Commands();
                global_commands.set_situation(0);
                global_commands.set_is_team_yellow(true);

                // get the input from dualshock3
                left = ds3.get_axis_left();
                right = ds3.get_axis_right();
                //ds3.show();

                // palce the controlable robot in the packet
                vss_command::Robot_Command *robot = global_commands.add_robot_commands();
                robot->set_id(0);

                robot->set_left_vel( (left.axis[Y] + left.axis[X]*0.2)*0.5 );
                robot->set_right_vel( (left.axis[Y] - left.axis[X]*0.2)*0.5 );
                
                // place the other robots in the packet
                for(int i = 1 ; i < 3 ; i++){
                    vss_command::Robot_Command *robot = global_commands.add_robot_commands();
                    robot->set_id(i);
                    robot->set_left_vel(0);
                    robot->set_right_vel(0);
                }

                interface.sendCommandTeam1();
                usleep(1000);
            }
        }else{
            cerr << "You must implement your own communication..." << endl;
        }
    }
};

bool argParse(int argc, char** argv, bool *real, string *ip);

int main(int argc, char** argv){
    string ip;
    bool real;
    if( argParse(argc, argv, &real, &ip) ){
        Core core;

        if(real)
            core.init(REAL, ip);
        else
            core.init(SIMULATOR, ip);
    }
}

bool argParse(int argc, char** argv, bool *real, string *ip){
    namespace bpo = boost::program_options;

    // Declare the supported options.
    bpo::options_description desc("Allowed options");
    desc.add_options()
        ("help,h", "(Optional) produce help message")
        ("ip_sender,i", bpo::value<std::string>()->default_value("localhost"), "(Optional) specify the ip of destiny.")
        ("real,r", "(Optional) Send command to real robots.");
    bpo::variables_map vm;
    bpo::store(bpo::parse_command_line(argc, argv, desc), vm);
    bpo::notify(vm);

    if (vm.count("help")){
        std::cout << desc << std::endl;
        return false;
    }

    if (vm.count("real")){
        *real = true;
    }

    *ip = vm["ip_sender"].as<string>();

    return true;
}