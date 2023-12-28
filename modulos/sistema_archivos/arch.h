#ifndef ARCH_H_INCLUDE



#define MAX_CONTENIDO 2000
#define MAX_NOMBRE 20

enum STATUS{NOT_EMPTY , ALREADY_EXIST , ALREADY_EMPTY , NOT_FOUND , UNREACHABLE , NOT_FILES , NOT_DIRS , SUCCESFULL};  // posibles errores que puede devolver cuando se intenten hacer operaciones no válidas

// funciones para carpetas

int mkdir(struct  Dir* carpeta , char nombre[MAX_NOMBRE]);

int rmdir(struct Dir* carpeta , char nombre[MAX_NOMBRE]);

int cd (struct Dir* carpeta , char nombre[MAX_NOMBRE]);

int back(struct Dir* carpeta);

int ls(struct Dir* carpeta);

// funciones para archivos

int touch(struct Dir* carpeta , char nombre[MAX_NOMBRE]);

int rmfile(struct Dir* carpeta , char nombre[MAX_NOMBRE]);



#endif