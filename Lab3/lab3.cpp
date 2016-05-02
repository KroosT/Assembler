#include <iostream> 
#include <string>

using namespace std;

template <typename T>
bool parse(string _input, T *result);

int main()
{
	char retry = '1';

	while (retry == '1') {

		__int8 a[8] = { 1, 123, 1, -1, 1, 4, -1, 3 };
		__int8 b[8] = { 1, -2, 3, 4, -128, 1, 11, 1 };
		__int8 c[8] = { 1, 127, -3, 4, -5, 6, 7, 8 };
		__int16 d[8] = { 1, 1, -1, -1, 1, 1, 1, 1 };
		__int16 g[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
		__int32 f[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };

		//(A+B)*C*D
		
		char choice;
		cout << "Do you want to input the arrays mannualy, or just use the default?" << endl;
		cout << "Input please '1' for the manual input." << endl;
		cin >> choice;
		if (choice == '1') {
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
		__asm
		{
			xor eax, eax
			mov eax, -1
				movd mm5, eax
				punpckldq mm5, mm5			//mm5 = 8*(-1)
				packssdw mm5, mm5
				packuswb mm5, mm5
				movq mm2, mm5
				movq mm0, a					//mm0=a
				movq mm1, mm0				//mm0=mm1=a
				pcmpgtb mm2, mm0
				pxor mm2, mm5
				punpcklbw mm0, mm2			//mm0=a[1..4]
				punpckhbw mm1, mm2			//mm1=a[5..8]
				movq mm4, mm5
				movq mm2, b					//mm2=b
				movq mm3, mm2				//mm3=mm2=b
				pcmpgtb mm4, mm2
				pxor mm4, mm5
				punpcklbw mm2, mm4			//mm2=b[1..4]
				punpckhbw mm3, mm4			//mm3=b[5..8]
				paddsw mm0, mm2				//mm0=a+b[1..4]
				paddsw mm1, mm3				//mm1=a+b[5..8]
				movq mm4, mm5
				movq mm2, c					//mm2=c
				movq mm3, mm2				//mm3=mm2=c
				pcmpgtb mm4, mm2
				pxor mm4, mm5
				punpcklbw mm2, mm4			//mm2=c[1..4]
				punpckhbw mm3, mm4			//mm3=c[5..8]
				pmullw mm0, mm2				//mm0=(a+b)*c[1..4]
				pmullw mm1, mm3				//mm1=(a+b)*c[5..8]
				movq mm2, mm0				//mm2=(a+b)*c[1..4]
				movq mm3, mm1				//mm3=(a+b)*c[5..8]
				pmullw mm1, d[TYPE d * 4]	//mm1=(a+b)*c[5..8]*d l.o.
				pmulhw mm2, d				//mm2=(a+b)*c[1..4]*d h.o.
				pmullw mm0, d				//mm0=(a+b)*c[1..4]*d l.o.
				pmulhw mm3, d[TYPE d * 4]	//mm3=(a+b)*c[5..8]*d h.o.
				movq mm4, mm0
				punpcklwd mm0, mm2			//mm0=(a+b)*c[1..4]*d[1,2]
				punpckhwd mm4, mm2			//mm4=(a+b)*c[1..4]*d[3,4]
				movq mm5, mm1
				punpcklwd mm1, mm3			//mm1=(a+b)*c[5..8]*d[5,6]
				punpckhwd mm5, mm3			//mm5=(a+b)*c[5..8]*d[7,8]
				movq f, mm0
				movq f[TYPE f * 2], mm4
				movq f[TYPE f * 4], mm1
				movq f[TYPE f * 6], mm5
				emms
		}
		cout << "The resut is:" << endl;
		for (int i = 0; i < 8; i++) {
			cout << f[i] << ' ';
		}
		cout << endl;
		cout << "Do you want to retry?" << endl;
		cout << "Input '1' for retry." << endl;
		cin >> retry;
	}
	
	return 0;
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
		case sizeof(__int8) :
			if ((res < -128) || (res > 127))
				return false;
			break;
		case sizeof(__int16) :
			if ((res < -32768) || (res > 32767))
				return false;
			break;
		}
		result[i] = (T)res;
	}
	if (j < _input.length())
		return false;
	return true;
}
