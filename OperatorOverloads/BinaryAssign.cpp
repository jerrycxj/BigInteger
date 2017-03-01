#include "../BigInteger.hpp"

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
	unsigned long long overflow = 0;
	unsigned long long originalDigit = 0;
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

BigInteger& BigInteger::operator-=(const BigInteger& rhs) {
	if(this->size != rhs.size) {
		//std::cout << "-: unequal sizes\n";
		return *this;
	}
	*this += -rhs;
	return *this;
}

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

	if(this->size > (full >> 1)) {
		//std::cout << "*: numbers too big\n";
		return *this;
	}

	BigInteger acc = BigInteger(this->size * 2);
	BigInteger adder = BigInteger(this->size * 2);
	BigInteger rhsCopy = BigInteger(rhs);
	BigInteger one = BigInteger(1,this->size);
	BigInteger temp = BigInteger(this->size);

	// copy rhs into the left half of rhsCopy
	for(unsigned long long i = 0; i < this->size;++i)
		adder.digits[i + this->size] = this->digits[i];

	for(unsigned long long i = this->size;i;--i) {
		for(unsigned char j = 64;j;--j) {
			temp = rhsCopy;
			temp &= one;
			if(!temp.Z()) acc += adder;
			acc >>= 1;
			rhsCopy >>= 1;
		}
	}

	for(unsigned long long i = 0; i < this->size; ++i)
		this->digits[i] = acc.digits[i];

	return *this;
}

BigInteger& BigInteger::operator/=(const BigInteger& rhs) {
	if(this->size != rhs.size) {
		//std::cout << "/: unequal sizes\n";
		return *this;
	}

	if(this == &rhs) {
		*this = (*this / rhs);
		return *this;
	}

	if(this->size > (full >> 1)) {
		//std::cout << "/: numbers too big\n";
		return *this;
	}

	// if either number is zero, return zero

	if(rhs.Z()) {
		//std::cout << "/: division by zero\n";
		this->zero();
		return *this;
	}
	if(this->Z()) return *this;

	if(*this <= rhs) {
		if(*this < rhs) {
			this->zero();
			return *this;
		}
		if(*this == rhs) {
			this->zero();
			this->digits[0] = 1;
			return *this;
		}
	}


	unsigned long long doubleThisSize = this->size << 1;

	BigInteger DEND = BigInteger(doubleThisSize);
	// DENDS is DEND shifted right this->size
	BigInteger DENDS = BigInteger(doubleThisSize);

	BigInteger SOR = BigInteger(doubleThisSize);
	// SORS is SOR shifted left this->size
	BigInteger SORS = BigInteger(doubleThisSize);

	BigInteger QUO = BigInteger(doubleThisSize);

	BigInteger tempThisABS = BigInteger(this->abs());
	BigInteger tempRhsABS = BigInteger(rhs.abs());


	// Set the Dividend and Divisor

	bool negAns = (this->N() ^ rhs.N());

	for(unsigned long long i = 0;i < this->size;++i) {
		DEND.digits[i] = tempThisABS.digits[i];
		SOR.digits[i] = tempRhsABS.digits[i];
	}

	BigInteger OGDEND = BigInteger(DEND);

	SORS = SOR;
	for(unsigned char i = 64;i;--i)
		SORS <<= this->size;

	BigInteger one = BigInteger(1,doubleThisSize);

	for(unsigned long long i = this->size;i;--i) {
		for(unsigned char j = 64;j;--j) {
			DENDS = DEND;
			for(unsigned char k = 64;k;--k)
				DENDS >>= this->size;
			if(DENDS >= SOR) {
				QUO ^= one;
				DEND -= SORS;
			}
			DEND <<= 1;
			QUO <<= 1;
		}
	}

	DEND = QUO;
	DEND *= SOR;
	if(DEND > OGDEND) ++QUO;
	if(negAns) QUO = -QUO;

	for(unsigned long long i = 0;i < this->size;++i)
		this->digits[i] = QUO.digits[i];

	return *this;
}

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

	if(*this <= rhs) {
		if(*this < rhs)
			return *this;
		if(*this == rhs) {
			this->zero();
			return *this;
		}
	}

	// slow mod

	BigInteger quotient = BigInteger(this->size);
	quotient = *this / rhs;

	quotient *= rhs;

	*this -= quotient;

	return *this;
}
