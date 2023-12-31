// test de funcionamiento del sistema de archivos

#include <stdio.h>
#include <string.h>
#include "arch.h"



int main(void){
    // creación del directorio raíz del sistema
    struct Dir home;
    home.nombre = "Home";
    home.permisos = 0b111111; // ejemplo de la declaración de los permisos del directorio

    struct Dir* aux = &home; // puntero auxiliar que nos permitirá usar el sistema de archivos

    enum STATUS estado;

    estado = mkdir(aux , "dante");

    printf("estado: %d \n" , estado);

    return 0;
}