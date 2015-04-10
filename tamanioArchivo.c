/*
 * tamanioArchivo.c
 *
 *  Created on: 30/03/2015
 *      Author: utnso
 */
/*===========================================
Obtiene el tama�de un archivo
===========================================*/
#include <fcntl.h>
#include <stdlib.h>

size_t tamanioArchivo(const char* unArchivo){

	int fd;
	size_t tamanio;
	struct stat file_info;

	fd = open (unArchivo, O_RDONLY);
	fstat (fd, &file_info);
	close(fd);
        return (tamanio = file_info.st_size);
}

