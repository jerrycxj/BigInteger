#include "../BigInteger.hpp"

BigInteger& BigInteger::operator&=(const BigInteger& rhs) {
	if(this->size != rhs.size) {
		//std::cout << "&=: unequal sizes\n";
		return *this;
	}
	unsigned long long index = this->size;
	while(index--)
		this->digits[index] &= rhs.digits[index];
	return *this;
}

BigInteger BigInteger::operator&(const BigInteger& rhs) const {
	BigInteger ret = BigInteger(*this);
	ret &= rhs;
	return ret;
}

BigInteger& BigInteger::operator^=(const BigInteger& rhs) {
	if(this->size != rhs.size) {
		//std::cout << "^=: unequal sizes\n";
		return *this;
	}
	unsigned long long index = this->size;
	while(index--)
		this->digits[index] ^= rhs.digits[index];
	return *this;
}

BigInteger BigInteger::operator^(const BigInteger& rhs) const {
	BigInteger ret = BigInteger(*this);
	ret ^= rhs;
	return ret;
}

BigInteger& BigInteger::operator|=(const BigInteger& rhs) {
	if(this->size != rhs.size) {
		//std::cout << "|=: unequal sizes\n";
		return *this;
	}
	unsigned long long index = this->size;
	while(index--)
		this->digits[index] |= rhs.digits[index];
	return *this;
}

BigInteger BigInteger::operator|(const BigInteger& rhs) const {
	BigInteger ret = BigInteger(*this);
	ret |= rhs;
	return ret;
}

BigInteger BigInteger::operator~() const {
	BigInteger ret = BigInteger(*this);
	unsigned long long index = this->size;
	while(index--)
		ret.digits[index] = ~(this->digits[index]);
	return ret;
}

BigInteger& BigInteger::operator<<=(unsigned long long shift) {
	unsigned long long completeShifts = shift >> 6;

	// if shift > 64
	if(completeShifts) {
		if(completeShifts >= this->size) {
			this->zero();
			return *this;
		}
		else {
			unsigned long long index = this->size;
			while(index-- - completeShifts) {
				this->digits[index] = this->digits[index - completeShifts];
			}
			++index;
			while(index--) {
				this->digits[index] = 0;
			}
		}
	}

	unsigned long long insideShifts = 0b111111;
	insideShifts &= shift;

	unsigned long long digitsToShift = 64 - insideShifts;
	unsigned long long overflowMask = 0;
	if(insideShifts) {
		overflowMask = full;
		overflowMask >>= digitsToShift;
		overflowMask <<= digitsToShift;
	}
	else {
		return *this;
	}

	unsigned long long index = 0;
	unsigned long long overflow = 0;
	unsigned long long pastOverflow = 0;

	while(index < this->size) {
		pastOverflow = overflowMask & this->digits[index];
		this->digits[index] <<= insideShifts;
		this->digits[index] += overflow;
		overflow = pastOverflow >> digitsToShift;
		++index;
	}

	return *this;
}

BigInteger BigInteger::operator<<(unsigned long long shift) const {
	BigInteger ret = BigInteger(*this);
	ret <<= shift;
	return ret;
}

BigInteger& BigInteger::operator>>=(unsigned long long shift) {
	unsigned long long completeShifts = shift >> 6;

	// if shift > 64
	if(completeShifts) {
		if(completeShifts >= this->size) {
			this->zero();
			return *this;
		}
		else {
			unsigned long long index = 0;
			while(index < this->size - completeShifts) {
				this->digits[index] = this->digits[index + completeShifts];
				++index;
			}
			index = this->size - completeShifts;
			while(index < this->size) {
				this->digits[index] = 0;
				++index;
			}
		}
	}

	unsigned long long insideShifts = 0b111111;
	insideShifts &= shift;

	unsigned long long digitsToShift = 64 - insideShifts;
	unsigned long long overflowMask = 0;
	if(insideShifts) {
		overflowMask = full;
		overflowMask <<= digitsToShift;
		overflowMask >>= digitsToShift;
	}
	else {
		return *this;
	}

	unsigned long long index = this->size;
	unsigned long long overflow = 0;
	unsigned long long pastOverflow = 0;

	while(index--) {
		pastOverflow = overflowMask & this->digits[index];
		this->digits[index] >>= insideShifts;
		this->digits[index] += overflow;
		overflow = pastOverflow << digitsToShift;
	}

	return *this;
}

BigInteger BigInteger::operator>>(unsigned long long shift) const {
	BigInteger ret = BigInteger(*this);
	ret >>= shift;
	return ret;
}
