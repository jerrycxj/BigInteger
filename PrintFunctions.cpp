#include <iostream>
#include <fstream>
#include "BigInteger.hpp"

using namespace std;

void BigInteger::hexPrint() const {
	unsigned long long mask = 0xF;
	unsigned long long index = this->size;
	unsigned long long temp = 0;
	//while(--index && digits[index] == 0) { }
	//++index;
	while(index--) {
		mask = 0xF;
		mask <<= 60;
		for(unsigned char i = 64;i;i -= 4) {
			temp = this->digits[index] & mask;
			temp >>= i - 4;
			temp += 48;
			if(temp > 57) temp += 7;
			cout << (char)(temp);
			mask >>= 4;
		}
		cout << " ";
	}
}

void BigInteger::binPrint() const {
	unsigned long long index = size;
	while(--index && digits[index] == 0) { }
	++index;
	while(index--) {
		cout << binDigit(index);
		cout << " ";
	}
}

string BigInteger::binDigit(unsigned long long digit) const {
	if(digit < 0 || digit >= size)
		return "invalid index in binDigit(unsigned long long)";
	string retString = "";
	unsigned long long testDigit = 0b1;
	testDigit <<= 63;
	while(testDigit) {
		retString += ( (digits[digit] & testDigit) ? '1' : '0' );
		testDigit >>= 1;
	}
	return retString;
}

void BigInteger::binDump(string filename) const {
	char* name = new char[filename.length() + 1];
	for(unsigned int i = 0;i < filename.length();++i)
		name[i] = filename[i];
	name[filename.length()] = '\0';
	ofstream file;
	file.open(name);
	unsigned long long charMask = 0;
	unsigned long long index = this->size;
	unsigned long long temp = 0;
	char printer = '\0';
	while(index--) {
		charMask = 0xFF;
		charMask <<= 56;
		
		for(unsigned char i = 64;i;i-=8) {
			temp = digits[index] & charMask;
			temp >>= i - 8;
			printer = (char)temp;
			charMask >>= 8;
			file << printer;
		}
	}
	file.close();
	delete[] name;
}
