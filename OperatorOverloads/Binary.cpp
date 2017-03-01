#include "../BigInteger.hpp"

BigInteger BigInteger::operator+(const BigInteger& rhs) const {
	BigInteger ret = BigInteger(*this); 
	ret += rhs;
	return ret;
}

BigInteger BigInteger::operator-(const BigInteger& rhs) const {
	BigInteger ret = BigInteger(*this); 
	ret -= rhs;
	return ret;
}

BigInteger BigInteger::operator*(const BigInteger& rhs) const {
	BigInteger ret = BigInteger(*this); 
	ret *= rhs;
	return ret;
}

BigInteger BigInteger::operator/(const BigInteger& rhs) const {
	BigInteger ret = BigInteger(*this); 
	ret /= rhs;
	return ret;
}

BigInteger BigInteger::operator%(const BigInteger& rhs) const {
	BigInteger ret = BigInteger(*this); 
	ret %= rhs;
	return ret;
}
