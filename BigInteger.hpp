#include <string>
//#include <iostream>

#include "DynamicDecimal/DynamicDecimal.hpp"

/*
Author:
Steven Borisko

Description:
Class for arbitrarily large number arithmetic
*/

class BigInteger {

	private:

	// constants used mainly for bit masking //

	// 32 bits of 1
	const unsigned long long half = 0b11111111111111111111111111111111;
	// 64 bits of 1
	const unsigned long long full = 0b1111111111111111111111111111111111111111111111111111111111111111;
	// 1 at 64th (index 63) (leftmost) bit
	const unsigned long long left = 0b1000000000000000000000000000000000000000000000000000000000000000;

	// data

	// number of digits in the number
	unsigned long long size;
	// array of digits in the number
	unsigned long long* digits;

	// helper function

	// retrieves, in string form, digits at index 'digit'
	std::string binDigit(const unsigned long long digit) const;

	public:

	// Constructors //

	// creates a number of 'newSize' digits set to zero
	BigInteger(unsigned long long newSize);
	// creates a number of 'newSize' digits set to 'initNum'
	BigInteger(unsigned long long initNum, unsigned long long newSize);
	// deep copy of rhs
	BigInteger(const BigInteger& rhs);
	~BigInteger();

	// Print Functions //

	// prints the entire number in hexadecimal
	void hexPrint() const;
	// prints, starting at the first non-zero digit, the number in binary
	void binPrint() const;
	// prints actual binary of number to file 'filename'
	void binDump(const std::string filename) const;
	// prints entire number in decimal
	void decPrint() const;

	// Math Functions //

	// Absolute Value
	BigInteger abs() const;
	// Square Root
	BigInteger sqrt() const;
	// Power: this ^ exp
	BigInteger pow(const BigInteger& exp) const;
	BigInteger pow(const unsigned long long& exp) const;
	// Factorialize
	BigInteger fact() const;

	// SetFunctions //

	// Set to zero
	void zero();
	// Set to a random number
	void rand();
	// Resizes the number to 'newSize' digits
	// if digits < size
		// the most significant digits will be cut off
		// the least significant digits will remain in the resized number
	// if digits > size
		// the whole number will remain in the resized number
		// the new, most significant digits will be willed in with zeroes
	void resize(unsigned long long newSize);

	/*** Operator Overloads ***/

	// Assignment: deep copy //
	BigInteger& operator=(const BigInteger& rhs);
	BigInteger& operator=(const unsigned long long& rhs);
	unsigned long long operator[](const unsigned long long& index) const;
	unsigned long long& operator[](const unsigned long long& index);

	// Binary //
	BigInteger& operator+=(const BigInteger& rhs);
	BigInteger operator+(const BigInteger& rhs) const;
	BigInteger& operator-=(const BigInteger& rhs);
	BigInteger operator-(const BigInteger& rhs) const;
	BigInteger& operator*=(const BigInteger& rhs);
	BigInteger operator*(const BigInteger& rhs) const;
	BigInteger& operator/=(const BigInteger& rhs);
	BigInteger operator/(const BigInteger& rhs) const;
	BigInteger& operator%=(const BigInteger& rhs);
	BigInteger operator%(const BigInteger& rhs) const;

	// Bitwise //
	BigInteger& operator&=(const BigInteger& rhs);
	BigInteger operator&(const BigInteger& rhs) const;
	BigInteger& operator&=(const unsigned long long& rhs);
	BigInteger operator&(const unsigned long long& rhs) const;

	BigInteger& operator^=(const BigInteger& rhs);
	BigInteger operator^(const BigInteger& rhs) const;
	BigInteger& operator^=(const unsigned long long& rhs);
	BigInteger operator^(const unsigned long long& rhs) const;

	BigInteger& operator|=(const BigInteger& rhs);
	BigInteger operator|(const BigInteger& rhs) const;
	BigInteger& operator|=(const unsigned long long& rhs);
	BigInteger operator|(const unsigned long long& rhs) const;

	BigInteger operator~() const;

	BigInteger& operator<<=(const unsigned long long& shift);
	BigInteger operator<<(const unsigned long long& shift) const;
	BigInteger& operator>>=(const unsigned long long& shift);
	BigInteger operator>>(const unsigned long long& shift) const;

	// Unary //
	BigInteger operator!() const;
	BigInteger operator-() const;
		// Prefix
	BigInteger& operator++();
	BigInteger& operator--();
		// Postfix
	BigInteger operator++(int);
	BigInteger operator--(int);

	// Relational //
	bool operator==(const BigInteger& rhs) const;
	bool operator!=(const BigInteger& rhs) const;
	bool operator<=(const BigInteger& rhs) const;
	bool operator<(const BigInteger& rhs) const;
	bool operator>=(const BigInteger& rhs) const;
	bool operator>(const BigInteger& rhs) const;

	// Flags //

	// Zero
	bool Z() const;
	// Negative
	bool N() const;
	// Odd
	bool O() const;

};
