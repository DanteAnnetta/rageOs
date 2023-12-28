#include <string.h>
#include <stdbool.h>
#include "arch.h"

// constantes de los límites en los nombres y en el contenido de los archivos





// para este primer modelado se utilizará un archivo para almacenar todo el contenido de los archivos

struct File{
    int permisos;  // para comodidad en la instanciación, estos se escribirán en binario "0b000000", trabajando de a pares leer- escribir correspondientes a grupo-usuario-todos
    char nombre[MAX_NOMBRE];
    char cont[MAX_CONTENIDO];
};

//-------------------------------------------------------------------INICIO FUNCIONES PARA LISTA DE ARCHIVOS------------------------------------------------------------

struct Nodo {
    struct File dato;
    struct Nodo* sig;
};

int criterioArchivo(struct File archivo1 , struct File archivo2){
    return strcmp(archivo1.nombre , archivo2.nombre);
}

// estas funciones necesitan que se les pase el valor del puntero, no el puntero 
void insertar(struct File archivo , struct Nodo * Lista){
    struct Nodo* nuevo;
    nuevo->dato = archivo;

    struct Nodo** pp = & Lista;
    while (*pp != NULL && criterioArchivo(nuevo->dato , (*pp)->dato) >= 0){
        pp  =&((*pp)->sig);
    }
    nuevo->sig = *pp;
    *pp = nuevo;
}

// esta función, en conjunto con la anterior se utilizarán para realizar movimientos dentro del sistema de archivos
struct Nodo* extraer(struct File archivo, struct Nodo* Lista){
    struct Nodo* aux;
    struct Nodo **pp = & Lista;

    while (*pp != NULL && criterioArchivo(archivo , (*pp)->dato) > 0){
        pp = &((*pp)->sig);
    }

    if(*pp != NULL && criterioArchivo(archivo , (*pp)->dato) == 0){
        aux = *pp;
        *pp = (*pp)->sig;
        return aux;
    }
    else{
        return NULL;
    }
}

bool borrar(struct File archivo , struct Nodo* Lista){
    struct Nodo* ext = extraer(archivo , &Lista);
    if(ext){
        free(ext);
        return true;
    }
    else{
        return false;
    }
}
// Hasta esta función, todas las de manipulación de la lista de archivos necesitan que el parámetro de la lista se pase como valor del puntero y no como puntero

struct Nodo* buscar(struct File archivo , struct Nodo* Lista){
    while (Lista!= NULL && criterioArchivo(archivo , Lista->dato) > 0){
        Lista = Lista->sig;
    }

    if(Lista != NULL && criterioArchivo(archivo , Lista->dato) == 0){
        return Lista;
    }
    else{
        return NULL;
    }
}

// ---------------------------------------------------FIN DE FUNCIONES PARA LISTA DE ARCHIVOS-------------------------------------------------------------


//----------------------------------------------------FUNCIONES PARA LA GESTIÓN DE LOS DIRECTORIOS-------------------------------------------------------

struct Dir{
    int permisos;
    char nombre[MAX_NOMBRE];
    struct Dir* sup;
    struct Dir* izq;
    struct Dir* inf;
    struct Nodo* files;  // lista de archivos que contiene cada uno de los directorios
};


// al llamar a las funciones:  modificarValor(&x);

int mkdir(struct  Dir* carpeta , char nombre[MAX_NOMBRE]){
    enum STATUS estado = SUCCESFULL;  // a no ser que haya errores, el estado predeterminado es de éxito
    struct Dir* nuevo;
    nuevo->sup = carpeta;  // la carpeta de la que proviene
    memcpy(nuevo->nombre, nombre, sizeof(char) * MAX_NOMBRE);
    nuevo->permisos = carpeta->permisos;  // a no ser que se modifiquen, las carpetas creadas mantendrán los mismos permisos que las heredadas

    if(carpeta->inf){  // si tiene otras carpetas dentro de esta, las recorre hasta llegar a la última y agrega la misma dentro del 
        struct Dir* aux = carpeta->inf;
        while(aux->izq){
            if(strcmp(aux->nombre , nombre)== 0){  // si el nombre ya existe, devuelve el error ALREADY_EXIST
                estado = ALREADY_EXIST;
                break;
            }
            aux = aux->izq;
        }
        if(estado == SUCCESFULL){  // si no existe una carpeta con este nombre, la puede crear perfectamente 
            aux->izq = nuevo;
        }
        
    }
    else{
        carpeta->inf = nuevo;
    }
    return estado;
}

bool isEmpty(struct Dir* carpeta){
    if(carpeta->inf == NULL && carpeta->files == NULL){   // está vacía siempre que no tenga ni carpetas ni archivos dentro
        return true;
    }
    else{
        return false;
    }
}

int rmdir(struct Dir* carpeta , char nombre[MAX_NOMBRE]){
    enum STATUS estado = SUCCESFULL;

    if(carpeta->inf == NULL){// si donde se quiere eliminar una carpeta ya de inicio no hay ninguna salta este error
        estado = ALREADY_EMPTY;
    }
    else{
        bool flag = false;
        struct Dir* iter = carpeta->inf;
        struct Dir* aux;
        while(iter->izq){
            aux = iter;
            if(strcmp(iter->nombre , nombre)== 0){  // cuando encuentra la carpeta deseada
                flag = true;
                break;
            }
            iter = iter->izq;
        }
        if (flag == false){ // si entre las carpetas no encuentra la que se eliminará, devuelve este estado
            estado = NOT_FOUND;
        }
        else{
            if(isEmpty(iter)){// si la carpeta no tiene nada adentro se elimina de la lista de carpetas hijas
                aux->izq = iter->izq; // se aisla al puntero correspondiente a la carpeta y luego se elimina
                free(iter);
            }
            else{
                estado = NOT_EMPTY;  // caso contrario devuelve este error
            }
        }
    }

    return estado;
}



int cd (struct Dir* carpeta , char nombre[MAX_NOMBRE]){
    enum STATUS estado = SUCCESFULL;
    if(carpeta->inf == NULL){// si donde se quiere eliminar una carpeta ya de inicio no hay ninguna salta este error
        estado = ALREADY_EMPTY;
    }
    else{
        bool flag = false;
        struct Dir* iter = carpeta->inf;
        while (iter->izq){
            if(strcmp(iter->nombre , nombre)== 0){  // cuando encuentra la carpeta deseada
                flag = true;
                break;
            }
            iter = iter->izq;
        }
        if (flag == false){ // si entre las carpetas no encuentra devuelve este estado
            estado = NOT_FOUND;
        }
        else{
            carpeta = iter;  // caso contrario, cambia la dirección del puntero a la nueva carpeta
        }
        
    }
}

int back(struct Dir* carpeta){
    enum STATUS estado = SUCCESFULL;
    if(carpeta->sup == NULL){ // en caso de que no pueda subir más carpetas devuelve este estado
        estado = UNREACHABLE;
    }
    else{
        carpeta = carpeta->sup;
    }

    return estado;
}

//------------------------------------------------------------------FUNCIONES PARA MANIPULACIÓN DE ARCHIVOS-------------------------------------------------------------

// enum STATUS{SUCCESFULL ,NOT_EMPTY , ALREADY_EXIST , ALREADY_EMPTY , NOT_FOUND , UNREACHABLE};

// función para crear un archivo dentro del directorio actual
int touch(struct Dir* carpeta , char nombre[MAX_NOMBRE]){
    enum STATUS estado = SUCCESFULL;
    struct File nuevo;
    memcpy(nuevo.nombre, nombre, sizeof(char) * MAX_NOMBRE);

    if(buscar(nuevo , carpeta->files)!= NULL){ // Si encuentra un archivo con ese nombre dentro de la carpeta devuelve este estado y cancela la creación del archivo
        estado = ALREADY_EXIST;
    }
    else{
        insertar(nuevo , &carpeta->files);
    }


    return estado;
}

int rmfile(struct Dir* carpeta , char nombre[MAX_NOMBRE]){
    enum STATUS estado = SUCCESFULL;
    struct File nuevo;
    memcpy(nuevo.nombre, nombre, sizeof(char) * MAX_NOMBRE);

    if(buscar(nuevo , carpeta->files)== NULL){ // Si no encuentra archivos devuelve este estado
        estado = NOT_FOUND;
    }
    else{
        borrar(nuevo , &carpeta->files); // elimina el archivo de la carpeta
    }
    return estado;
}