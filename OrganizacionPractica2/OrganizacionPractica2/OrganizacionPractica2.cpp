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

float fpot_auxiliary(float base, int exponent) {
	float result = 1;

	//ASM code
	__asm {
		//exponent++
		mov eax, [exponent]
			inc eax
			mov[exponent], eax

		// ECX = exponent
		mov ecx, [exponent]

			ciclo:
		loop mult
			jmp fin

			mult :
		fld dword ptr[result]
			fmul[base]
			fst dword ptr[result]
			jmp  ciclo

			fin :
	}

	return result;
}

void fpot() {
	//Variables declaration
	float base, result;
	int exponent;
	//Variables initialization
	cout << "****** INGRESA BASE: ";
	cin >> base;
	cout << "****** INGRESA EXPONENTE (solo enteros positivos): ";
	cin >> exponent;
	//Call the auxiliary function
	result = fpot_auxiliary(base, exponent);
	cout << "****** RESULTADO: " << result << endl;
}

float ffact_auxiliary(float basef) {
	int base = (int)basef;
	int result = 1;
	__asm {
		// ECX = base
		mov ecx, [base]

			mult:
		mov eax, [result]
			mul ecx
			mov[result], eax
			loop mult
	}

	float resultf = (float)result;
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

//TRIGONOMETRIC OPERATIONS

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

//LOGARITHMIC OPERATIONS
void flog2() {
	//Variables declaration
	float x, one, proc, us;

	//Variables initialization
	cout << "****** INGRESA EL ARGUMENTO: ";
	cin >> x;
	one = 1;

	//ASM code (processor)
	__asm {
		//log2(x)
		fld dword ptr[one] //ST(1) = 1
			fld dword ptr [x] //ST(0) = x
			fyl2x //ST(1) = (ST(1) ? log2(ST(0))) -> ST(1) = 1 * log2(x)
			fst dword ptr[proc] //proc = ST(1)
	}
	cout << "****** RESULTADO (Funcion coprocesador): " << proc << endl;

	//ASM code (our implementation)
	__asm {

	}
	cout << "****** RESULTADO (Series): " << endl;
}

void flog10() {
	//Variables declaration
	float x, one, ten, var, proc, us;

	//Variables initialization
	cout << "****** INGRESA EL ARGUMENTO: ";
	cin >> x;
	one = 1;
	ten = 10;

	//ASM code (processor)
	__asm {
		//log2(10)
		fld dword ptr[one] //ST(1) = 1
			fld dword ptr[ten] //ST(0) = 10
			fyl2x //ST(1) = (ST(1) ? log2(ST(0))) -> ST(1) = 1 * log2(10)
			fst dword ptr[var] //var = ST(1)

		//1/log2(10)
			fld dword ptr[one] //ST(1) = 1
			fld dword ptr[var] //ST(0) = var -> ST(0) = log2(10)
			fdiv //ST(1) = ST(1)/ST(0) -> ST(1) = 1/log2(10)

		//(1/log2(10)) * log2(x) -> log10(x)
			fld dword ptr[x] //ST(0) = x
			fyl2x //ST(1) = (ST(1) ? log2(ST(0))) -> ST(1) = (1/log2(10)) * log2(x) -> ST(1) = log10(x)
			fst dword ptr[proc] //proc = ST(1)

	}
	cout << "****** RESULTADO (Funcion coprocesador): " << proc << endl;

	//ASM code (our implementation)
	__asm {

	}
	cout << "****** RESULTADO (Series): " << endl;
}

//CALLING FUNCTIONS
int fun(int a, int b) {
	__asm {
		mov eax, [a]
		add eax,[b]
		mov [a], eax
	}

	return a;
}

void call() {
	int a, b, result;
	cin >> a >> b;
	
	__asm {
			push [b]
			push [a]
			call fun
			add esp, 8
			mov dword ptr[result], eax
	}

	cout << result << endl;
}

void printMenu() {
	cout << "****** CALCULATHOR ******" << endl
		<< "****** OPERACIONES BASICAS" << endl
		<< "****** 1. SUMA" << endl
		<< "****** 2. RESTA" << endl
		<< "****** 3. MULTIPLICACION" << endl
		<< "****** 4. DIVISION" << endl
		<< "****** OPERACIONES CIENTIFICAS" << endl
		<< "****** 5. SENO" << endl
		<< "****** 6. COSENO" << endl
		<< "****** 7. TANGENTE" << endl
		<< "****** 8. RAIZ CUADRADA" << endl
		<< "****** 9. POTENCIA" << endl
		<< "****** 10. LOGARITMO EN BASE 2 'log2(x)'" << endl
		<< "****** 11. LOGARITMO EN BASE 10 'log10(x)'" << endl
		<< "****** 12. EULER" << endl
		<< "****** 13. FACTORIAL" << endl
		<< "****** 14. CALL" << endl
		<< "****** 0 SALIR" << endl
		<< "****** INGRESA ELECCION: ";
}

int main() {
	int choice;
	do {
		printMenu();
		cin >> choice;

		switch (choice) {
		case 0: //Exit
			break;
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
		case 10: //Log2(x)
			flog2();
			break;
		case 11: //Log10(x)
			flog10();
			break;
		case 12: //e^x
			break;
		case 13: //Fact
			ffact();
			break;
		case 14:
			call();
			break;
		default:
			cout << "****** OPCION INVALIDA ******" << endl;
			break;
		}
	} while (choice);
 
	cout << "HASTA LA PROXIMA" << endl;
	return 0;
}