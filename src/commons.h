/*
 * This file is part of the VSS-Joystick project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */

#ifndef _COMMONS_H_
#define _COMMONS_H_

#include "iostream"

using namespace std;

//! Valor máximo obtido por um analógico
#define MAX_VAL 32767.0

//! Definição de X e Y para facilitar a leitura
enum { X = 0, Y = 1 };

//! Definição para onde o comando o VSS-Joystick irá
enum { SIMULATOR = 0, REAL = 1 };

//! Essa struct passiva, contém os valores de um analógico
struct JoyAxis {
	//! Valores X e Y de 0 a 100
	float axis[2];
	//! Construtor DEFAULT
	JoyAxis(){
		axis[X] = axis[Y] = 0;
	};
	//! Construtor(x, y)
	JoyAxis( int x, int y ){
		axis[X] = x;
		axis[Y] = y;
	};
	//! Cosntrutor cópia
	JoyAxis( JoyAxis *joy ){
		axis[X] = joy->axis[X];
		axis[Y] = joy->axis[Y];
	};
	//! Método de debug no terminal
	void show(){
		cout << "(" << axis[X] << ", " << axis[Y] << ")" << endl;
	}
};

#endif // _COMMONS_H_
