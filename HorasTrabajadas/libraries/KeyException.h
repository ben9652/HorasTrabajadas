#ifndef __KEY_EXCEPTION
#define __KEY_EXCEPTION

#include <exception>

class KeyException : public std::exception
{
public:
	KeyException(const char* mensaje);
	~KeyException() = default;

	virtual const char* what() const;
private:
	char* msj;
};

#endif