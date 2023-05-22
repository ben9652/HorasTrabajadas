#include "TreeException.h"

TreeException::TreeException(const char* mensaje)
{
    msj = (char*)mensaje;
}

const char* TreeException::what() const
{
    return msj;
}
