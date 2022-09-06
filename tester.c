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
#include "file_item.h"
#include "message.h"
#include "tester.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/**
 * Entrada principal del sistema.
 *
 * @param argc cantidad de argumentos pasados en la linea de comandos.
 * @param argv argumentos de la linea de comandos.
 * @return {0} si el programa se ejecutó correctamente.
 */
int main(int argc, char** argv) {
    char* programDir = getFatherPath(argv[0]);                          // Crea array con el directorio en donde se encuentra el ejecutable actual.
    char path[265] = "";                                                // Crea array que tendrá la ruta del archivo con las rutas.
    sprintf(path, "%s\\config\\paths.ini", programDir);                 // Almacena la ruta del archivo de rutas.
    MessageList* paths = makePathList(path, programDir);                // Obtiene los messages del archivo con las rutas.

    printf("\nPaths:\n");                                               // Muestra mensaje.
    prtMsgList(paths);                                                  // Muestra las rutas.

    MessageList* messages = makeMsgList(findMsgVal(paths, "messages")); // Obtiene los messages del archivo con los mensajes a mostar en pantalla.
    printf("\nMessages:\n");                                            // Muestra mensaje.
    prtMsgList(messages);                                               // Muestra los mensajes a mostar en pantalla.
}
