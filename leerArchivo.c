/*
 * leerArchivo.c
 *
 *  Created on: 30/03/2015
 *      Author: utnso
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <ctype.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include "leerArchivo.h"
/*===================================================================================
	Lee el contenido de unArchivo y lo guarda en buffer. El tamanio de
	buffer se guarda en length, el cual es un puntero.
	La funcion retorna un buffer, que debe ser liberado (free) desde la
	funcion invocante.
===================================================================================*/
char* leerArchivo (const char* unArchivo, size_t length) {
	int fd;
	struct stat file_info;
	char* buffer;

	/* Abrir el archivo y asignarlo a un FD */
	fd = open (unArchivo, O_RDONLY);

	/* Obtener info del archivo: tamanio */
	fstat (fd, &file_info);
	//*length = file_info.st_size;

	/* Asegurarse que el archivo es "legible" (o Regular).
	Caso contrario cierra el FD y devuelve NULL */
	if (!S_ISREG (file_info.st_mode)) {
		close (fd);
		return NULL;
	}

	buffer = (char*) malloc (length);
	//memset(buffer, '\0', length);
	read (fd, buffer, length);

	close (fd);
	return buffer;
}

