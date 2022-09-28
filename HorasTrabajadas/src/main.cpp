#include <iostream>
#include <stdlib.h>
#include <mysql.h>

void finaliza_con_errores(MYSQL* conn)
{
	std::cerr << mysql_error(conn) << std::endl;
	mysql_close(conn);
	std::cin.get();
	exit(1);
}

int main()
{
	MYSQL* conector = mysql_init(NULL);

	if (!conector)
	{
		std::cerr << "Error en la conexi\xa2n con el servidor" << std::endl;
		std::cin.get();
		exit(1);
	}


	conector = mysql_real_connect(conector, "localhost", "root", "facet2108", "HorasTrabajadas", 3306, NULL, 0);
	MYSQL_ROW fila;
	MYSQL_RES* resultado;

	if (mysql_query(conector, (char*)"CALL ListarRegistros(2);"))
		finaliza_con_errores(conector);

	resultado = mysql_store_result(conector);

	while (fila = mysql_fetch_row(resultado))
	{
		std::cout << fila[0] << ", ";
		std::cout << fila[1] << ", ";
		std::cout << fila[2] << ", ";
		std::cout << fila[3] << std::endl;
	}

	std::cin.get();

	return 0;
}