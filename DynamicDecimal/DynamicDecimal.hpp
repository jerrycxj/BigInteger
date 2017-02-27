/*
These structs are solely for converting a binary number to decimal
*/

struct DecimalNode {

private:
	const unsigned long long base = 1000000000000000000ULL;

public:
	unsigned long long data;
	DecimalNode* left;
	DecimalNode* right;

	DecimalNode(unsigned long long newData);
	void add(unsigned long long adder);
	void print();

};

struct DynamicDecimal {

private:
	const unsigned long long base = 1000000000000000000ULL;
	DecimalNode* onesDigit;
	DecimalNode* leadDigit;

	void updateLead();

public:

	DynamicDecimal(unsigned long long initNum);
	~DynamicDecimal();

	void multiplyByTwo();
	void addOne();

	void print();

};
