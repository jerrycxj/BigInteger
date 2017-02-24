#include <iostream>
#include <string>
using namespace std;

class BigInteger {

	private:

	// constants used mainly for bit masking //

	// 32 bits of 1
	const unsigned long long half = 0b11111111111111111111111111111111;
	// 64 bits of 1
	const unsigned long long full = 0b1111111111111111111111111111111111111111111111111111111111111111;
	// 1 at 64th (index 63) (leftmost) bit
	const unsigned long long left = 0b1000000000000000000000000000000000000000000000000000000000000000;
	// number of digits in the number
	unsigned long long size;
	// array of digits in the number
	unsigned long long* digits;

	public:

	// Constructors //

	// creates a number of 'newSize' digits set to zero
	BigInteger(unsigned long long newSize);
	// creates a number of 'newSize' digits set to initNum
	BigInteger(unsigned long long initNum, unsigned long long newSize);
	// deep copy of rhs
	BigInteger(const BigInteger& rhs);
	~BigInteger();

	// Print Functions //

	// prints the entire number in hexadecimal
	void hexPrint() const;
	// prints, starting at the first non-zero digit, the number in binary
	void binPrint() const;
	// retrieves, in string form, digits at index 'digit'
	string binDigit(unsigned long long digit) const;
	// prints actual binary of number to file 'filename'
	void binDump(string filename) const;

	// Math Functions //

	// Absolute Value
	BigInteger abs() const;
	// Square Root
	BigInteger sqrt() const;
	// Power: this ^ exp
	BigInteger pow(const BigInteger& exp) const;

	/*** Operator Overloads ***/

	// Assignment: deep copy //
	BigInteger& operator=(const BigInteger& rhs);

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
	BigInteger& operator^=(const BigInteger& rhs);
	BigInteger operator^(const BigInteger& rhs) const;
	BigInteger& operator|=(const BigInteger& rhs);
	BigInteger operator|(const BigInteger& rhs) const;
	BigInteger operator~() const;
	BigInteger& operator<<=(unsigned long long shift);
	BigInteger operator<<(unsigned long long shift) const;
	BigInteger& operator>>=(unsigned long long shift);
	BigInteger operator>>(unsigned long long shift) const;

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

	//friend ostream& operator<<(ostream& os, const BigInteger& number);

	// Flags //

	// Zero
	bool Z() const;
	// Negative
	bool N() const;
	// Odd
	bool O() const;

};
/*
ostream& operator<<(ostream& os, const BigInteger& number) {
	number.binPrint();
	return os;
	
}
*/
