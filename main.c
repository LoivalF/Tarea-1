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
    unsigned short prioridad; // 1 baja, 2 media, 3 alta
    char horaRegistro[9]; // formato HH:MM:SS
} Ticket;

Ticket* crearTicket(char* nombre, char* rut, int id, char* descripcion) {
    Ticket* ticket = malloc(sizeof(Ticket));
    if (ticket == NULL) exit(EXIT_FAILURE);
    
    strcpy(ticket->nombre, nombre);
    strcpy(ticket->rut, rut);
    strcpy(ticket->descripcion, descripcion);
    ticket->prioridad = 1;
    
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

void imprimirTicket(Ticket* ticket) {
    char prioridad[10];
    switch (ticket->prioridad) {
        case 1: strcpy(prioridad, "Baja"); break;
        case 2: strcpy(prioridad, "Media"); break;
        case 3: strcpy(prioridad, "Alta"); break;
    }

    printf("ID: %d\n", ticket->id);
    printf("Nombre: %s\n", ticket->nombre);
    printf("RUT: %s\n", ticket->rut);
    printf("Descripción: %s\n", ticket->descripcion);
    printf("Prioridad: %s\n", prioridad);
    printf("Hora de registro: %s\n", ticket->horaRegistro);
}

Ticket* buscarTicketPorID(List* lista, int id) {
    Ticket* ticket = first(lista);
    while (ticket != NULL) {
        if (ticket->id == id) return ticket;
        ticket = next(lista);
    }
    return NULL;
}

Ticket* buscarTicketPorIDyDetalles(List* lista, int id) {
    Ticket* ticket = buscarTicketPorID(lista, id);
    if (ticket) {
        imprimirTicket(ticket);
        return ticket;
    } 
    else printf("Error: El ticket no existe.\n"); 
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

void asignarPrioridad(List* baja, List* medio, List* alto, int id, unsigned short nuevaPrioridad) {
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

    if (!ticket) printf("El ticket no existe.\n"); return;

    eliminarTicketPorID(origen, id);

    if (ticket) {
        if (nuevaPrioridad == 1 && ticket->prioridad == 1) {
            pushBack(baja, ticket);
        } 
        else if (nuevaPrioridad == 2 && ticket->prioridad == 2) {
            pushBack(medio, ticket);
        }
        else {
            pushBack(alto, ticket);
        }
    }
}

void mostrarTicketsPendientes(List* baja, List* media, List* alta) {
    printf("\n=== Tickets Pendientes ===\n");
    Ticket* ticket = first(alta);
    printf("\nPrioridad Alta:\n");
    ticket = first(alta);
    while (ticket != NULL) {
        imprimirTicket(ticket);
        ticket = next(alta);
    }
    printf("\nPrioridad Media:\n");
    ticket = first(media);
    while (ticket != NULL) {
        imprimirTicket(ticket);
        ticket = next(media);
    }
    printf("Prioridad Baja:\n");
    while (ticket != NULL) {
        imprimirTicket(ticket);
        ticket = next(baja);
    }
}

void procesarSgteTicket(List* baja, List* media, List* alta) {
    int sizeAlta = get_size(alta);
    int sizeMedia = get_size(media);
    int sizeBaja = get_size(baja);
    if (sizeAlta == 0 && sizeMedia == 0 && sizeBaja == 0) {
        printf("\nNo hay tickets pendientes.\n");
        return;
    }
    if (sizeAlta > 0) {
        printf("\nProcesando ticket de prioridad alta:\n");
        Ticket* ticket = first(alta);
        imprimirTicket(ticket);
        eliminarTicketPorID(alta, ticket->id);
    } else if (sizeMedia > 0) {
        printf("\nProcesando ticket de prioridad media:\n");
        Ticket* ticket = first(media);
        imprimirTicket(ticket);
        eliminarTicketPorID(media, ticket->id);
    } else {
        printf("\nProcesando ticket de prioridad baja:\n");
        Ticket* ticket = first(baja);
        imprimirTicket(ticket);
        eliminarTicketPorID(baja, ticket->id);
    }
}

int main() {
    List* listaBaja = create_list();
    List* listaMedia = create_list();
    List* listaAlta = create_list();

    unsigned short opcion, nuevaPrioridad; int id;
    char nombre[51], rut[13], descripcion[256];

    do {
        printf("\n=== Sistema de Tickets ===\n");
        printf("1. Registrar nuevo ticket\n");
        printf("2. Asignar nueva prioridad a ticket\n");
        printf("3. Mostrar tickets pendientes\n");
        printf("4. Procesar siguiente ticket\n");
        printf("5. Salir\n");
        printf("Seleccione una opción: ");
        scanf("%hu", &opcion);

        switch (opcion) {
            case 1:
                printf("Ingrese el nombre del cliente: ");
                scanf("%s", nombre);
                printf("Ingrese el RUT del cliente: ");
                scanf("%s", rut);
                printf("Ingrese la descripción del problema: ");
                scanf("%s", descripcion);
                printf("Ingrese el ID del ticket: ");
                while (1) {
                    scanf("%d", &id);
                    if (buscarTicketPorID(listaBaja, id) == NULL && buscarTicketPorID(listaMedia, id) == NULL && buscarTicketPorID(listaAlta, id) == NULL) {
                        break;
                    } else {
                        printf("El ID ya existe. Ingrese otro ID: ");
                    }
                }
                printf("Ingrese la prioridad (1 para baja, 2 para media, 3 para alta): "); 
                registrarTicket(listaBaja, nombre, rut, id, descripcion);
                printf("Ticket registrado con ID: %d\n", id);
                break;
            case 2:
                printf("Ingrese el ID del ticket a modificar: ");
                scanf("%d", &id);
                printf("Ingrese la nueva prioridad (1 para baja, 2 para media, 3 para alta): ");
                scanf("%hu", &nuevaPrioridad);
                asignarPrioridad(listaBaja, listaMedia, listaAlta, id, nuevaPrioridad);
                break;
            case 3:
                printf("Mostrar Tickets pendientes:\n");
                mostrarTicketsPendientes(listaBaja, listaMedia, listaAlta);
                break;
            case 4:
                printf("Procesar siguiente ticket:\n");
                procesarSgteTicket(listaBaja, listaMedia, listaAlta);
                break;
            case 5:
                printf("Saliendo del programa...\n");
                free(listaBaja);
                free(listaMedia);
                free(listaAlta);
                return EXIT_SUCCESS;
            default:
                printf("Opción no válida.\n");
                break;
        }
    } while (opcion != 5);

    return EXIT_SUCCESS;
}
