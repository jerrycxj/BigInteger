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

	if(this->size > (full >> 1)) {
		//std::cout << "*: numbers too big\n";
		return *this;
	}

	const unsigned long long doubleSize = (this->size << 1);

	BigInteger acc = BigInteger(doubleSize);

	unsigned long long i = this->size;
	while(i--) acc.digits[i] = rhs.digits[i];


	BigInteger adder = BigInteger(doubleSize);
	i = this->size;
	while(i--) adder.digits[i + this->size] = this->digits[i];

	i = this->size;
	while(i--) {
		for(unsigned long long j = 64;j;--j) {
			if(acc.digits[0] & 1) acc += adder;
			acc >>= 1;
		}
	}

	i = this->size;
	while(i--) this->digits[i] = acc.digits[i];

	return *this;
}

BigInteger& BigInteger::operator*=(const unsigned long long& rhs) {

	unsigned long long rhsCopy = rhs;
	BigInteger acc = BigInteger(this->size + 1);
	BigInteger adder = BigInteger(this->size + 1);
	unsigned long long i = this->size;
	while(i--) adder[i + 1] = this->digits[i];

	for(i = 64;i;--i) {
		if(rhsCopy & 1) acc += adder;
		rhsCopy >>= 1;
		acc >>= 1;
	}

	i = this->size;
	while(i--) this->digits[i] = acc[i];

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
				QUO ^= 1;
				DEND -= SORS;
			}
			DEND <<= 1;
			QUO <<= 1;
		}
	}

	DEND = QUO;
	DEND *= SOR;
	if(DEND < OGDEND) ++QUO;
	if(negAns) QUO = -QUO;

	for(unsigned long long i = 0;i < this->size;++i)
		this->digits[i] = QUO.digits[i];

	return *this;
}

BigInteger& BigInteger::operator/=(const unsigned long long& rhs) {
	BigInteger DEND = BigInteger(this->size + 1);
	BigInteger OGDEND = BigInteger(*this);

	bool negAns = this->N();

	if(negAns) this->neg();

	unsigned long long i = this->size;
	while(i--) DEND.digits[i] = this->digits[i];

	this->zero();

	for(i = this->size;i;--i) {
		for(unsigned char j = 64;j;--j) {
			if(DEND.digits[this->size] >= rhs) {
				*this ^= 1;
				DEND.digits[this->size] -= rhs;
			}
			DEND <<= 1;
			*this <<= 1;
		}
	}

	if((*this * rhs) < OGDEND) ++(*this);
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

BigInteger& BigInteger::operator%=(const unsigned long long& rhs) {
	BigInteger quotient = BigInteger(*this);

	quotient /= rhs;
	quotient *= rhs;

	*this -= quotient;
	return *this;
}
