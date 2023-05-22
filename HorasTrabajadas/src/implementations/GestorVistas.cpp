#include "GestorVistas.h"

GestorVistas* GestorVistas::gestor;

GestorVistas* GestorVistas::instanciar()
{
    if (gestor == nullptr)
        gestor = new GestorVistas();
    return gestor;
}

unsigned short GestorVistas::GetVistaActiva()
{
    return menuActivo;
}

void GestorVistas::setVistaPrincipal()
{
    menuActivo = Vistas::VISTA_PRINCIPAL;
}

void GestorVistas::setVistaAgregarActividad()
{
    menuActivo = Vistas::VISTA_AGREGAR_ACTIVIDAD;
}

void GestorVistas::setVistaListaActividades()
{
    menuActivo = Vistas::VISTA_LISTA_ACTIVIDADES;
}

void GestorVistas::setVistaActividad()
{
    menuActivo = Vistas::VISTA_ACTIVIDAD;
}

void GestorVistas::setVistaIngresarTiempo()
{
    menuActivo = Vistas::VISTA_INGRESAR_TIEMPO;
}

void GestorVistas::setVistaListarRegistros()
{
    menuActivo = Vistas::VISTA_LISTAR_REGISTROS;
}

void GestorVistas::setVistaBuscarRegistros()
{
    menuActivo = Vistas::VISTA_BUSCAR_REGISTROS;
}

void GestorVistas::setVistaAgruparRegistros()
{
    menuActivo = Vistas::VISTA_AGRUPAR_REGISTROS;
}

void GestorVistas::setVistaModificarNombreActividad()
{
    menuActivo = Vistas::VISTA_MODIFICAR_NOMBRE_ACTIVIDAD;
}

void GestorVistas::setVistaRegistrosListados()
{
    menuActivo = Vistas::VISTA_REGISTROS_LISTADOS;
}

void GestorVistas::setVistaFiltroID()
{
    menuActivo = Vistas::VISTA_FILTRO_ID;
}

void GestorVistas::setVistaFiltroTiempo()
{
    menuActivo = Vistas::VISTA_FILTRO_TIEMPO;
}

void GestorVistas::setVistaFiltroFecha()
{
    menuActivo = Vistas::VISTA_FILTRO_FECHA;
}

void GestorVistas::setVistaFiltroDescripcion()
{
    menuActivo = Vistas::VISTA_FILTRO_DESCRIPCION;
}

void GestorVistas::setVistaRegistrosBuscados()
{
    menuActivo = Vistas::VISTA_REGISTROS_BUSCADOS;
}

void GestorVistas::cerrarMenu()
{
    menuActivo = 0;
}
