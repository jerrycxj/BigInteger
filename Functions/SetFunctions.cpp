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
	while(index) {
		shifted = (unsigned long long)std::rand() << 32;
		digits[--index] = shifted;
		digits[index] += std::rand();
	}
}
