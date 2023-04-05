#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct usuario{
    char rut[11];
    char nombre[100];
    int edad;
};

typedef struct usuario tUsuario;


void leeArchivo(){
    char nombreArchivo[30], nombreArchivoSalida[30], linea[150];
    printf("Ingresa el nombre del archivo: ");

    fgets(nombreArchivo, 50, stdin);
    strtok(nombreArchivo, "\n");

    FILE *archivo = fopen(nombreArchivo, "r");

    if (archivo == NULL ){
        printf("Archivo invalido o no encontrado, cerrando el programa.");
        exit(-1);
    }

    strcpy(nombreArchivoSalida, nombreArchivo);
    strtok(nombreArchivoSalida, ".");
    strcat(nombreArchivoSalida, ".sal");
    FILE *archivoSalida = fopen(nombreArchivoSalida, "w");

    while (fgets(linea, sizeof(linea), archivo)) {
        if (linea[0] == "\n") continue;
        char *rut;
        char *nombre;
        char *cadena;
        int edad;
        strtok(linea, "\n");
        rut = strtok(linea, ",");
        nombre = strtok(NULL, ",");
        cadena = strtok(NULL, ",");
        edad = atoi(cadena);
        if ( rut == NULL || nombre == NULL || edad == NULL) continue;
        printf("Rut: %11s nombre: %20s             edad: %i\n", rut, nombre, edad);
        fprintf(archivoSalida,"Rut: %11s nombre: %20s             edad: %i\n", rut, nombre, edad);

    }


    fclose(archivo);
    fclose(archivoSalida);






}

int main(){
    leeArchivo();
    return 0;
}
