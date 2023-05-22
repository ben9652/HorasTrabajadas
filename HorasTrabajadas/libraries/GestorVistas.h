#ifndef __GESTOR_VISTAS_
#define __GESTOR_VISTAS_

class GestorVistas
{
private:
	static GestorVistas* gestor;

	unsigned short menuActivo;

	GestorVistas()
	{
		menuActivo = 0;
	}
public:
	enum Vistas
	{
		VISTA_PRINCIPAL = 1 << 0,
		VISTA_AGREGAR_ACTIVIDAD = 1 << 1,
		VISTA_LISTA_ACTIVIDADES = 1 << 2,
		VISTA_ACTIVIDAD = 1 << 3,
		VISTA_INGRESAR_TIEMPO = 1 << 4,
		VISTA_LISTAR_REGISTROS = 1 << 5,
		VISTA_BUSCAR_REGISTROS = 1 << 6,
		VISTA_AGRUPAR_REGISTROS = 1 << 7,
		VISTA_MODIFICAR_NOMBRE_ACTIVIDAD = 1 << 8,
		VISTA_REGISTROS_LISTADOS = 1 << 9,
		VISTA_FILTRO_ID = 1 << 10,
		VISTA_FILTRO_TIEMPO = 1 << 11,
		VISTA_FILTRO_FECHA = 1 << 12,
		VISTA_FILTRO_DESCRIPCION = 1 << 13,
		VISTA_REGISTROS_BUSCADOS = 1 << 14
	};

	static GestorVistas* instanciar();

	unsigned short GetVistaActiva();

	void setVistaPrincipal();
	void setVistaAgregarActividad();
	void setVistaListaActividades();
	void setVistaActividad();
	
	// Lo que sigue est� dentro de MenuActividad

	void setVistaIngresarTiempo();
	void setVistaListarRegistros();
	void setVistaBuscarRegistros();
	void setVistaAgruparRegistros();
	void setVistaModificarNombreActividad();

	// Aqu� se ver�n los registros listados desde una opci�n del men� ListarRegistros
	void setVistaRegistrosListados();

	// Aqu� se ver�n las opciones de un registro seleccionado
	void setVistaRegistro();
	
	void setVistaModificarTiempo();
	void setVistaModificarDescripcion();
	void setVistaEliminarRegistro();

	// Opci�n del filtro por ID, a la que se entra por medio del men� BuscarRegistros
	void setVistaFiltroID();
	// Opci�n del filtro por tiempo, a la que se entra por medio del men� BuscarRegistros
	void setVistaFiltroTiempo();
	// Opci�n del filtro por fecha, a la que se entra por medio del men� BuscarRegistros
	void setVistaFiltroFecha();
	// Opci�n del filtrado por descripci�n, a la que se entra por medio del men� BuscarRegistros
	void setVistaFiltroDescripcion();
	// Aqu� se ver�n los registros listados desde un filtro puesto en BuscarRegistros
	void setVistaRegistrosBuscados();

	void cerrarMenu();
};

#endif