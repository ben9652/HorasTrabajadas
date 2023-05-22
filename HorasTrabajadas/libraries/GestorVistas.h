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
	
	// Lo que sigue está dentro de MenuActividad

	void setVistaIngresarTiempo();
	void setVistaListarRegistros();
	void setVistaBuscarRegistros();
	void setVistaAgruparRegistros();
	void setVistaModificarNombreActividad();

	// Aquí se verán los registros listados desde una opción del menú ListarRegistros
	void setVistaRegistrosListados();

	// Aquí se verán las opciones de un registro seleccionado
	void setVistaRegistro();
	
	void setVistaModificarTiempo();
	void setVistaModificarDescripcion();
	void setVistaEliminarRegistro();

	// Opción del filtro por ID, a la que se entra por medio del menú BuscarRegistros
	void setVistaFiltroID();
	// Opción del filtro por tiempo, a la que se entra por medio del menú BuscarRegistros
	void setVistaFiltroTiempo();
	// Opción del filtro por fecha, a la que se entra por medio del menú BuscarRegistros
	void setVistaFiltroFecha();
	// Opción del filtrado por descripción, a la que se entra por medio del menú BuscarRegistros
	void setVistaFiltroDescripcion();
	// Aquí se verán los registros listados desde un filtro puesto en BuscarRegistros
	void setVistaRegistrosBuscados();

	void cerrarMenu();
};

#endif