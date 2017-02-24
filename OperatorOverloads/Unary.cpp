#include "../BigInteger.hpp"

BigInteger BigInteger::operator!() const {
	BigInteger ret = BigInteger(!this->Z(),this->size);
	return ret;
}
BigInteger BigInteger::operator-() const {
	BigInteger copy = BigInteger(*this);
	copy = ~copy;
	++copy;
	return copy;
}

// Prefix
BigInteger& BigInteger::operator++() {
	BigInteger one = BigInteger(1,this->size);
	*this += one;
	return *this;
}

BigInteger& BigInteger::operator--() {
	BigInteger one = BigInteger(1,this->size);
	*this -= one;
	return *this;
}

// Postfix
BigInteger BigInteger::operator++(int) {
	BigInteger ret = BigInteger(*this);
	++(*this);
	return ret;
}

BigInteger BigInteger::operator--(int) {
	BigInteger ret = BigInteger(*this);
	--(*this);
	return ret;
}
