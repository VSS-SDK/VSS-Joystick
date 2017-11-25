/*
 * This file is part of the VSS-Joystick project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */

#include "iostream"
#include "boost.h"
#include "core.h"

using namespace std;

//! Leitura dos parâmetros de entrada
bool argParse( int argc, char** argv, bool *real, string *ip );

int main( int argc, char** argv ){
	string ip;
	bool real;
	if( argParse( argc, argv, &real, &ip ) ) {
		Core core;

		if(real)
			core.init( REAL, ip );
		else
			core.init( SIMULATOR, ip );
	}
}

bool argParse( int argc, char** argv, bool *real, string *ip ){
	namespace bpo = boost::program_options;

	//! Define as opções de parâmetros
	bpo::options_description desc( "Allowed options" );
	desc.add_options()
	        ( "help,h", "(Optional) produce help message" )
	        ( "ip_sender,i", bpo::value<std::string>()->default_value( "localhost" ), "(Optional) specify the ip of destiny." )
	        ( "real,r", "(Optional) Send command to real robots." );
	bpo::variables_map vm;
	bpo::store( bpo::parse_command_line( argc, argv, desc ), vm );
	bpo::notify( vm );

	//! Imprime a lista de parâmetros e fecha o programa
	if (vm.count( "help" )) {
		std::cout << desc << std::endl;
		return false;
	}

	//! Define o destino dos comandos. VSS-Simulator ou robôs reais
	if (vm.count( "real" )) {
		*real = true;
	}

	//! Define o IP de destino do VSS-Simulator
	*ip = vm["ip_sender"].as<string>();

	return true;
}
