#include <iostream>
#include <fstream>

#include "../BigInteger.hpp"

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
			std::cout << (char)(temp);
			mask >>= 4;
		}
		std::cout << " ";
	}
}

void BigInteger::binPrint() const {
	unsigned long long index = size;
	while(--index && digits[index] == 0) { }
	++index;
	while(index--) {
		std::cout << binDigit(index);
		std::cout << " ";
	}
}

std::string BigInteger::binDigit(const unsigned long long digit) const {
	if(digit >= size)
		return "invalid index in binDigit(unsigned long long)";
	std::string retString = "";
	unsigned long long testDigit = 0b1;
	testDigit <<= 63;
	while(testDigit) {
		retString += ( (digits[digit] & testDigit) ? '1' : '0' );
		testDigit >>= 1;
	}
	return retString;
}

void BigInteger::binDump(const std::string filename) const {
	const char* name = filename.c_str();
	std::ofstream file;
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
}

void BigInteger::decPrint() const {
	DynamicDecimal acc = DynamicDecimal(0);
	unsigned long long mask = left;
	unsigned long long index = this->size - 1;
	unsigned long long currDigit = this->digits[index];

	mask >>= 1;
	while(mask) {
		acc.multiplyByTwo();
		if(mask & currDigit) acc.addOne();
		mask >>= 1;
	}

	while(index--) {
		currDigit = this->digits[index];
		mask = left;
		while(mask) {
			acc.multiplyByTwo();
			if(mask & currDigit) acc.addOne();
			mask >>= 1;
		}
	}

	if(this->N()) std::cout << "-";
	acc.print();
}
