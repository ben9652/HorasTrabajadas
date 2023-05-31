#include "ControladorAccionBReg.h"
#include "ControladorFiltroID.h"
#include "ControladorFiltroTiempo.h"
#include "ControladorFiltroFecha.h"
#include "ControladorFiltroDescr.h"
#include "ControladorRegistro.h"
#include "GestorConexion.h"
#include <unordered_map>
#include "common.h"

ControladorAccionBReg::ControladorAccionBReg(Actividad&& _modelo)
{
	vista = new VistaAccionBReg();
	modelo = new Actividad();
	*modelo = _modelo;

	ejecutarLogica();
}

ControladorAccionBReg::~ControladorAccionBReg()
{
	delete vista;
}

void ControladorAccionBReg::ejecutarLogica()
{
	do
	{
		indices_registros_encontrados.clear();

		vista->limpiar();
		vista->limpiarTabla();

		GestorConexion* gc = GestorConexion::instanciar();
		GestorRegistros* gr = GestorRegistros::instanciar();
		sql::PreparedStatement* pstmt = hacerBusqueda();
		sql::ResultSet* res;

		int IDMaximo = 0;
		try {
			res = pstmt->executeQuery();
			while (res->next())
			{
				int idRegistro = res->getInt(1);
				indices_registros_encontrados[idRegistro] = 0;
				if (idRegistro > IDMaximo) IDMaximo = idRegistro;
				Registro& r = gr->obtenerRegistroPorId(idRegistro, modelo->getIdActividad());
				vista->addFila(r.getIdRegistroString(), r.getSegundosConsumidosString(), r.getFechaCreacionString(), r.getDescripcion());
			}
			while (pstmt->getMoreResults())
				res = pstmt->getResultSet();
		}
		catch (sql::SQLException e) {
			const char* error = e.what();
			vista->mostrar(error);
			vista->ingresar(0);
		}

		delete pstmt;
		pstmt = verificarNoErrores();
		res = pstmt->executeQuery();
		res->next();
		sql::SQLString mensaje = res->getString(1);
#ifdef FUNCIONA_CHARACTER_SET_LATIN
		if(mensaje == "B�squeda exitosa")
#else
		if (!strcmp(utf8_to_ascii(mensaje.c_str()), "B�squeda exitosa"))
#endif
		{
			vista->mostrar(mensaje.c_str());
			vista->ingresar(0);
			return;
		}
		mostrarCursor(false);

		vista->mostrarTabla();
		vista->mostrar("\n");

		size_t digitosIDMaximo;
		for (digitosIDMaximo = 0; IDMaximo != 0; IDMaximo /= 10)
			digitosIDMaximo++;

		COORD posicionActual = posicionActualCursor();

		do
		{
			vista->irXY(posicionActual.X, posicionActual.Y);
			vista->mostrar("A continuaci�n, puede ingresar alg�n ID para acceder a un registro en particular: ");
			for (int i = 0; i < digitosIDMaximo; i++)
				vista->mostrar(" ");
			for (int i = 0; i < digitosIDMaximo; i++)
				vista->mostrar("\b");
			mostrarCursor(true);
			char* resultado = vista->ingresar_opcion_salir(digitosIDMaximo);

			if (resultado[0] == 0x1B)
				return;

			if (!es_numero(resultado))
				continue;

			int ID = atoi(resultado);
			try {
				int& temp = indices_registros_encontrados.at(ID);
			}
			catch (std::out_of_range e) {
				continue;
			}

			Registro& r = gr->obtenerRegistroPorId(ID, modelo->getIdActividad());

			if (r.esRegistroNulo())
				continue;

			ControladorRegistro cr(std::move(r), std::move(*modelo));
			break;

		} while (true);

	} while (true);
}

sql::PreparedStatement* ControladorAccionBReg::hacerBusqueda()
{
	ControladorFiltroID cfid;
	ControladorFiltroTiempo cft;
	ControladorFiltroFecha cff;
	ControladorFiltroDescr cfd;

	GestorConexion* gc = GestorConexion::instanciar();
	sql::PreparedStatement* pstmt = gc->prepareStatement("CALL BuscarRegistros(?,?,?,?,?,?,?,?,?,@m)");

	if (cfid.hayFiltro())
		pstmt->setInt(1, cfid.getFiltro());
	else
		pstmt->setNull(1, sql::DataType::INTEGER);

	pstmt->setInt(2, modelo->getIdActividad());

	if (cft.getCriterio() == ControladorFiltroTiempo::SIN_CRITERIO)
		pstmt->setNull(3, sql::DataType::VARCHAR);
	else if (cft.getCriterio() == ControladorFiltroTiempo::IGUAL)
		pstmt->setString(3, "=");
	else if (cft.getCriterio() == ControladorFiltroTiempo::MENOR)
		pstmt->setString(3, "<");
	else if (cft.getCriterio() == ControladorFiltroTiempo::MENOR_O_IGUAL)
		pstmt->setString(3, "<=");
	else if (cft.getCriterio() == ControladorFiltroTiempo::MAYOR)
		pstmt->setString(3, ">");
	else if (cft.getCriterio() == ControladorFiltroTiempo::MAYOR_O_IGUAL)
		pstmt->setString(3, ">=");
	else
		pstmt->setString(3, "><");

	if (cft.hayFiltro())
		pstmt->setUInt(4, cft.getTiempoFiltroInicio());
	else
		pstmt->setNull(4, sql::DataType::INTEGER);

	if (cft.hayFiltro())
		pstmt->setUInt(5, cft.getTiempoFiltroFin());
	else
		pstmt->setNull(5, sql::DataType::INTEGER);

	if (cff.getCriterio() == ControladorFiltroFecha::SIN_CRITERIO)
		pstmt->setNull(6, sql::DataType::VARCHAR);
	else if (cff.getCriterio() == ControladorFiltroFecha::IGUAL)
		pstmt->setString(6, "=");
	else if (cff.getCriterio() == ControladorFiltroFecha::MENOR)
		pstmt->setString(6, "<");
	else if (cff.getCriterio() == ControladorFiltroFecha::MENOR_O_IGUAL)
		pstmt->setString(6, "<=");
	else if (cff.getCriterio() == ControladorFiltroFecha::MAYOR)
		pstmt->setString(6, ">");
	else if (cff.getCriterio() == ControladorFiltroFecha::MAYOR_O_IGUAL)
		pstmt->setString(6, ">=");
	else
		pstmt->setString(6, "><");

	if (cff.hayFiltro())
		pstmt->setDateTime(7, cff.getFiltroFechaInicio());
	else
		pstmt->setNull(7, sql::DataType::DATE);

	if (cff.hayFiltro())
		pstmt->setDateTime(8, cff.getFiltroFechaFin());
	else
		pstmt->setNull(8, sql::DataType::DATE);

	if (cfd.hayFiltro())
		pstmt->setString(9, cfd.getFiltro());
	else
		pstmt->setNull(9, sql::DataType::VARCHAR);

	return pstmt;
}

sql::PreparedStatement* ControladorAccionBReg::verificarNoErrores()
{
	GestorConexion* gc = GestorConexion::instanciar();
	sql::PreparedStatement* pstmt = gc->prepareStatement("SELECT @m");
	
	return pstmt;
}