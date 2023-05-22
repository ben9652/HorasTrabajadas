#include "KeyException.h"

KeyException::KeyException(const char* mensaje)
{
	msj = (char*)mensaje;
}

const char* KeyException::what() const
{
	return msj;
}
