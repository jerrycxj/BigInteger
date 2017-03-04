#include "../BigInteger.hpp"

BigInteger abs(const BigInteger& num) {
	return (num.N() ? -(num) : BigInteger(num));
}

BigInteger sqrt(const BigInteger& num) {
	if(num.Z()) return num;
	if(num.N()) {
		//std::cout << "sqrt: negative radicand\n";
		return num;
	}

	BigInteger one = BigInteger(1,num.size);
	if(num == one) return one;

	BigInteger ret = BigInteger(num);

	for(unsigned long long i = num.size;i;--i)
		ret >>= 32;

	if(ret.Z()) ret = one + one;

	for(unsigned long long i = num.size;i;--i) {
		for(unsigned char j = 128;j;--j) {
			ret += num / ret;
			ret >>= 1;
		}
	}
	one = ret;
	one *= ret;
	if(one > num) --ret;
	return ret;
}

BigInteger pow(const BigInteger& num, const BigInteger& exp) {
	BigInteger acc = BigInteger(1,num.size);

	bool thisZ = num.Z();
	bool expZ = num.Z();
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
	BigInteger numCopy = BigInteger(num);
	while(!expCopy.Z()) {
		while(!expCopy.O()) {
			numCopy *= numCopy;
			expCopy >>= 1;
		}
		acc *= numCopy;
		--expCopy;
	}
	return acc;
}

BigInteger pow(const BigInteger& num, const unsigned long long& exp) {
	return pow(num, BigInteger(exp,1));
}

BigInteger fact(const BigInteger& num) {
	BigInteger ret = BigInteger(1,num.size);
	if(num.N()) {
		//std::cout << "fact: negative number\n";
		return ret;
	}
	if(num.Z() || num == ret) return ret;

	BigInteger copy = BigInteger(num);

	do {
		ret *= copy;
		--copy;
	}while(!copy.Z());

	return ret;
}
