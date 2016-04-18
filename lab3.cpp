#include <string>
#include <iostream>
#include <stdint.h>

using namespace std;

template <typename T>
bool parse(string _input, T *result);

int main() {

	__int8 a[8];
	__int8 b[8];
	__int8 c[8];
	__int16 d[8];

	string input;
	int choice = 1;
	//while (choice == 1) {
		cout << "Input values for 'A' array:" << endl;
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
		for (int i = 0; i < 8; i++)
			cout << a[i] << ' ';
		for (int i = 0; i < 8; i++)
			cout << d[i] << ' ';
	//}
	system("pause");
}

template <typename T>
bool parse(string _input, T *result) {

	T j = 0;
	T s;
	int res;
	
	for (T i = 0; i < 8; i++) {
		
		res = 0;
		s = 1;
		while (_input[j] == ' ')
			j++;
		if (_input[j] == '-') {
			s = -1;
			j++;
		}
		if ((_input[j] < '0') || (_input[j] > '9')) {
			return false;
		}
		while ((_input[j] >= '0') && (_input[j] <= '9')) {
			res = res * 10 + _input[j] - '0';
			j++;
		}
		res = res * s;
		switch (sizeof(T))
		{
		case sizeof(__int8):
			if ((res < -128) || (res > 127))
				return false;
			break;
		case sizeof(__int16):
			if ((res < -32768) || (res > 32767))
				return false;
			break;
		}
		result[i] = (T)res;
	}

	return true;
}

int32_t calc(__int8 *_a, __int8 *_b, __int8 *_c, __int16 *_d) {

	int32_t f[8];
	__asm {



	}
	return 1;
}