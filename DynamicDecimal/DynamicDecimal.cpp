#include <iostream>

#include "DynamicDecimal.hpp"

// DecimalNode //

DecimalNode::DecimalNode(unsigned long long newData) :

	data(newData),
	left(nullptr),
	right(nullptr)

	{

	unsigned long long overflow = newData / base;
	if(overflow) {
		left = new DecimalNode(overflow);
		left->right = this;
		data %= base;
	}

}

void DecimalNode::add(unsigned long long adder) {
	data += adder;
	unsigned long long overflow = data / base;
	if(overflow) {
		if(left) {
			left->add(overflow);
		}
		else {
			left = new DecimalNode(overflow);
			left->right = this;
		}
		data %= base;
	}
}

void DecimalNode::print() {
	unsigned char zeros = 18;
	unsigned long long dataCopy = this->data;

	while(dataCopy) {
		dataCopy /= 10;
		--zeros;
	}
	while(zeros--)
		std::cout << "0";
	std::cout << this->data;
}

// DynamicDecimal //

void DynamicDecimal::updateLead() {
	while(leadDigit->left) leadDigit = leadDigit->left;
}

DynamicDecimal::DynamicDecimal(unsigned long long initNum) :

	onesDigit(nullptr),
	leadDigit(nullptr)

	{

	onesDigit = new DecimalNode(initNum);
	leadDigit = (onesDigit->left ? onesDigit->left : onesDigit);

}

DynamicDecimal::~DynamicDecimal() {
	DecimalNode* temp;
	while(onesDigit) {
		temp = onesDigit->left;
		delete onesDigit;
		onesDigit = temp;
	}
}

void DynamicDecimal::multiplyByTwo() {
	DecimalNode* currNode = onesDigit;
	unsigned long long overflow = 0;
	while(currNode) {
		currNode->data <<= 1;
		currNode->data += overflow;
		overflow = currNode->data / base;
		if(overflow) {
			currNode->data %= base;
			if(!currNode->left) {
				currNode->left = new DecimalNode(0);
				currNode->left->right = currNode;
			}
		}
		currNode = currNode->left;
	}
	updateLead();
}

void DynamicDecimal::addOne() {
	onesDigit->add(1);
}

void DynamicDecimal::print() {
	updateLead();
	DecimalNode* currNode = leadDigit;

	while((!currNode->data) && currNode->right)
		currNode = currNode->right;

	std::cout << currNode->data;
	currNode = currNode->right;

	while(currNode) {
		currNode->print();
		currNode = currNode->right;
	}
}
