#ifndef __INTEGER_
#define __INTEGER_

class Integer
{
public:
	Integer(int i);
	Integer(const Integer& other);
	Integer(Integer* other);
	~Integer() = default;

	void operator=(const int& other);
	void operator=(const Integer& other);
	operator int() const;
	friend bool operator<(const Integer& i1, const Integer& i2);
	friend bool operator>(const Integer& i1, const Integer& i2);
	friend bool operator<=(const Integer& i1, const Integer& i2);
	friend bool operator>=(const Integer& i1, const Integer& i2);
	friend bool operator==(const Integer& i1, const Integer& i2);

	friend bool operator<(const Integer& i1, const int& i2);
	friend bool operator<(const int& i1, const Integer& i2);
	friend bool operator>(const Integer& i1, const int& i2);
	friend bool operator>(const int& i1, const Integer& i2);
	friend bool operator<=(const Integer& i1, const int& i2);
	friend bool operator<=(const int& i1, const Integer& i2);
	friend bool operator>=(const Integer& i1, const int& i2);
	friend bool operator>=(const int& i1, const Integer& i2);
	friend bool operator==(const Integer& i1, const int& i2);
	friend bool operator==(const int& i1, const Integer& i2);

	int getInt();
	void setInt(int i);
	char getChar();

private:
	int i;
};

#endif