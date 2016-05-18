#include <iostream> 
#include <string>

using namespace std;

template <typename T>
bool parse(string _input, T *result);

int main()
{
	char retry = 'y';

	while ((retry == 'y') || (retry == 'Y')) {

		__declspec(align(16)) float a[8] = { -1.0, -10.0, 323.555, 2.0, 1.0, 10.0, 999.5, -3.1255 };
		__declspec(align(16)) float b[8] = { -1.0, -1.125, 1.0, 5.5, 1.0, 1.0, 60.2, -4.0 };
		__declspec(align(16)) float c[8] = { -1.0, 1.5, 1.0, 10.5, 1.0, 1.0, 50.0, 1.0 };
		__declspec(align(16)) double d[8] = { -1.0, 1.05, 1.0, -1.252525, 1.0, 1.0, -40.3, 3.125 };
		__declspec(align(16)) double f[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };

		bool overflow = false;
		bool underflow = false;
		long status = 0;

		//(A+B)*C*D
		
		char choice;
		cout << "Do you want to use the default arrays? Y/n" << endl;
		cin >> choice;
		if ( (choice == 'n') || (choice == 'N') )  {
			string input;
			cout << "Input values for 'A' array:" << endl;
			cin.ignore();
			getline(cin, input);
			while (!parse(input, a)) {
				cout << "Make sure you entered valid values and try again." << endl;
				cout << "Input values for 'A' array:" << endl;
				getline(cin, input);
			}
			cout << "Input values for 'B' array:" << endl;
			getline(cin, input);
			while (!parse(input, b)) {
				cout << "Make sure you entered valid values and try again." << endl;
				cout << "Input values for 'B' array:" << endl;
				getline(cin, input);
			}
			cout << "Input values for 'C' array:" << endl;
			getline(cin, input);
			while (!parse(input, c)) {
				cout << "Make sure you entered valid values and try again." << endl;
				cout << "Input values for 'C' array:" << endl;
				getline(cin, input);
			}
			cout << "Input values for 'D' array:" << endl;
			getline(cin, input);
			while (!parse(input, d)) {
				cout << "Make sure you entered valid values and try again." << endl;
				cout << "Input values for 'D' array:" << endl;
				getline(cin, input);
			}
		}
		bool flag = false;
		for (int i = 0; i < 8; i++) {
			if (isinf(a[i]) || isnan(a[i]) || isinf(b[i]) || isnan(b[i]) ||
				isinf(c[i]) || isnan(c[i]) || isinf(d[i]) || isnan(d[i]))
				flag = true;
		}
		if (!flag) {
			__asm
			{
			xor ecx, ecx
			main_loop :
				movlps xmm0, a[TYPE a * ecx]		//xmm0 = a[ecx, ecx+1]
				cvtps2pd xmm0, xmm0					//xmm0 = double()
				movlps xmm1, b[TYPE b * ecx]		//xmm1 = b[ecx, ecx+1]
				cvtps2pd xmm1, xmm1					//xmm1 = double()
				addpd xmm0, xmm1					//xmm0 = a+b[ecx, ecx+1]
				movlps xmm1, c[TYPE c * ecx]		//xmm1 = c[ecx, ecx+1]
				cvtps2pd xmm1, xmm1					//xmm1 = double()
				mulpd xmm0, xmm1					//xmm0 = (a+b) * c [ecx, ecx + 1]
				movups xmm1, d[TYPE d * ecx]		//xmm1 = d[ecx, ecx+1]
				mulpd xmm0, xmm1					//xmm0 = (a+b)*c*d[ecx, ecx+1]
				movaps f[TYPE f * ecx], xmm0
				cmp ecx, 6
				jae finish
				add ecx, 2
				jmp main_loop
				finish :
			}
			bool flag = false;
			for (int i = 0; i < 8; i++) {
				if (isnan(f[i]) || isinf(f[i])) {
					cout << "Overflow or underflow detected!" << endl;
					flag = true;
				}
			}
			if (!flag) {
				cout << "The resut is:" << endl;
				for (int i = 0; i < 8; i++) {
					cout << f[i] << ' ';
				}
			}
		}
		if (flag)
			cout << "Overflow or underflow detected!" << endl;
		cout << endl;
		cout << "Do you want to retry? Y/n" << endl;
		cin.ignore();
		cin >> retry;
	}
	
	return 0;
}

template <typename T>
bool parse(string _input, T *result) {

	T j = 0;
	T s;
	T res;
	int dot_pos = 0;

	for (int i = 0; i < 8; i++) {

		res = 0;
		s = 1;
		while (_input[j] == ' ')
			j++;
		if (_input[j] == '-') {
			s = -1;
			j++;
		}
		if (((_input[j] < '0') || (_input[j] > '9')) && (_input[j] != '.')) {
			return false;
		}
		while ((_input[j] >= '0') && (_input[j] <= '9')) {
			res = res * 10 + _input[j] - '0';
			j++;
		}
		if (_input[j] == '.') {
			++j;
		}
		while ((_input[j] >= '0') && (_input[j] <= '9')) {
			res = res * 10 + (_input[j] - '0');
			++dot_pos;
			++j;
		}
		switch (sizeof(T))
		{
		case sizeof(float) :
			res /= powf(10, (float)dot_pos);
			break;
		case sizeof(double) :
			res /= pow(10.0, (double)dot_pos);
			break;
		}
		res *= s;
		if ((fpclassify(res) != FP_NORMAL) &&
			(fpclassify(res) != FP_ZERO)) {
			return false;
		}
		result[i] = (T)res;
	}
	if (j < _input.length())
		return false;
	return true;
}
