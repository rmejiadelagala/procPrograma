/*
 * programa.c
 *
 *  Created on: 30/03/2015
 *      Author: utnso
 */

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <ctype.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include "ansisopPath.h"
#include "leerArchivo.h"
#include "tamanioArchivo.h"
#include <commons/config.h>
#include <commons/string.h>

#define MAXDATASIZE 100 // m�ximo n�mero de bytes que se pueden leer de una vez


/*=====================
Estructuras
=====================*/
typedef struct {
    int size;
    char* codigoAnsiSop;
}nodo;


/*======================================================================

FUNCION PRINCIPAL

===================|===================================================*/

int main (int argc, char* argv[]) {

    nodo unPaquete;
    char *datoIP;
    char *datoPort;
	char *ansisop_config = ansisopPath("ANSISOP_CONFIG");

	int sockfd,numbytes;
    char buf[MAXDATASIZE];
    struct sockaddr_in dest_addr; // informacion de la direcci�n de destino

    t_config* arch_config=config_create(ansisop_config);
	if (!config_has_property(arch_config,"IP")){
		printf("Error: No existe el dato IP en arch configuracion");
		return 2;
	}
	if (!config_has_property(arch_config,"PORT")){
		printf("Error: No existe el dato PORT en arch configuracion");
		return 2;
	}
	datoIP=config_get_string_value(arch_config,"IP");
	datoPort=config_get_string_value(arch_config,"PORT");

	printf("IP es %s\n",datoIP);
	printf("Port es %s\n",datoPort);

	if (argc < 2){
	printf("Se espera un nombre de archivo como parametro.\n");
	return 3;
	}

	unPaquete.size = tamanioArchivo(argv[1]);
	unPaquete.codigoAnsiSop = (char*) malloc (unPaquete.size);
	unPaquete.codigoAnsiSop = leerArchivo(argv[1],unPaquete.size);

        /*Empezamos a conectarnos */
	sockfd = socket(AF_INET, SOCK_STREAM, 0); // �Comprueba errores!
        dest_addr.sin_family = AF_INET;          // Ordenaci�n de m�quina
        dest_addr.sin_port = htons(atoi(datoPort));   // short, Ordenaci�n de la red
        dest_addr.sin_addr.s_addr = inet_addr(datoIP);
        memset(&(dest_addr.sin_zero), '\0', 8);  // Poner a cero el resto de la estructura
        // no olvides comprobar los errores de connect()!

        if (connect(sockfd, (struct sockaddr *)&dest_addr,
                                              sizeof(struct sockaddr)) == -1) {
            perror("connect");
            exit(1);
        }

        if (send(sockfd, unPaquete.codigoAnsiSop, unPaquete.size , 0) == -1) {
                perror("send");
                close(sockfd);
		exit(1);
	}

	free(unPaquete.codigoAnsiSop);

        while(1){
		if ((numbytes=recv(sockfd, buf, MAXDATASIZE-1, 0)) == -1) {
        	    perror("recv");
	            exit(1);
        	}

	        buf[numbytes] = '\0';

        	printf("%s",buf);
	}

        close(sockfd);
    	free(datoIP);
    	free(datoPort);
    	free(ansisop_config);
	return 0;
}

