#ifndef __CONNECTION_EXCEPTION
#define __CONNECTION_EXCEPTION

#include <exception>

class ConnectionException : public std::exception
{
public:
	ConnectionException(const char* mensaje);
	~ConnectionException() = default;

	virtual const char* what() const;
private:
	char* msj;
};

#endif