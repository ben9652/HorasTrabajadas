#include "GestorDatos.h"

GestorDatos* GestorDatos::gestor;

GestorDatos* GestorDatos::instanciar()
{
	if (gestor == nullptr)
		gestor = new GestorDatos();
	return gestor;
}

size_t GestorDatos::getDatosTotales()
{
	return datos_totales;
}

size_t GestorDatos::getDatosTomados()
{
	return datos_tomados;
}

unsigned char GestorDatos::porcentajeDatosTomados()
{
	float x = datos_tomados * 100 / (float)datos_totales;
	return (unsigned char)x;
}

void GestorDatos::asignarCantidadActividadesEnBD(size_t cantidadActividades)
{
	if (datos_totales < cantidad_actividades_en_bd)
		datos_totales = cantidadActividades + cantidad_registros_en_bd;
	else
		datos_totales -= cantidad_actividades_en_bd;
	datos_totales += cantidadActividades;
	cantidad_actividades_en_bd = cantidadActividades;
}

void GestorDatos::asignarCantidadRegistrosEnBD(size_t cantidadRegistros)
{
	if (datos_totales < cantidad_registros_en_bd)
		datos_totales = cantidadRegistros + cantidad_actividades_en_bd;
	else
		datos_totales -= cantidad_registros_en_bd;
	datos_totales += cantidadRegistros;
	cantidad_registros_en_bd = cantidadRegistros;
}

void GestorDatos::asignarCantidadActividades(size_t cantidadActividades)
{
	if (datos_tomados < actividades_tomadas)
		datos_tomados = cantidadActividades + registros_tomados;
	else
		datos_tomados -= actividades_tomadas;
	datos_tomados += cantidadActividades;
	actividades_tomadas = cantidadActividades;
}

void GestorDatos::asignarCantidadRegistros(size_t cantidadRegistros)
{
	if (datos_tomados < registros_tomados)
		datos_tomados = cantidadRegistros + actividades_tomadas;
	else
		datos_tomados -= registros_tomados;
	datos_tomados += cantidadRegistros;
	registros_tomados = cantidadRegistros;
}

void GestorDatos::agregar_ActividadEnBD()
{
	datos_totales++;
	cantidad_actividades_en_bd++;
}

void GestorDatos::agregar_RegistroEnBD()
{
	datos_totales++;
	cantidad_registros_en_bd++;
}

void GestorDatos::tomarActividad()
{
	datos_tomados++;
	actividades_tomadas++;
}

void GestorDatos::tomarRegistro()
{
	datos_tomados++;
	registros_tomados++;
}

void GestorDatos::eliminar_ActividadEnBD()
{
	if(datos_totales > 0)
		datos_totales--;
	if(cantidad_actividades_en_bd > 0)
		cantidad_actividades_en_bd--;
}

void GestorDatos::eliminar_RegistroEnBD()
{
	if(datos_totales > 0)
		datos_totales--;
	if(cantidad_registros_en_bd > 0)
		cantidad_registros_en_bd--;
}

size_t GestorDatos::obtenerCantidadActividadesEnBD()
{
	return cantidad_actividades_en_bd;
}

size_t GestorDatos::obtenerCantidadRegistrosEnBD()
{
	return cantidad_registros_en_bd;
}

size_t GestorDatos::obtenerCantidadActividades()
{
	return actividades_tomadas;
}

size_t GestorDatos::obtenerCantidadRegistros()
{
	return registros_tomados;
}
