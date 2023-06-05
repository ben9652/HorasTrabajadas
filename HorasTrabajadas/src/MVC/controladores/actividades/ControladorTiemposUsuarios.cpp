#include "ControladorTiemposUsuarios.h"
#include <iostream>
#include <stdlib.h>
#include <ConnectionException.h>

ControladorTiemposUsuarios::ControladorTiemposUsuarios(Actividad&& _actividad)
{
	conector = GestorConexion::instanciar();
	actividad = new Actividad();
	actividad = &_actividad;

	vista = new VistaTiemposUsuarios();

	ejecutarLogica();
}

void ControladorTiemposUsuarios::ejecutarLogica()
{
	system("cls");
	TextTable t('-', '|', '+');
	t.add("Usuario");
	t.add("Tiempo trabajado");
	t.endOfRow();

	sql::PreparedStatement* pstmt;
	try
	{
		pstmt = conector->prepareStatement("CALL TiempoTotalUsuarioActividad(?)");
		pstmt->setInt(1, actividad->getIdActividad());
		pstmt->execute();
	}
	catch (ConnectionException e)
	{
		std::cout << e.what() << std::endl;
		std::cin.get();
		return;
	}

	do
	{
		sql::ResultSet* res = pstmt->getResultSet();
		while (res->next())
		{
			t.add(res->getString(1));

			unsigned int segundosConsumidos = res->getUInt(2);
			unsigned int horasInt = segundosConsumidos / 3600;
			unsigned int minutosInt = segundosConsumidos % 3600;
			unsigned int segundosInt = minutosInt % 60;
			minutosInt /= 60;

			char* tiempo = (char*)malloc(60);
			memset(tiempo, 0, 60);

			if (segundosConsumidos == 0)
				strcat_s(tiempo, 60, "0s");

			if (horasInt != 0)
			{
				char* horas = (char*)malloc(20);
				_itoa_s(horasInt, horas, 20, 10);
				strcat_s(tiempo, 60, horas);
				strcat_s(tiempo, 60, "h ");
			}

			if (minutosInt != 0)
			{
				char* minutos = (char*)malloc(20);
				_itoa_s(minutosInt, minutos, 20, 10);
				strcat_s(tiempo, 60, minutos);
				strcat_s(tiempo, 60, "m ");
			}

			if (segundosInt != 0)
			{
				char* segundos = (char*)malloc(20);
				_itoa_s(segundosInt, segundos, 20, 10);
				strcat_s(tiempo, 60, segundos);
				strcat_s(tiempo, 60, "s");
			}

			t.add(tiempo);
			t.endOfRow();
		}
		delete res;
	} while (pstmt->getMoreResults());

	delete pstmt;

	std::cout << t << std::endl;

	vista->ingresar_opcion_salir(1);
}
