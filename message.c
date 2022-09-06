/*
 * @fileoverview {FileName} se encarga de realizar tareas especificas.
 *
 * @version             1.0
 *
 * @author              Dyson Arley Parra Tilano <dysontilano@gmail.com>
 * Copyright (C) Dyson Parra
 *
 * @History v1.0 --- La implementacion de {FileName} fue realizada el 31/07/2022.
 * @Dev - La primera version de {FileName} fue escrita por Dyson A. Parra T.
 */
#include "message.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <windows.h>

#if (!defined STATIC_LIB_) && (!defined NO_DLL_MAIN_)
/**
 * Entrada principal de la dll (creado si no se indica que es biblioteca estática)
 *
 * @param instance identificador del módulo.
 * @param reason   razón de la llamada.
 * @param reserved argumento reservado.
 * @return {@code TRUE} si se completó exitosamente la llamada, caso contrario {@code FALSE}.
 */
BOOL APIENTRY DllMain(HINSTANCE instance, DWORD reason, LPVOID reserved) {
    /*
     * Evalúa la razón de la llamada a la dll.
     */
    switch (reason) {
        /*
         * Se cargó la dll en el proceso actual.
         */
        case DLL_PROCESS_ATTACH:
            // printf("%s\n", "DLL_PROCESS_ATTACH");
            break;

        /*
         * Se liberó la dll en el proceso actual.
         */
        case DLL_PROCESS_DETACH:
            // printf("%s\n", "DLL_PROCESS_DETACH");
            break;

        /*
         * Se cargó la dll en un nuevo hilo.
         */
        case DLL_THREAD_ATTACH:
            // printf("%s\n", "DLL_THREAD_ATTACH");
            break;

        /*
         * Se liberó la dll en el nuevo hilo.
         */
        case DLL_THREAD_DETACH:
            // printf("%s\n", "DLL_THREAD_DETACH");
            break;
    }

    return TRUE;
}
#endif

/**
 * FIXME: Definición de {@code newMessage}.
 * Agrega un {Message} a una lista de {Message} específicada como parámetro.
 */
LANGUAGE DLLIMPORT CALLING void newMessage(MessageList* list, char* name, char* value) {
    Message* nuevo;                                                     // Declara apuntador a un Message.
    nuevo = (Message*)malloc(sizeof(Message));                          // Reserva espacio en el heap para el Message.
    nuevo->name = (char*)malloc((strlen(name) + 1) * sizeof(char));     // Inicializa name con la cantidad de posiciones del parámetro name.
    nuevo->value = (char*)malloc((strlen(value) + 1) * sizeof(char));   // Inicializa value con la cantidad de posiciones del parámetro value.

    sprintf(nuevo->name, "%s", name);                                   // Copia el parámetro name al campo name de "nuevo".
    sprintf(nuevo->value, "%s", value);                                 // Copia el parámetro value al campo value de "nuevo".
    nuevo->next = NULL;                                                 // Asigna a nuevo su siguiente Message como null.

    if (list->first == NULL) {                                          // Si la lista está vacía.
        list->first = nuevo;                                            // El nuevo Message es el primero de la lista.
        list->last = nuevo;                                             // El nuevo Message es el último de la lista.
    } else {                                                            // Si no está vacía la lista.
        list->last->next = nuevo;                                       // Liga el nuevo Message con el último de la lista.
        list->last = nuevo;                                             // Indica que nuevo es ahora el último Message de la lista.
    }
}

/**
 * FIXME: Definición de {@code setMessageName}.
 * Cambia el campo name de un {Message} por el de un array especificado.
 */
LANGUAGE DLLIMPORT CALLING void setMessageName(Message* aux, char* name) {
    int nameSize = (int)(strlen(name) + 1);                             // Crea entero que tendrá la longitud del array name.

    if (nameSize > (int)(strlen(aux->name) + 1))                        // Si la longitud del nuevo name es mayor que el anterior.
        aux->name = (char*)realloc(aux->name, nameSize * sizeof(char)); // Redimensiona el espacio en el heap del nombre de aux.

    memcpy(aux->name, name, nameSize);                                  // Copia el valor de name en el campo name de aux.
}

/**
 * FIXME: Definición de {@code setMessageValue}.
 * Cambia el campo value de un {Message} por el de un array especificado.
 */
LANGUAGE DLLIMPORT CALLING void setMessageValue(Message* aux, char* value) {
    int valueSize = (int)(strlen(value) + 1);                               // Crea entero que tendrá la longitud del array value.
    if (valueSize > (int)(strlen(aux->value) + 1))                          // Si la longitud del nuevo value es mayor que el anterior.
        aux->value = (char*)realloc(aux->value, valueSize * sizeof(char));  // Redimensiona el espacio en el heap del valor de aux.

    memcpy(aux->value, value, valueSize);                                   // Copia el valor de value en el campo value de aux.
}

/**
 * FIXME: Definición de {@code makeMessageList}.
 * Almacena en una lista de {Message} todos los {Message} del archivo indicado por filePath.
 */
LANGUAGE DLLIMPORT CALLING MessageList* makeMessageList(char* filePath) {
    MessageList* list = (MessageList*)malloc(sizeof(MessageList));  // Crea una lista que tendrá los Message.
    list->first = NULL;                                             // Indica que la lista de Message está vacía.
    int quotation = 0;                                              // Variable usada para contar la cantidad de comillas en cada línea.
    char* name = NULL;                                              // Variable usada para almacenar el nombre de cada Message.
    char* value = NULL;                                             // Variable usada para almacenar el valor de cada Message.

    FILE* fp = fopen(filePath, "r");                                // Abre filePath.
    char line[2000] = "";                                           // Crea array para almacenar cada linea de filePath.

    if (fp != NULL)                                                 // Si fue posible abrir el archivo indicado.
        while (!feof(fp)) {                                         // Recorre todo filePath.
            line[0] = 0;                                            // Pone . al inicio d eline.
            fgets(line, 2000, fp);                                  // Obtiene la siguiente línea del archivo fileName.
            if (line[0] == 0)                                       // Si terminó de recorrer fp.
                break;                                              // Sale del ciclo.

            quotation = 0;                                          // Reinicia quotation.
            for (int i = 0; i < 2000; i++)                          // Recorre la linea.
                if (line[i] == '\"') {                              // Si encentra comillas.
                    quotation++;                                    // Aumenta la cantidad de comillas.
                    switch (quotation) {                            // Evalúa la cantidad de comillas.
                        case 1:                                     // Si son las primeras comillas.
                            name = &line[i + 1];                    // Marca el inicio del nombre del Message.
                            break;                                  // Termina de evaluar las comillas.

                        case 3:                                     // Si son las terceras comillas.
                            value = &line[i + 1];                   // Marca el inicio del valor del Message.
                            break;                                  // Termina de evaluar las comillas.

                        case 2:                                     // Si son las segundas comillas.
                        case 4:                                     // Si son las cuartas comillas.
                            line[i] = 0;                            // Marca el final del nombre o valor del Message.
                            break;                                  // Termina de evaluar las comillas.
                    }

                    if (quotation == 4) {                           // Si van cuatro comillas.
                        newMessage(list, name, value);              // Crea un nuevo Message.
                        break;                                      // Sale del for.
                    }
                }
        }

    fclose(fp);                                                     // Cierra filePath.

    return list;                                                    // Devuelve lista de Message.
}

/**
 * FIXME: Definición de {@code makePathList}.
 * Almacena en una lista de rutas todos los Message del archivo indicado por filePath.
 */
LANGUAGE DLLIMPORT CALLING MessageList* makePathList(char* filePath, char* ProgramDir) {
    MessageList* list = makeMessageList(filePath);                                      // Crea la lista de mensajes.
    Message* aux = list->first;                                                         // Crea un apuntador a un Message con el primer mensaje.
    char* value = NULL;                                                                 // Crea variable para almacenar el valor de cada Message.
    char path[500] = "";                                                                // Crea array para almacenar la ruta de cada mensaje.
    int pos = 0;                                                                        // Crea variable para indicar la posición actual de path.
    char actualDir[300] = "";                                                           // Crea variable que tendrá el directorio actual.
    getcwd(actualDir, 300);                                                             // Almacena el directorio actual en actualDir.

    char* flag1[] = {"%ProgramDir%", ProgramDir};                                       // Crea flag con el directorio del programa.
    char* flag2[] = {"%actualDir%", actualDir};                                         // Crea flag con el directorio actual.
    char** flags[] = {flag1, flag2, NULL};                                              // Crea apuntador a array de apuntadores con las flags.

    while (aux != NULL) {                                                               // Recorre la lista de Message.
        pos = 0;                                                                        // Reinicia pos.
        value = aux->value;
        for (int i = 0; i <= strlen(aux->value); i++) {                                 // Recorrer el valor del mensaje actual.
            if (value[i] == '%')                                                        // Si ecnuentra un indicador de flag.
                for (int j = 0; j < sizeof(flags); j++) {
                    if (flags[j] != NULL) {                                             // Si no terminó de recorrer las flags.
                        if (!strncmp(&value[i], flags[j][0], strlen(flags[j][0]))) {    // Si se indicó la flag actual.
                            sprintf(&path[pos], "%s", flags[j][1]);                     // Almacenba el valor de la flag actual en path.
                            pos += strlen(flags[j][1]);                                 // Aumenta pos la cantidad de posiciones del valor de la flag.
                            i += strlen(flags[j][0]);                                   // Aumenta i la cantidad de posiciones del nombre de la flag.
                        }
                    } else                                                              // Si es la última flag.
                        break;                                                          // Sale del for.
                }

            path[pos] = value[i];                                                       // A path le lleva el valor de value en la posición actual.
            pos++;                                                                      // Aumenta pos.
        }

        setMessageValue(aux, path);                                                     // Actualiza el campo value de aux.
        aux = aux->next;                                                                // Pasa al siguiente Message.
    }

    return list;                                                                        // Devuelve la lista con las rutas.
}

/**
 * FIXME: Definición de {@code printMessageList}.
 * Muestra los elementos de una lista de {Message} en pantalla.
 */
LANGUAGE DLLIMPORT CALLING void printMessageList(MessageList* list) {
    Message* aux = NULL;                            // Crea un apuntador a un Message.

    if (list->first != NULL)                        // Si la lista no está vacía.
        aux = list->first;                          // A aux le lleva la posición de memoria del primer Message de la lista.
    else                                            // Si la lista está vacía.
        printf("List is void\n");                   // Imprime que está vacía.

    while (aux != NULL) {                           // Recorre la lista de Message.
        printf("\"%s\" = ", aux->name);             // Imprime el nombre del Message actual.
        printf("\"%s\"\n", aux->value);             // Imprime el valor del Message actual.
        aux = aux->next;                            // Pasa al siguiente Message.
    }
    // printf("\n");                                // Imprime salto de línea.
}

/**
 * FIXME: Definición de {@code compareMessageName}.
 * Compara el campo name de un {Message} con un array y devuelve 1 si son iguales, y caso contrario 0.
 */
LANGUAGE DLLIMPORT CALLING int compareMessageName(Message* aux, char* array) {
    if ((int)strlen(array) != (int)strlen(aux->name))   // Si el nombre del Message tiene diferente longitud al array parámetro.
        return 0;                                       // Devuelve cero indicando que no son iguales.

    for (int i = 0; i < (int)strlen(aux->name); i++)    // Recorre el nombre del Message.
        if (aux->name[i] != array[i])                   // Si en la posición actual el nombre del Message no es igual al array parámetro.
            return 0;                                   // Devuelve cero indicando que no son iguales.

    return 1;                                           // Devuelve uno indicando que son iguales.
}

/**
 * FIXME: Definición de {@code findMessage}.
 * Obtiene un mensaje de una lista de mensajes.
 */
LANGUAGE DLLIMPORT CALLING Message* findMessage(MessageList* list, char* name) {
    Message* aux = NULL;                    // Crea un apuntador a un Message.
    aux = list->first;                      // A aux le lleva la posición de memoria del primer Message de la lista.

    while (aux != NULL) {                   // Recorre la lista de Message.
        if (compareMessageName(aux, name))  // Si el nombre del mensaje actual es igual que name.
            break;                          // Sale del while.
        aux = aux->next;                    // Pasa al siguiente Message.
    }

    return aux;                             // Devuelve el mensaje obtenido.
}
