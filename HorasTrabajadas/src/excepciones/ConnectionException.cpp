#include "ConnectionException.h"

ConnectionException::ConnectionException(const char* mensaje)
{
	msj = (char*)mensaje;
}

const char* ConnectionException::what() const
{
	return msj;
}