/*
 * ansisopPatch.c
 *
 *  Created on: 30/03/2015
 *      Author: utnso
 */

/*=========================================================
Cargo el path del archivo de configuracion
referenciado en variable de entorno
ANSISOP_CONFIG
=========================================================*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>


char* ansisopPath (char* nombreVariable){
	char *unPath;
	if ((unPath = getenv(nombreVariable))==NULL){
		printf("%s no existe como variable de entoron\n",nombreVariable);
		printf("Exit 1\n");
		exit (1);
	}

	if (checkFileAccess(unPath))
		return unPath;
	else
		return NULL;
}

