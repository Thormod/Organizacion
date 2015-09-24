// OrganizacionPractica2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

//CONSTANT VARIABLES
const double grades_to_radians_constant = 0.0174532925;
/******************/

//BASIC OPERATIONS
void fadd() {
	//Variables declaration
	double first_operand, second_operand;
	//Variables initialization
	cout << "****** INGRESA PRIMER OPERANDO: ";
	cin >> first_operand;
	cout << "****** INGRESA SENGUNDO OPERANDO: ";
	cin >> second_operand;
	//ASM code
	_asm {
		movsd xmm0, [first_operand]
			addsd xmm0, [second_operand]
			movsd[first_operand], xmm0
	}
	cout << "****** RESULTADO: " << first_operand << endl;
}

void fsub() {
	//Variables declaration
	double first_operand, second_operand;
	//Variables initialization
	cout << "****** INGRESA PRIMER OPERANDO: ";
	cin >> first_operand;
	cout << "****** INGRESA SENGUNDO OPERANDO: ";
	cin >> second_operand;
	//ASM code
	_asm {
		movsd xmm0, [first_operand]
			subsd xmm0, [second_operand]
			movsd[first_operand], xmm0
	}
	cout << "****** RESULTADO: " << first_operand << endl;
}

void fmul() {
	//Variables declaration
	double first_operand, second_operand;
	//Variables initialization
	cout << "****** INGRESA PRIMER OPERANDO: ";
	cin >> first_operand;
	cout << "****** INGRESA SENGUNDO OPERANDO: ";
	cin >> second_operand;
	//ASM code
	_asm {
		movsd xmm0, [first_operand]
			mulsd xmm0, [second_operand]
			movsd[first_operand], xmm0
	}
	cout << "****** RESULTADO: " << first_operand << endl;
}

void fdiv() {
	//Variables declaration
	double first_operand, second_operand;
	//Variables initialization
	cout << "****** INGRESA PRIMER OPERANDO: ";
	cin >> first_operand;
	cout << "****** INGRESA SENGUNDO OPERANDO: ";
	cin >> second_operand;
	//ASM code
	_asm {
		movsd xmm0, [first_operand]
			divsd xmm0, [second_operand]
			movsd[first_operand], xmm0
	}
	cout << "****** RESULTADO: " << first_operand << endl;
}

double fsqrt_auxiliary(double operand) {
	double result = 0;

	//squirt
	__asm {
	}

	return result;
}

void fsqrt() {
	//Variables declaration
	double operand, proc, us;

	//Variables initialization
	cout << "****** INGRESA OPERANDO: ";
	cin >> operand;

	//ASM code (processor)
	__asm {
		fld[operand]
			fsqrt
			fstp[proc]
	}
	cout << "****** RESULTADO (coprocesador): " << proc << endl;

	//ASM code (our implementation)
	__asm {
		sub esp, 8
			movsd xmm0, [operand]
			movsd[esp], xmm0
			call fsqrt_auxiliary
			add esp, 8
			fstp[us]
	}
	cout << "****** RESULTADO (Series): " << us << endl;
}

double fpot_auxiliary(double base, int exponent) {
	double result = 1;

	//ASM code 
	__asm {
		//exponent++
		mov eax, [exponent]
			inc eax
			mov[exponent], eax

			//ECX = exponent
			mov ecx, [exponent]

			ciclo:
		loop mult
			jmp fin

			mult :
		movsd xmm0, [result]
			mulsd xmm0, [base]
			movsd[result], xmm0
			jmp  ciclo

			fin :
	}

	return result;
}

void fpot() {
	//Variables declaration
	double base, result;
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

int ffact_auxiliary(int base) {
	int result = 1, one = 1;
	__asm {
		// ECX = base
		mov ecx, [base]
		
		cmp [base], 0
		jne mult
		
		case_0 :
			mov eax, [one]
			mov[result], eax
			jmp endd

		mult:
			mov eax, [result]
			mul ecx
			mov[result], eax
			loop mult

		endd:

	}

	return result;
}

void ffact() {
	//Variables declaration
	int base, result;
	//Variables initialization
	cout << "****** INGRESA BASE (solo enteros positivos): ";
	cin >> base;
	//Call the auxiliary fuction
	result = ffact_auxiliary(base);
	cout << "****** RESULTADO: " << result << endl;
}

//TRIGONOMETRIC OPERATIONS

//SUM 0 to inf ( (-1^n /(2n+1)!) * x^(2n+1) )
double fsin_auxiliary(double radians) {
	//Variables
	double result = 0, sign = -1, num, x, dden;
	int iteration = 0, two = 2, den, var;

	//Taylor Series
	__asm {
	taylor:
		//(-1)^n
		push[iteration] //Push final argument (n = tolerance)
		sub esp, 8
		movsd xmm0, [sign]
		movsd[esp], xmm0 //Push first argument (-1)
		call fpot_auxiliary //Call pot
		add esp, 0Ch
		fstp[num] //num = -1^n

		//2n + 1
		mov eax, [iteration] //Move tolerance (n) to eax
		mul[two] //eax = eax * 2 -> eax = 2n
		inc eax //eax++
		mov[var], eax //var = 2n + 1

		//(2n + 1)!
		push[var] //push var
		call ffact_auxiliary //call factorial
		add esp, 4
		mov[den], eax //den = (2n + 1)!
		cvtsi2sd xmm0, [den]
		movsd[dden], xmm0

		//x^(2n+1)
		push[var] //Push final argument (2n+1)
		sub esp, 8
		movsd xmm0, [radians]
		movsd[esp], xmm0 //Push first argument (x = radians)
		call fpot_auxiliary //Call pot
		add esp, 0Ch
		fstp[x] //x = x^(2n+1)

		//(-1^n /(2n+1)!) * x^(2n+1)
		movsd xmm0, [num] //- 1 ^ n
		divsd xmm0, [dden] //-1^n /(2n+1)!
		mulsd xmm0, [x] //(-1^n /(2n+1)!) * x^(2n+1)
		addsd xmm0, [result]
		movsd[result], xmm0 //result += (-1^n /(2n+1)!) * x^(2n+1

		//Repeat until iteration < limit 
		inc[iteration]
		cmp[iteration], 9 //Change this value for chage the number of repetitions
		jne taylor
	}

	return result;
}

void fsin() {
	//Variables declaration
	double degrees, proc, us;
	//Variables initialization
	cout << "****** INGRESA ANGULO EN GRADOS: ";
	cin >> degrees;
	degrees *= grades_to_radians_constant;
	//ASM code (processor)
	_asm {
		fld[degrees] //Load the float variable
		fsin //Sin function
		fstp[proc] //Store the float variable
	}
	cout << "****** RESULTADO (coprocesador): " << proc << endl;
	//ASM code (our implementation)
	__asm {
		sub esp, 8
		movsd xmm0, [degrees]
		movsd[esp], xmm0
		call fsin_auxiliary
		add esp, 8
		fstp[us]
	}

	cout << "****** RESULTADO (Series): " << us << endl;
}

//SUM 0 to inf ( (-1^n /(2n)!) * x^(2n) )
double fcos_auxiliary(double radians) {
	//Variables
	/*
	* result -> result of the operation
	* sign -> Sign calculation of the Taylor serie
	* num -> Taylor serie numerator
	*/
	double result = 0, sign = -1, num, x, dden;
	int iteration = 0, two = 2, den, var;

	//Taylor Series
	__asm {
	taylor:
		//(-1)^n
		push[iteration] //Push final argument (n = tolerance)
		sub esp, 8
		movsd xmm0, [sign]
		movsd[esp], xmm0 //Push first argument (-1)
		call fpot_auxiliary //Call pot
		add esp, 0Ch
		fstp[num] //num = -1^n

		//2n
		mov eax, [iteration] //Move tolerance (n) to eax
		mul[two] //eax = eax * 2 -> eax = 2n
		mov[var], eax //var = 2n

		//(2n)!
		push[var] //push var
		call ffact_auxiliary //call factorial
		add esp, 4
		mov[den], eax //den = (2n)!
		cvtsi2sd xmm0, [den]
		movsd[dden], xmm0

		//x^(2n)
		push[var] //Push final argument (2n)
		sub esp, 8
		movsd xmm0, [radians]
		movsd[esp], xmm0 //Push first argument (x = radians)
		call fpot_auxiliary //Call pot
		add esp, 0Ch
		fstp[x] //x = x^(2n)

		//(-1^n /(2n)!) * x^(2n)
		movsd xmm0, [num] //- 1 ^ n
		divsd xmm0, [dden] //-1^n /(2n)!
		mulsd xmm0, [x] //(-1^n /(2n+1)!) * x^(2n)
		addsd xmm0, [result]
		movsd[result], xmm0 //result += (-1^n /(2n)!) * x^(2n)

		//Repeat until iteration < limit 
		inc[iteration]
		cmp[iteration], 9 //Change this value for chage the number of repetitions
		jne taylor
	}

	return result;
}

void fcos() {
	//Variables declaration
	double degrees, proc, us;
	//Variables initialization
	cout << "****** INGRESA ANGULO EN GRADOS: ";
	cin >> degrees;
	degrees *= grades_to_radians_constant;

	//ASM code
	_asm {
		fld[degrees] //Load the float variable
		fcos //Cos function
		fstp[proc] //Store the float variable
	}
	cout << "****** RESULTADO (Funcion coprocesador): " << proc << endl;
	//ASM code (our implementation)
	__asm {
		sub esp, 8
		movsd xmm0, [degrees]
		movsd[esp], xmm0
		call fcos_auxiliary
		add esp, 8
		fstp[us]
	}

	cout << "****** RESULTADO (Series): " << us << endl;
}

void ftan() {
	//Variables declaration
	double degrees, result;
	//Variables initialization
	cout << "****** INGRESA ANGULO EN GRADOS: ";
	cin >> degrees;
	degrees *= grades_to_radians_constant;
	//ASM code
	_asm {
		fld[degrees] //Load the float variable
		fsin //Sin function
		fld[degrees] //
		fcos
		fdivp st(1), st(0)
		fstp[result]
	}
	cout << "****** RESULTADO (Funcion coprocesador): " << result << endl;

	double sin, dsin, cos, dcos;

	_asm {
		//sin(degrees)
		sub esp, 8
		movsd xmm0, [degrees]
		movsd[esp], xmm0
		call fsin_auxiliary //Call sin
		add esp, 8
		fstp[sin]

		//cos(degrees)
		sub esp, 8
		movsd xmm0, [degrees]
		movsd[esp], xmm0
		call fcos_auxiliary //Call cos
		add esp, 8
		fstp[cos]
		
		//tan = sin(degrees)/cos(degrees)
		movsd xmm0, [sin] //sin(degrees)
		divsd xmm0, [cos] //sin(degrees)/cos(degrees)
		movsd[result], xmm0 //result = sin(degrees)/cos(degrees)
	}
	cout << "****** RESULTADO (Series): " << result << endl;
}



//LOGARITHMIC OPERATIONS
void flog2() {
	//Variables declaration
	double x, one, proc, us;

	//Variables initialization
	cout << "****** INGRESA EL ARGUMENTO: ";
	cin >> x;
	one = 1;

	//ASM code (processor)
	__asm {
		//log2(x)
		fld[one] //ST(1) = 1
		fld[x] //ST(0) = x
		fyl2x //ST(1) = (ST(1) * log2(ST(0))) -> ST(1) = 1 * log2(x)
		fstp[proc] //proc = ST(1)
	}
	cout << "****** RESULTADO (coprocesador): " << proc << endl;

	//ASM code (our implementation)
	__asm {

	}
	cout << "****** RESULTADO (Series): " << endl;
}

void flog10() {
	//Variables declaration
	double x, one, ten, var, proc, us;

	//Variables initialization
	cout << "****** INGRESA EL ARGUMENTO: ";
	cin >> x;
	one = 1;
	ten = 10;

	//ASM code (processor)
	__asm {
		//log2(10)
		fld[one] //ST(1) = 1
		fld[ten] //ST(0) = 10
		fyl2x //ST(1) = (ST(1) * log2(ST(0))) -> ST(1) = 1 * log2(10)
		fstp[var] //var = ST(1)

		//1/log2(10)
		movsd xmm0, [one]
		divsd xmm0, [var]
		movsd[var], xmm0 //var = 1/log2(10)

		//(1/log2(10)) * log2(x) -> log10(x)
		fld[var] //ST(1) = var -> ST(1) = 1/log2(10)
		fld[x] //ST(0) = x
		fyl2x //ST(1) = (ST(1) * log2(ST(0))) -> ST(1) = (1/log2(10)) * log2(x) -> ST(1) = log10(x)
		fstp[proc] //proc = ST(1)

	}
	cout << "****** RESULTADO (coprocesador): " << proc << endl;

	//ASM code (our implementation)
	__asm {

	}
	cout << "****** RESULTADO (Series): " << endl;
}

void printMenu() {
	cout<< "********************************************************" << endl 
		<< "****** CALCULATHOR ******" << endl
		<< "****** OPERACIONES BASICAS" << endl
		<< "****** 1. SUMA" << endl
		<< "****** 2. RESTA" << endl
		<< "****** 3. MULTIPLICACION" << endl
		<< "****** 4. DIVISION" << endl
		<< "****** OPERACIONES CIENTIFICAS" << endl
		<< "****** 5. SENO" << endl
		<< "****** 6. COSENO" << endl
		<< "****** 7. TANGENTE" << endl
		<< "****** 8. - RAIZ CUADRADA" << endl
		<< "****** 9. POTENCIA" << endl
		<< "****** 10. LOGARITMO EN BASE 2 'log2(x)'" << endl
		<< "****** 11. - LOGARITMO EN BASE 10 'log10(x)'" << endl
		<< "****** 12. - EULER" << endl
		<< "****** 13. FACTORIAL" << endl
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
		default:
			cout << "****** OPCION INVALIDA ******" << endl;
			break;
		}
	} while (choice);

	cout << "HASTA LA PROXIMA" << endl;
	return 0;
}