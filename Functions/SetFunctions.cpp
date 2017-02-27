#include <cstdlib>
#include <ctime>

#include "../BigInteger.hpp"

void BigInteger::zero() {
	unsigned long long index = size;
	while(index) digits[--index] = 0;
}

void BigInteger::rand() {
	std::srand(std::time(0));
	unsigned long long index = size;
	unsigned long long shifted = 0;
	unsigned long long temp = 0;
	while(index) {
		temp = (unsigned long long) std::rand() << 32;
		temp += std::rand();
		shifted = (unsigned long long)std::rand() << 32;
		digits[--index] = shifted;
		digits[index] += std::rand();
		digits[index] += temp;
	}
}

void BigInteger::resize(unsigned long long newSize) {
	if(newSize == size) return;
	unsigned long long* newArray = new unsigned long long[newSize];
	unsigned long long index = 0;
	while((index < newSize) & (index < size)) {
		newArray[index] = digits[index];
		++index;
	}
	--index;
	while(++index < newSize)
		newArray[index] = 0;
	delete[] digits;
	digits = newArray;
	size = newSize;
}
