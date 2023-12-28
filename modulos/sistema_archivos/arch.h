#ifndef ARCH_H_INCLUDE
// para este primer modelado se utilizará un archivo para almacenar todo el contenido de los archivos

// constantes de los límites en los nombres y en el contenido de los archivos


#define MAX_CONTENIDO 2000
#define MAX_NOMBRE 20

// declaración de estructuras necesarias para el sistema
struct File{
    int permisos;  // para comodidad en la instanciación, estos se escribirán en binario "0b000000", trabajando de a pares leer- escribir correspondientes a grupo-usuario-todos
    char nombre[MAX_NOMBRE];
    char cont[MAX_CONTENIDO];
};

struct Nodo {
    struct File dato;
    struct Nodo* sig;
};

struct Dir{
    int permisos;
    char nombre[MAX_NOMBRE];
    struct Dir* sup;
    struct Dir* izq;
    struct Dir* inf;
    struct Nodo* files;  // lista de archivos que contiene cada uno de los directorios
};



enum STATUS{NOT_EMPTY , ALREADY_EXIST , ALREADY_EMPTY , NOT_FOUND , UNREACHABLE , NOT_FILES , NOT_DIRS , SUCCESFULL};  // posibles errores que puede devolver cuando se intenten hacer operaciones no válidas

// funciones para carpetas

int mkdir(struct  Dir* carpeta , char nombre[MAX_NOMBRE]);

int rmdir(struct Dir* carpeta , char nombre[MAX_NOMBRE]);

int cd (struct Dir* carpeta , char nombre[MAX_NOMBRE]);

int back(struct Dir* carpeta);

int ls(struct Dir* carpeta);

// DESARROLLAR ESTAS FUNCIONALIDADES

int chmod(struct Dir* carpeta, int permisos);

int pwd(struct Dir* carpeta);

// funciones para archivos

int touch(struct Dir* carpeta , char nombre[MAX_NOMBRE]);

int rmfile(struct Dir* carpeta , char nombre[MAX_NOMBRE]);

// agregar funciones de persistencia únicamente (load y save)

#endif