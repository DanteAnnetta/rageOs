#ifndef ARCH_H_INCLUDE



#define MAX_CONTENIDO 2000
#define MAX_NOMBRE 20
enum errores{IS_NOT_EMPTY , ALREADY_EXIST};  // errores que pueden devolver el llamado de las funciones 

int mkdir(struct  Dir* carpeta , char nombre[MAX_NOMBRE]);





#endif