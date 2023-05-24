#include "VistaListarRegistros.h"
#include "common.h"

void VistaListarRegistros::mostrarRegistro(const char* ID, const char* tiempoConsumido, const char* fechaCreacion, const char* descripcion)
{
	fprintf(stdout, "\033[38;5;%dm%s\033[m%s%c", 226, "ID: ", ID, '\n');
	fprintf(stdout, "\033[38;5;%dm%s\033[m%s%c", 182, "Tiempo consumido: ", tiempoConsumido, '\n');
	fprintf(stdout, "\033[38;5;%dm%s\033[m%s%c", 202, "Fecha de creación: ", fechaCreacion, '\n');
	fprintf(stdout, "\033[38;5;%dm%s\033[m%s%c", 201, "Descripción\n", formatear_texto(descripcion), '\n');
}

const char* VistaListarRegistros::formatear_texto(const char* input) {
	int len = (int)strlen(input);
	char* output = (char*)malloc(DESCRIPTION_SIZE * sizeof(char)); // resultado final
	int char_count = 0; // cuenta los caracteres en la línea actual
	int word_len = 0; // longitud de la palabra actual
	int last_space = -1; // la posición del último espacio
	int output_len = 0; // longitud de la cadena de salida

	for (int i = 0; i <= len; i++)
	{
		// si es un espacio, o el final de la línea
		if (input[i] == ' ' || input[i] == '\0' || input[i] == '\n')
		{
			// si la adición de esta palabra superaría el límite de la línea
			if (char_count + word_len > 50 && last_space != -1)
			{
				output[last_space] = '\n'; // inserta un salto de línea en el último espacio
				char_count = i - last_space; // calcula la longitud de la nueva línea
			}
			else
				char_count += word_len + 1; // suma la longitud de la palabra y el espacio al conteo de caracteres
			output[output_len] = input[i];
			output_len++;
			last_space = output_len - 1;
			word_len = 0; // restablecer la longitud de la palabra
		}
		else
		{
			// agrega el carácter a la palabra actual
			output[output_len] = input[i];
			output_len++;
			word_len++;
		}
	}
	output[output_len] = '\0'; // asegurarse de que la cadena de salida esté terminada
	return output;
}