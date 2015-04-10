/*
 * getDatoInfoConex.c
 *
 *  Created on: 30/03/2015
 *      Author: utnso
 */
/*======================================================================
Obtiene datos de conexion desde el archivo de configuracion, el cual
esta dado por la variable de ambiente ANSISOP_CONFIG_PATH.
===================|===================================================*/

char* getDatoInfoConex(char *cadena, int *idx) {

	char *dato=(char *)malloc(strlen(cadena));
	int i,j;

	j=0;
	for(i=*idx; cadena[i] != '\n' && i < strlen(cadena); i++){
		if(isdigit(cadena[i]) || cadena[i]=='.')
		  dato[j++]=cadena[i];
	}
	dato[j]='\0';
	*idx=++i;
	return dato;

}

