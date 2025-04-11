#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "arraylist.h"

typedef struct {
    int id; // ID del cliente
    char descripcion[256]; // descripción del problema
    unsigned short prioridad; // 1 baja, 2 media, 3 alta
    char horaRegistro[9]; // formato HH:MM:SS
} Ticket;

Ticket* crearTicket(int id, char* descripcion) {
    Ticket* ticket = malloc(sizeof(Ticket));
    if (ticket == NULL) exit(EXIT_FAILURE);
    
    strcpy(ticket->descripcion, descripcion);
    ticket->prioridad = 1;
    
    ticket->id = id;

    time_t tiempo = time(NULL);
    struct tm* info = localtime(&tiempo);
    strftime(ticket->horaRegistro, sizeof(ticket->horaRegistro), "%H:%M:%S", info);

    return ticket;
}

void registrarTicket(List* baja, int id, char* descripcion) {
    Ticket* nuevo = crearTicket(id, descripcion);
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
    printf("Descripcion: %s\n", ticket->descripcion);
    printf("Prioridad: %s\n", prioridad);
    printf("Hora de registro: %s\n\n", ticket->horaRegistro);
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

void eliminarTicketPorID(List* lista, int id) {
    Ticket* ticket = first(lista);
    while (ticket != NULL) {
        if (ticket->id == id) {
            popCurrent(lista);
            return;
        }
        ticket = next(lista);
    }
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
        if (nuevaPrioridad == 1) {
            pushBack(baja, ticket);
            ticket->prioridad = 1;
        } 
        else if (nuevaPrioridad == 2) {
            pushBack(medio, ticket);
            ticket->prioridad = 2;
        }
        else {
            pushBack(alto, ticket);
            ticket->prioridad = 3;
        }
    }
}

void mostrarTicketsPendientes(List* baja, List* media, List* alta) {
    if (get_size(alta) == 0 && get_size(media) == 0 && get_size(baja) == 0) {
        printf("No hay tickets pendientes.\n");
        return;
    }
    printf("\n=== Tickets Pendientes ===\n");
    if (get_size(alta) > 0) {
        Ticket* ticket = first(alta);
        printf("\nPrioridad Alta:\n");
        ticket = first(alta);
        while (ticket != NULL) {
            imprimirTicket(ticket);
            ticket = next(alta);
        }
    }
    if (get_size(media) > 0) {
        printf("\nPrioridad Media:\n");
        Ticket* ticket = first(media);
        while (ticket != NULL) {
            imprimirTicket(ticket);
            ticket = next(media);
        }
    } 
    if (get_size(baja) > 0) {
        printf("Prioridad Baja:\n");
        Ticket* ticket = first(baja);
        while (ticket != NULL) {
            imprimirTicket(ticket);
            ticket = next(baja);
        }
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
    } 
    else if (sizeMedia > 0) {
        printf("\nProcesando ticket de prioridad media:\n");
        Ticket* ticket = first(media);
        imprimirTicket(ticket);
        eliminarTicketPorID(media, ticket->id);
    } 
    else {
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
    char descripcion[256];

    do {
        printf("\n=== Sistema de Tickets ===\n");
        printf("1. Registrar nuevo ticket\n");
        printf("2. Asignar nueva prioridad a ticket\n");
        printf("3. Mostrar tickets pendientes\n");
        printf("4. Procesar siguiente ticket\n");
        printf("5. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%hu", &opcion);

        switch (opcion) {
            case 1:
                printf("Ingrese el ID del ticket: ");
                while (1) {
                    scanf("%d", &id);
                    if (buscarTicketPorID(listaBaja, id) == NULL && buscarTicketPorID(listaMedia, id) == NULL && buscarTicketPorID(listaAlta, id) == NULL) {
                        break;
                    } else {
                        printf("El ID ya existe. Ingrese otro ID: ");
                    }
                }
                printf("Ingrese la descripcion del problema: ");
                scanf("%s", descripcion);
                registrarTicket(listaBaja, id, descripcion);
                printf("Ticket registrado con ID: %d\n", id);
                break;
            case 2:
                printf("Ingrese el ID del ticket a modificar: ");
                do {
                    scanf("%d", &id);
                    if (buscarTicketPorID(listaBaja, id) == NULL && buscarTicketPorID(listaMedia, id) == NULL && buscarTicketPorID(listaAlta, id) == NULL) {
                        printf("El ID no existe. Ingrese otro ID: ");
                    }
                } while (buscarTicketPorID(listaBaja, id) == NULL && buscarTicketPorID(listaMedia, id) == NULL && buscarTicketPorID(listaAlta, id) == NULL);

                printf("Ingrese la nueva prioridad (1 para baja, 2 para media, 3 para alta): ");
                do {
                    scanf("%d", &nuevaPrioridad);
                    if (nuevaPrioridad < 1 || nuevaPrioridad > 3) {
                        printf("Prioridad no valida. Ingrese nuevamente (1 para baja, 2 para media, 3 para alta): ");
                    }
                } while (nuevaPrioridad < 1 || nuevaPrioridad > 3);
                
                asignarPrioridad(listaBaja, listaMedia, listaAlta, id, nuevaPrioridad);
                printf("Prioridad del ticket %d actualizada correctamente.\n", id);
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
                printf("Opcion no valida.\n");
                break;
        }
    } while (opcion != 5);

    return EXIT_SUCCESS;
}

