#ifndef __TREE_EXCEPTION
#define __TREE_EXCEPTION

#include <exception>

class TreeException : public std::exception
{
public:
	TreeException(const char* mensaje);
	~TreeException() = default;

	virtual const char* what() const;
private:
	char* msj;
};

#endif