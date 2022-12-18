#include "mbed.h"
#include <cstdio>
#include <string>
#include <iostream>
using namespace std;
DigitalOut myled(LED1);
const double teckaMezera = 0.2; // 200 ms
const double carkaMezera = 0.75; // 750 ms
const double znakMezera = 1.3; // 1.3 sec
string morseEncode(char x) {
	// refer to the Morse table
	// image attached in the article
	switch (x) {
	case 'a':
		return ".-";
	case 'b':
		return "-...";
	case 'c':
		return "-.-.";
	case 'd':
		return "-..";
	case 'e':
		return ".";
	case 'f':
		return "..-.";
	case 'g':
		return "--.";
	case 'h':
		return "....";
	case 'i':
		return "..";
	case 'j':
		return ".---";
	case 'k':
		return "-.-";
	case 'l':
		return ".-..";
	case 'm':
		return "--";
	case 'n':
		return "-.";
	case 'o':
		return "---";
	case 'p':
		return ".--.";
	case 'q':
		return "--.-";
	case 'r':
		return ".-.";
	case 's':
		return "...";
	case 't':
		return "-";
	case 'u':
		return "..-";
	case 'v':
		return "...-";
	case 'w':
		return ".--";
	case 'x':
		return "-..-";
	case 'y':
		return "-.--";
	case 'z':
		return "--..";
	default:
		//cerr << "Found invalid character: " << x << ' '
		// << std::endl;
		exit(0);
	}
}
string morseCode(string s)
{
	string ok = "";
	// character by character print
	// Morse code
	for (int i = 0; s[i]; i++) {
		cout << morseEncode(s[i]);
		ok = ok + morseEncode(s[i]);
	}


	cout << endl;
	return ok;
}
int main() {
	printf("David Karnik  Tomas Chmelar");
	while (1) {
		//myled = 1; // LED is ON
		//wait(0.2); // 200 ms
		//myled = 0; // LED is OFF
		//wait(1.0); // 1 sec
		string s = "davidkarniktomaschmelar";
		string hotovo = morseCode(s);
		const char tecka = '.';
		//for (promenna; podminka; prikaz)
		for (int i = 0; i < hotovo.length(); i++) {
			//bool porovnani= hotovo[i] == '.';
			if (hotovo[i] == tecka) {
				myled = 1; // LED is ON
				wait(teckaMezera); // 200 ms
				//myled = 0; // LED is OFF
				//wait(1.0); // 1 sec
			}
			else {
				myled = 1; // LED is ON
				wait(carkaMezera); // 750 ms
			}
			myled = 0; // LED is OFF
			wait(znakMezera); // 1.3 sec
		}
		//return 0;

	}
}