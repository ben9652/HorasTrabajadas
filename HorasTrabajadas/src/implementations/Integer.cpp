#include "Integer.h"

Integer::Integer(int i)
{
	this->i = i;
}

Integer::Integer(const Integer& other)
{
	this->i = other.i;
}

Integer::Integer(Integer* other)
{
	this->i = other->i;
}

void Integer::operator=(const int& other)
{
	this->i = other;
}

void Integer::operator=(const Integer& other)
{
	this->i = other.i;
}

Integer::operator int() const
{
	return i;
}

int Integer::getInt()
{
	return i;
}

void Integer::setInt(int i)
{
	this->i = i;
}

char Integer::getChar()
{
	return (char)i;
}

bool operator<(const Integer& i1, const Integer& i2)
{
	return i1.i < i2.i;
}

bool operator>(const Integer& i1, const Integer& i2)
{
	return i1.i > i2.i;
}

bool operator<=(const Integer& i1, const Integer& i2)
{
	return i1.i <= i2.i;
}

bool operator>=(const Integer& i1, const Integer& i2)
{
	return i1.i >= i2.i;
}

bool operator==(const Integer& i1, const Integer& i2)
{
	return i1.i == i2.i;
}

bool operator<(const Integer& i1, const int& i2)
{
	return i1.i < i2;
}

bool operator<(const int& i1, const Integer& i2)
{
	return i1 < i2.i;
}

bool operator>(const Integer& i1, const int& i2)
{
	return i1.i > i2;
}

bool operator>(const int& i1, const Integer& i2)
{
	return i1 > i2.i;
}

bool operator<=(const Integer& i1, const int& i2)
{
	return i1.i <= i2;
}

bool operator<=(const int& i1, const Integer& i2)
{
	return i1 <= i2.i;
}

bool operator>=(const Integer& i1, const int& i2)
{
	return i1.i >= i2;
}

bool operator>=(const int& i1, const Integer& i2)
{
	return i1 >= i2.i;
}

bool operator==(const Integer& i1, const int& i2)
{
	return i1.i == i2;
}

bool operator==(const int& i1, const Integer& i2)
{
	return i1 == i2.i;
}
