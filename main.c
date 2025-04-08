#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "arraylist.h"

typedef struct {
    char nombre[51]; // nombre del cliente
    char rut[13];  // formato XX.XXX.XXX-X
    int id; // ID del cliente
    char descripcion[256]; // descripción del problema
    char prioridad[10]; // baja, media, alta
    char horaRegistro[9]; // formato HH:MM:SS
} Ticket;

Ticket* crearTicket(char* nombre, char* rut, int id, char* descripcion) {
    Ticket* ticket = malloc(sizeof(Ticket));
    if (ticket == NULL) exit(EXIT_FAILURE);
    
    strcpy(ticket->nombre, nombre);
    strcpy(ticket->rut, rut);
    strcpy(ticket->descripcion, descripcion);
    strcpy(ticket->prioridad, "baja");
    
    ticket->id = id;

    time_t tiempo = time(NULL);
    struct tm* info = localtime(&tiempo);
    strftime(ticket->horaRegistro, sizeof(ticket->horaRegistro), "%H:%M:%S", info);

    return ticket;
}

void registrarTicket(List* baja, char* nombre, char* rut, int id, char* descripcion) {
    Ticket* nuevo = crearTicket(nombre, rut, id, descripcion);
    pushBack(baja, nuevo);
}

Ticket* buscarTicketPorID(List* lista, int id) {
    Ticket* ticket = first(lista);
    while (ticket != NULL) {
        if (ticket->id == id) return ticket;
        ticket = next(lista);
    }
    return NULL;
}

int eliminarTicketPorID(List* lista, int id) {
    Ticket* ticket = first(lista);
    while (ticket != NULL) {
        if (ticket->id == id) {
            popCurrent(lista);
            return 1;
        }
        ticket = next(lista);
    }
    return 0;
}

void asignarPrioridad(List* baja, List* medio, List* alto, int id, char* nuevaPrioridad) {
    Ticket* ticket = buscarTicketPorID(baja, id);
    List* origen = baja;

    if (!ticket) {
        ticket = buscarTicketPorID(medio, id);
        origen = medio;
    }
    if (!ticket) {
        ticket = buscarTicketPorID(alto, id);
        origen = alto;
    }

    if (ticket) {
        if (strcmp(nuevaPrioridad, "baja") == 0) {
            pushBack(baja, ticket);
        } else if (strcmp(nuevaPrioridad, "media") == 0) {
            pushBack(medio, ticket);
        } else if (strcmp(nuevaPrioridad, "alta") == 0) {
            pushBack(alto, ticket);
        }
        eliminarTicketPorID(origen, id);
    }
}

main() {
    List* listaBaja = create_list();
    List* listaMedia = create_list();
    List* listaAlta = create_list();

    
}
