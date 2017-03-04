#include "../BigInteger.hpp"

// ADDITION //

BigInteger& BigInteger::operator+=(const BigInteger& rhs) {
	if(this->size != rhs.size) {
		//std::cout << "+: unequal sizes\n";
		return *this;
	}

	if(this == &rhs) {
		*this = (*this + rhs);
		return *this;
	}

	unsigned long long index = 0;
	unsigned long long originalDigit = 0;
	unsigned char overflow = 0;
	do {
		originalDigit = this->digits[index];
		this->digits[index] += overflow;
		overflow = (this->digits[index] < originalDigit);

		originalDigit = this->digits[index];
		this->digits[index] += rhs.digits[index];
		overflow |= (this->digits[index] < originalDigit);
	}while(++index < this->size);

	return *this;
}

BigInteger& BigInteger::operator+=(const unsigned long long& rhs) {
	unsigned long long index = 0;
	unsigned long long originalDigit = 0;
	unsigned long long overflow = rhs;
	do {
		originalDigit = this->digits[index];
		this->digits[index] += overflow;
		overflow = (this->digits[index] < originalDigit);
	} while(overflow & (++index < this->size));

	return *this;
}

// SUBTRACTION //

BigInteger& BigInteger::operator-=(const BigInteger& rhs) {
	if(this->size != rhs.size) {
		//std::cout << "-: unequal sizes\n";
		return *this;
	}
	*this += -rhs;
	return *this;
}

BigInteger& BigInteger::operator-=(const unsigned long long& rhs) {

	this->neg();
	*this += rhs;
	this->neg();

	return *this;
}

// MULTIPLICATION //

BigInteger& BigInteger::operator*=(const BigInteger& rhs) {
	if(this->size != rhs.size) {
		//std::cout << "*: unequal sizes\n";
		return *this;
	}

	if(this == &rhs) {
		*this = (*this * rhs);
		return *this;
	}

	if(this->Z()) return *this;
	if(rhs.Z()) {
		this->zero();
		return *this;
	}

	BigInteger acc = BigInteger(this->size);

	for(unsigned long long i = this->size;i;--i) {
		for(unsigned long long j = 64;j;--j) {

			if(this->digits[0] & 1) acc += rhs;
			*this >>= 1;
			if(acc.digits[0] & 1)
				this->digits[this->size - 1] |= left;
			acc >>= 1;

		}
	}

	return *this;
}

BigInteger& BigInteger::operator*=(const unsigned long long& rhs) {

	unsigned long long acc = 0;
	for(unsigned long long i = this->size;i;--i) {
		for(unsigned long long j = 64;j;--j) {

			if(this->digits[0] & 1) acc += rhs;
			*this >>= 1;
			if(acc & 1)
				this->digits[this->size - 1] |= left;
			acc >>= 1;

		}
	}

	return *this;
}

// DIVISION //

BigInteger& BigInteger::operator/=(const BigInteger& rhs) {
	if(this->size != rhs.size) {
		//std::cout << "/: unequal sizes\n";
		return *this;
	}

	if(this == &rhs) {
		*this = (*this / rhs);
		return *this;
	}

	// if either number is zero, return zero

	if(rhs.Z()) {
		//std::cout << "/: division by zero\n";
		this->zero();
		return *this;
	}

	if(this->Z()) return *this;

	BigInteger acc = BigInteger(this->size);
	BigInteger sor = BigInteger(rhs);

	bool thisNegative = this->N();
	bool rhsNegative = rhs.N();

	bool negAns = (thisNegative ^ rhsNegative);

	if(thisNegative) this->neg();
	if(rhsNegative) sor.neg();

	BigInteger negSor = BigInteger(sor);
	negSor.neg();

	bool negative = false;
	for(unsigned long long i = this->size;i;--i) {
		for(unsigned long long j = 64;j;--j) {

			negative = acc.N();
			acc <<= 1;
			if(this->N()) acc.digits[0] |= 1;
			*this <<= 1;
			acc += (negative ? sor : negSor);
			this->digits[0] |= !acc.N();

		}
	}

	if(negAns) this->neg();

	return *this;
}

BigInteger& BigInteger::operator/=(const unsigned long long& rhs) {

	if(rhs == 0) {
		this->zero();
		return *this;
	}
	if(this->Z()) return *this;

	bool negAns = this->N();
	if(negAns) this->neg();

	unsigned long long acc = 0;
	unsigned long long negRHS = ~rhs;
	++negRHS;
	bool negative = false;
	for(unsigned long long i = this->size;i;--i) {
		for(unsigned long long j = 64;j;--j) {

			negative = (acc & left);
			acc <<= 1;
			if(this->N()) acc |= 1;
			*this <<= 1;
			acc += (negative ? rhs : negRHS);
			this->digits[0] |= !(acc & left);

		}
	}

	if(negAns) this->neg();

	return *this;
}

// MODULUS //

BigInteger& BigInteger::operator%=(const BigInteger& rhs) {
	if(this->size != rhs.size) {
		//std::cout << "%: unequal sizes\n";
		return *this;
	}

	if(this == &rhs) {
		*this = (*this % rhs);
		return *this;
	}

	// obvious cases

	if(this->Z()) return *this;

	BigInteger acc = BigInteger(this->size);
	BigInteger sor = BigInteger(rhs);

	if(this->N()) this->neg();
	if(rhs.N()) sor.neg();

	if(*this <= sor) {
		if(*this < sor)
			return *this;
		if(*this == sor) {
			this->zero();
			return *this;
		}
	}

	BigInteger negSor = BigInteger(sor);
	negSor.neg();

	bool negative = false;
	for(unsigned long long i = this->size;i;--i) {
		for(unsigned long long j = 64;j;--j) {

			negative = acc.N();
			acc <<= 1;
			if(this->N()) acc.digits[0] |= 1;
			*this <<= 1;
			acc += (negative ? sor : negSor);
			this->digits[0] |= !acc.N();

		}
	}

	if(acc.N()) acc += sor;

	*this = acc;

	return *this;
}

BigInteger& BigInteger::operator%=(const unsigned long long& rhs) {

	if(this->N()) this->neg();
	if(this->Z()) return *this;

	unsigned long long acc = 0;
	unsigned long long negRHS = ~rhs;
	++negRHS;
	bool negative = false;
	for(unsigned long long i = this->size;i;--i) {
		for(unsigned long long j = 64;j;--j) {

			negative = (acc & left);
			acc <<= 1;
			if(this->N()) acc |= 1;
			*this <<= 1;
			acc += (negative ? rhs : negRHS);
			this->digits[0] |= !(acc & left);

		}
	}

	if(acc & left) acc += rhs;

	this->zero();
	this->digits[0] = acc;

	return *this;
}
