#include "ConjuntoRegistros.h"

ConjuntoRegistros::ConjuntoRegistros(int idConjuntoRegistros, const std::vector<Registro>& registros_agrupados)
{
    this->idConjuntoRegistros = idConjuntoRegistros;
    this->registros_agrupados = registros_agrupados;
}

int ConjuntoRegistros::getIdConjuntoRegistros() const
{
    return idConjuntoRegistros;
}

const std::vector<Registro>& ConjuntoRegistros::getConjuntoRegistros() const
{
    return registros_agrupados;
}

void ConjuntoRegistros::setIdConjuntoRegistros(int idConjuntoRegistros)
{
    this->idConjuntoRegistros = idConjuntoRegistros;
}