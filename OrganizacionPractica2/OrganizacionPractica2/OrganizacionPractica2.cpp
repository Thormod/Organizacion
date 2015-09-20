// OrganizacionPractica2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

//CONSTANT VARIABLES
const float grades_to_radians_constant = 0.0174532925f;
const float cero = 0;
const float one = 1;
/******************/

//BASIC OPERATIONS
void fadd() {
	//Variables declaration
	float first_operand, second_operand;
	//Variables initialization
	cout << "****** INGRESA PRIMER OPERANDO: ";
	cin >> first_operand;
	cout << "****** INGRESA SENGUNDO OPERANDO: ";
	cin >> second_operand;
	//ASM code
	_asm {
		fld dword ptr[first_operand]
		fld dword ptr[second_operand]
		fadd
		fst dword ptr[first_operand]
	}
	cout << "****** RESULTADO: " << first_operand << endl;
}

void fsub() {
	//Variables declaration
	float first_operand, second_operand;
	//Variables initialization
	cout << "****** INGRESA PRIMER OPERANDO: ";
	cin >> first_operand;
	cout << "****** INGRESA SENGUNDO OPERANDO: ";
	cin >> second_operand;
	//ASM code
	_asm {
		fld dword ptr[first_operand]
		fld dword ptr[second_operand]
		fsub
		fst dword ptr[first_operand]
	}
	cout << "****** RESULTADO: " << first_operand << endl;
}

void fmul() {
	//Variables declaration
	float first_operand, second_operand;
	//Variables initialization
	cout << "****** INGRESA PRIMER OPERANDO: ";
	cin >> first_operand;
	cout << "****** INGRESA SENGUNDO OPERANDO: ";
	cin >> second_operand;
	//ASM code
	_asm {
		fld dword ptr[first_operand]
		fld dword ptr[second_operand]
		fmul
		fst dword ptr[first_operand]
	}
	cout << "****** RESULTADO: " << first_operand << endl;
}

void fdiv() {
	//Variables declaration
	float first_operand, second_operand;
	//Variables initialization
	cout << "****** INGRESA PRIMER OPERANDO: ";
	cin >> first_operand;
	cout << "****** INGRESA SENGUNDO OPERANDO: ";
	cin >> second_operand;
	//ASM code
	_asm {
		fld dword ptr[first_operand]
		fld dword ptr[second_operand]
		fdiv
		fst dword ptr[first_operand]
	}
	cout << "****** RESULTADO: " << first_operand << endl;
}

void fcos() {
	//Variables declaration
	float degrees;
	//Variables initialization
	cout << "****** INGRESA ANGULO EN GRADOS: ";
	cin >> degrees;
	degrees *= grades_to_radians_constant;
	//ASM code
	_asm {
		fld dword ptr[degrees] //Load the float variable
		fcos //Cos function
		fst dword ptr[degrees] //Store the float variable
	}
	cout << "****** RESULTADO (Funcion coprocesador): " << degrees << endl;
}

void ftan() {
	//Variables declaration
	float degrees, result;
	//Variables initialization
	cout << "****** INGRESA ANGULO EN GRADOS: ";
	cin >> degrees;
	degrees *= grades_to_radians_constant;
	//ASM code
	_asm {
		fld dword ptr[degrees] //Load the float variable
		fsin //Sin function
		fld dword ptr[degrees] //
		fcos
		fdivp st(1), st(0)
		fst dword ptr[result]
	}
	cout << "****** RESULTADO (Funcion coprocesador): " << result << endl;
}

void fsqrt() {
	//Variables declaration
	float first_operand;
	//Variables initialization
	cout << "****** INGRESA OPERANDO: ";
	cin >> first_operand;
	//ASM code
	_asm {
		fld dword ptr[first_operand]
		fsqrt
		fst dword ptr[first_operand]
	}
	cout << "****** RESULTADO: " << first_operand << endl;
}

float fpot_auxiliary(float basef, float exponentf) {
	int base = (int) basef;
	int exponent = (int) exponentf;
	int result = base;

	//ASM code
	__asm {
		//comparation with 1
		cmp [exponent], 1
		je fin
		
		//exponent--
		mov eax, [exponent]
		dec eax
		mov[exponent], eax

		// ECX = exponent
		mov ecx, [exponent]
	
		mult:
		mov eax, [result]
		mul [base]
		mov [result], eax
		loop mult

		fin:
	}

	float resultf = (float) result;
	return resultf;
}

void fpot() {
	//Variables declaration
	float base, exponent, result;
	//Variables initialization
	cout << "****** INGRESA BASE: ";
	cin >> base;
	cout << "****** INGRESA EXPONENTE: ";
	cin >> exponent;
	//Call the auxiliary function
	result = fpot_auxiliary(base, exponent);
	cout << "****** RESULTADO: " << result << endl;
}

float ffact_auxiliary(float basef) {
	int base = (int) basef;
	int result = 1;
	__asm {
		// ECX = base
		mov ecx, [base]

		mult:
		mov eax, [result]
		mul ecx
		mov [result], eax
		loop mult
	}
	
	float resultf = (float) result;
	return resultf;
}

void ffact() {
	//Variables declaration
	float base, result;
	//Variables initialization
	cout << "****** INGRESA BASE: ";
	cin >> base;
	//Call the auxiliary fuction
	result = ffact_auxiliary(base);
	cout << "****** RESULTADO: " << result << endl;
}

//CIENTIFIC OPERATIONS

//SUM 0 to inf ( -1^n /(2n +1)! * x^2n+1 )
float fsin_auxiliary() {
	__asm {
		push 5
		call ffact_auxiliary
		
	}
	return 0;
}

void fsin() {
	//Variables declaration
	float degrees;
	//Variables initialization
	cout << "****** INGRESA ANGULO EN GRADOS: ";
	cin >> degrees;
	degrees *= grades_to_radians_constant;
	//ASM code
	_asm {
		fld dword ptr[degrees] //Load the float variable
			fsin //Sin function
			fst dword ptr[degrees] //Store the float variable
	}
	cout << "****** RESULTADO (Funcion coprocesador): " << degrees << endl;
}

int main()
{
	cout << "****** CALCULATHOR ******";
	cout << "\n ****** OPERACIONES BASICAS";
	cout << "\n ****** 1. SUMA";
	cout << "\n ****** 2. RESTA";
	cout << "\n ****** 3. MULTIPLICACION";
	cout << "\n ****** 4. DIVISION";
	cout << "\n ****** OPERACIONES CIENTIFICAS";
	cout << "\n ****** 5. SENO";
	cout << "\n ****** 6. COSENO";
	cout << "\n ****** 7. TANGENTE";
	cout << "\n ****** 8. RAIZ CUADRADA";
	cout << "\n ****** 9. POTENCIA";
	cout << "\n ****** 10. LOGARITMO NATURAL";
	cout << "\n ****** 11. LOGARITMO";
	cout << "\n ****** 12. EULER";
	cout << "\n ****** 13. FACTORIAL";
	cout << "\n ****** 14. aux";
	cout << "\n ****** INGRESA ELECCION: ";
	int choice = 0;
	cin >> choice;
	switch (choice) {
		case 1: //Add
			fadd();
			break;
		case 2: //Sub
			fsub();
			break;
		case 3: //Mul
			fmul();
			break;
		case 4: //Div
			fdiv();
			break;
		case 5: //Sin
			fsin();
			break;
		case 6: //Cos
			fcos();
			break;
		case 7: //Tan
			ftan();
			break;
		case 8: //Sqrt
			fsqrt();
			break;
		case 9: //Pot
			fpot();
			break;
		case 10: //Ln
			break;
		case 11: //Log
			break;
		case 12: //e
			break;
		case 13: //Fact
			ffact();
			break;
		case 14:
			fsin_auxiliary();
			break;
		default:
			cout << "****** OPCION INVALIDA ******";
			break;
	}
	system("pause");
	return 0;
}

