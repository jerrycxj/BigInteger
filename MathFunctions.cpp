#include "BigInteger.hpp"

BigInteger BigInteger::abs() const {
	return (N() ? -(*this) : *this);
}

BigInteger BigInteger::sqrt() const {
	if(this->Z()) return *this;
	if(this->N()) {
		//std::cout << "sqrt: negative radicand\n";
		return *this;
	}

	BigInteger one = BigInteger(1,this->size);
	if(*this == one) return one;

	BigInteger ret = BigInteger(*this);

	for(unsigned long long i = this->size;i;--i)
		ret >>= 32;

	if(ret.Z()) ret = one + one;

	for(unsigned long long i = this->size;i;--i) {
		for(unsigned char j = 8;j;--j) {
			ret += *this / ret;
			ret >>= 1;
		}
	}
	one = ret;
	one *= ret;
	if(one > *this) --ret;
	return ret;
}

BigInteger BigInteger::pow(const BigInteger& exp) const {
	BigInteger acc = BigInteger(1,this->size);

	bool thisZ = this->Z();
	bool expZ = this->Z();
	if(thisZ & expZ) {
		//std::cout << "pow: 0 ^ 0\n";
		return acc;
	}

	if(expZ) return acc;
	if(thisZ) {
		acc.digits[0] = 0;
		return acc;
	}


	BigInteger expCopy = BigInteger(exp);
	BigInteger thisCopy = BigInteger(*this);
	while(!expCopy.Z()) {
		while(!expCopy.O()) {
			thisCopy *= thisCopy;
			expCopy >>= 1;
		}
		acc *= thisCopy;
		--expCopy;
	}
	return acc;
}

BigInteger BigInteger::fact() const {
	BigInteger ret = BigInteger(1,this->size);
	if(this->N()) {
		//std::cout << "fact: negative number\n";
		return ret;
	}
	if(this->Z() || *this == ret) return ret;

	BigInteger copy = BigInteger(*this);

	do {
		ret *= copy;
		--copy;
	}while(!copy.Z());

	return ret;
}


void BigInteger::setToZero() {
	unsigned long long index = size;
	while(index--) digits[index] = 0;
}
