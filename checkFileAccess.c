/*
 * checkfileAccess.c
 *
 *  Created on: 30/03/2015
 *      Author: utnso
 */
/*========================================
Analiza su unArchivo existe
y tiene permiso de lectura
=========================================*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int checkFileAccess (char* unArchivo){
	int rval;

	/* Existe el archivo? */
	rval = access (unArchivo, F_OK);
	if (rval == 0)
	printf ("%s Existe\n", unArchivo);
	else {
		if (errno == ENOENT)
			printf ("%s No Existe\n", unArchivo);
		else if (errno == EACCES)
			printf ("%s No es Accesible\n", unArchivo);
		return 0;
	}

	/* Se puede leer? */
	rval = access (unArchivo, R_OK);
	if (rval == 0)
		printf ("%s tiene permiso de Lectura\n", unArchivo);
	else {
		printf ("%s no tiene permiso de Lectura (access denied)\n", unArchivo);
		return 0;
	}

	return 1;
}


