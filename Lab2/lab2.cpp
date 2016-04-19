#include <iostream>
#include <string>
#include <math.h>

using namespace std;

bool IsParsable(string str, float* res) {

	int index = 0;
	int sign = 1;
	bool point_found = false;

	if (str[0] == '-') {
		sign = -1;
		++index;
	}

	char chr;
	float mul = 0.1;
	while (index < str.length()) {
		chr = str[index];
		if (chr >= '0' && chr <= '9') {
			if (point_found) {
				*res += (chr - 48) * mul;
				mul /= 10;
			}
			else {
				*res = *res * 10 + (chr - 48);
			}
		}
		else if (chr == '.') {
			if (str[index - 1] >= '0' && str[index - 1] <= '9') {
				if (!point_found)
					point_found = true;
				else
					return false;
			}
			else
				return false;
		}
		else {
			return false;
		}
		++index;
	}

	*res *= sign;

	return true;

}

void the_mainest() {

	string str;
	float a = 0, b = 0, h = 0, e = 0, n = 0;
	float S = 0, Y = 0;
	cout << "Enter the value for -2.8 < 'a' < 2.8: " << endl;
	cin >> str;
	while ((IsParsable(str, &a) != true)) {

		cout << "Invalid argument, make sure you entered a float and try again" << endl;
		cout << "Enter the value for 'a': " << endl;
		str = "";
		cin >> str;

	}
	//if (a == 0){
	//	cout << "Zero value" << endl;
	//	system("pause");
	//	return 1;
	//}
	//cout << a;
	str = "";
	cout << "Enter the value for -2.8 < 'b' < 2.8: " << endl;
	cin >> str;
	while (!IsParsable(str, &b)) {

		cout << "Invalid argument, make sure you entered a float and try again" << endl;
		cout << "Enter the value for 'b': " << endl;
		str = "";
		cin >> str;

	}
	//cout << b;
	str = "";
	cout << "Enter the value for 'h': " << endl;
	cin >> str;
	while (!IsParsable(str, &h)) {

		cout << "Invalid argument, make sure you entered a float and try again" << endl;
		cout << "Enter the value for 'c': " << endl;
		str = "";
		cin >> str;
	}
	//cout << h;
	str = "";
	cout << "Enter the value for 'e' <= 0.001: " << endl;
	cin >> str;
	while (!IsParsable(str, &e)) {

		cout << "Invalid argument, make sure you entered a float and try again" << endl;
		cout << "Enter the value for 'e': " << endl;
		str = "";
		cin >> str;
	}
	//cout << e;

	while (e < 0.0009)
	{
		cout << "Epsilon out of range" << endl;
		str = "";
		cout << "Enter the value for 'e' <= 0.001: " << endl;
		cin >> str;
		while (!IsParsable(str, &e)) {
			cout << "Invalid argument, make sure you entered a float and try again" << endl;
			cout << "Enter the value for 'e': " << endl;
			str = "";
			cin >> str;
		}
	}

	float two = 2;
	float k = 0;
	float temp = 0;
	float cycle_sum = 0;
	float null = 0;

	float x = a;
	int counter = 0;
	while (x <= b) {
		
		while ((x <= -2.8) || (x >= 2.8)) {
			if (x >= b)
				break;
			//cout << "x = " << x << " - out of range" << endl;
			x += h;
			counter++;
		}

		
		if (x >= b)
			break;

		if (x == 0) {
			Y = 1;
			S = 0;
			n = 0;
			cout << "x = " << x << ":" << endl;
			cout << "	Y(x) = " << Y << "	S(x) = " << S << " n = " << n << endl;
			x += h;
		}

		__asm {
			finit
			//Âû÷èñëÿåì Y(x)
			fld two					//st(0) = 2
			fld x					//st(0) = x, st(1) = 2
			fabs
			fyl2x					//st(0) = 2log2x
			fld st					//st(0) = 2log2x, st(1) = 2log2x
			frndint					//st(0) = round(2log2x), st(1) = 2log2x
			fsub st(1), st			//st(0) = öåëàÿ, st(1) = äðîáíàÿ
			fxch					//st(0) = äðîáíàÿ, st(1) = öåëàÿ
			F2XM1					//st(0) = 2^äðîáíàÿ - 1, st(1) = öåëàÿ
			fld1					
			faddp st(1), st			//st(0) = 2^äðîáíàÿ, st(1) = öåëàÿ
			fscale					//st(0) = x^2
			fld st					//st(0) = x^2, st(1) = x^2
			fld two					//st(0) = 2, st(1) = x^2, st(2) = x^2
			fmulp st(1), st			//st(0) = 2*x^2, st(1) = x^2
			fld1
			faddp st(1), st			//st(0) = 1+2*x^2, st(1) = x^2
			fldl2e					//st(0) = log2e, st(1) = 1+2*x^2, st(2) = x^2
			fxch
			fxch st(2)				//st(0) = x^2, st(1) = log2e, st(2) = 1+2*x^2
			fmulp st(1), st			//st(0) = x^2*log2e, st(1) = 1+2*x^2
			fld st					//st(0) = x^2*log2e, st(1) = x^2*log2e, st(2) = 1+2*x^2
			frndint
			fsub st(1), st			//st(0) = öåëàÿ, st(1) = äðîáíàÿ, st(2) = 1+2*x^2
			fxch
			F2XM1					//st(0) = 2^äðîáíàÿ - 1, st(1) = öåëàÿ, st(2) = 1+2*x^2
			fld1
			faddp st(1), st			//st(0) = 2^äðîáíàÿ, st(1) = öåëàÿ, st(2) = 1+2*x^2
			fscale					//st(0) = e^(x^2), st(1) = 0, st(2) = 1+2*x^2
			fxch
			fxch st(2)				//st(0) = 1+2*x^2, st(2) = e^(x^2)
			fmulp st(1), st			//st(0) = Y
			fstp Y

			//Âû÷èñëÿåì S(x) è n
			finit
			fld cycle_sum			//st(0) = 0
			fld k					//st(0) = k, st(1) = 0
			fld st					//st(0) = k, st(1) = k, st(2) = 0
			fld st					//st(0) = k, st(1) = k, st(2) = k, st(3) = 0
			main_loop:
				//fst n
				fld two				//st(0) = 2, st(1) = k, st(2) = k, st(3) = k, st(4) = 0
				//fstp n
				//fstp S
				fmulp st(1), st		//st(0) = 2k, st(1) = k, st(2) = k, st(3) = 0
				fld1				//st(0) = 1, st(1) = 2k, st(2) = k, st(3) = k, st(4) = 0
				faddp st(1), st		//st(0) = 2k + 1, st(1) = k, st(2) = k, st(3) = 0
				fxch				//st(0) = k, st(1) = 2k + 1, st(2) = k, st(3) = 0
				//Factorial
				factorial:
					fldz
					fcom st(1)
					fstsw ax
					sahf
					je exit_with_one
					fstp temp
					fld1
					fcom st(1)
					fstsw ax
					sahf
					je exit_with_one
					fstp temp
					fld1
					fxch
					fld1
					cycle:
						fxch
						fmul st(2), st
						fxch
						fsub st(1), st
						fcom st(1)
						fstsw ax
						sahf
						jne cycle
					fstp temp
					fstp temp
					jmp cont
					exit_with_one:
						fstp temp
						fstp temp
						fld1
				cont:
				fdiv st(1), st		
				fstp temp			//st(0) = (2k + 1)/k!, st(1) = k, st(2) = 0
				fxch				//st(0) = k, st(1) = (2k + 1)/k!, st(2) = 0
				fld st				//st(0) = k, st(1) = k, st(2) = (2k + 1)/k!, st(3) = 0
				fld two
				fmulp st(1), st		//st(0) = 2k, st(1) = k, st(2) = (2k + 1)/k!, st(3) = 0
				fld x				//st(0) = x, st(1) = 2k, st(2) = k, st(3) = (2k + 1)/k!, st(4) = 0
				fabs
				fyl2x				//st(0) = 2klog2x ...
				fld st
				frndint				//st(0) = round(2klog2x), st(1) = 2klog2x, ...
				fsub st(1), st		//st(0) = öåëàÿ, st(1) = äðîáíàÿ, ...
				fxch				//st(0) = äðîáíàÿ, st(1) = öåëàÿ, ...
				F2XM1				//st(0) = 2^äðîáíàÿ - 1, st(1) = öåëàÿ, ...
				fld1					
				faddp st(1), st		//st(0) = 2^äðîáíàÿ, st(1) = öåëàÿ, ...
				fscale				//st(0) = x^2k, st(1) = k, st(2) = (2k + 1)/k!, st(3) = 0
				fxch
				fstp temp
				fxch
				fxch st(2)
				fmulp st(1), st		//st(0) = (2k + 1)/k! * x^2k, st(1) = k, st(2) = 0
				fadd st(2), st		
				fstp temp			//st(0) = k, st(1) = sum
				fxch
				fst n
				fxch
				fld1
				faddp st(1), st		//st(0) = k + 1, st(1) = sum
				fld Y				//st(0) = Y, st(1) = k + 1, st(2) = sum
				fsub st, st(2)
				fabs				//st(0) = |Y - S|, st(1) = k + 1, st(2) = sum
				fld e				//st(0) = e, st(1) = |Y - S|, st(2) = k + 1, st(3) = sum
				fcom st(1)
				fstsw ax
				sahf
				ja quit_main_loop
				fstp temp
				fstp temp
				fld st
				fld st
				jmp main_loop
			quit_main_loop:
			fstp temp
			fstp temp
			fstp n
			fstp S
		}
		cout << "x = " << x << ":" << endl;
		cout << "	Y(x) = " << Y << "	S(x) = " << S << "	n = " << n << endl;
		x += h;
	}
	cout << endl;
	if (counter != 0)
		cout << "Some values ('a' or 'b') were out of range" << endl;
	cout << endl;
}

int main() {
	
	char choice;
	the_mainest();
	cout << "Do you want to try again? Y/n" << endl;
	cin >> choice;
	while (choice == 'Y' || choice == 'y'){
		the_mainest();
		cout << "Do you want to try again? Y/n" << endl;
		cin >> choice;
	}
}
