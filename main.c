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

/* Esta funcion reserva memoria para 1 ticket y le copia
la ID y la descripcion entregadas, ademas de eso usa la 
hora actual del sistema como hora de registro en el 
formato HH:MM:SS*/
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

/*Usa la funcion crear ticket y lo inserta de manera
predeterminada en la lista de prioridad baja con un
push back*/
void registrarTicket(List* baja, int id, char* descripcion) {
    Ticket* nuevo = crearTicket(id, descripcion);
    pushBack(baja, nuevo);
}

/*Hago una variable de prioridad que se basa en el numero
que esta guardado en el ticket, 1 para baja, 2 para media 
y 3 para alta, luego muestro los datos ya guardados en el 
ticket mas la prioridad*/
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

/*Recibe una lista y un ID para buscar, busca 
desde el primero hasta el ultimo de la lista, 
si lo encuentra lo retorna, si no retorna nulo*/
Ticket* buscarTicketPorID(List* lista, int id) {
    Ticket* ticket = first(lista);
    while (ticket != NULL) {
        if (ticket->id == id) return ticket;
        ticket = next(lista);
    }
    return NULL;
}

/*Esta funcion hace lo mismo que la de arriba con la 
diferencia que esta ademas imprime los detalles si es 
que existe, si no existe muestra un respectivo aviso*/
Ticket* buscarTicketPorIDyDetalles(List* lista, int id) {
    Ticket* ticket = buscarTicketPorID(lista, id);
    if (ticket) {
        imprimirTicket(ticket);
        return ticket;
    } 
    else printf("Error: El ticket no existe.\n"); 
    return NULL;
}

/*Funciona de manera parecida a buscar por ID, pero 
si en esta si es que lo encuentra lo borra y retorna*/
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

/*Asigna prioridad recibiendo las listas para las 3 prioridades, el ID 
y la nueva prioridad, va consecutivamente buscando el ID en las lista 
en orden ascendente, si no lo encuentra lo especifica y en cualquier otro
caso lo borra desde donde esta, le cambia la prioridad y le hace un 
push back basado en la nueva prioridad*/
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

    if (!ticket) {
        printf("El ticket no existe.\n"); 
        return;
    }

    eliminarTicketPorID(origen, id);

    ticket->prioridad = nuevaPrioridad;

    if (nuevaPrioridad == 1) {
        pushBack(baja, ticket);
    } 
    else if (nuevaPrioridad == 2) {
        pushBack(medio, ticket);
    }
    else {
        pushBack(alto, ticket);
    }
}

/*Muestra todos los tickets pendientes entre las 3 listas, si no hay ninguno
en las 3, lo especifica, en otros casos muestra los tickets de las listas 
con tamanyo mayor a 0, para imprimirlos va recorriendo cada lista*/
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
/*Procesa el siguiente ticket, si no hay tickets en ninguna lista
lo especifica y si no borra solo 1 ticket de la lista que contenga 
tickets con la mayor prioridad*/
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

/*Crea 1 lista para cada prioridad y asigna las variables a usar
hace un do while para que el programa se ejecute hasta que el 
usuario lo requiera, se muestra el menu y la ultima opcion finaliza
el programa, limpia la pantalla en cada opcion, en la primera, 
ingresar un nuevo ticket, se revisa si el ID ya existe, en la 
segunda, cambiar prioridad, se revisa si el ticket no existe,
igual que con la prioridad, que se repite hasta que este entre
1 y 3, opcion 3 y 4 funcionan normalmente y en la 5, buscar
ticket por ID se revisa que el ID sea valido y la opcion 6
es para salir, liberando todas las listas antes*/
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
        printf("5. Buscar ticket por ID\n");
        printf("6. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%hu", &opcion);

        switch (opcion) {
            case 1:
                system("cls||clear");
                printf("Ingrese el ID del ticket: ");
                do {
                    scanf("%d", &id);
                    getchar(); 
                    if (buscarTicketPorID(listaBaja, id) == NULL && buscarTicketPorID(listaMedia, id) == NULL && buscarTicketPorID(listaAlta, id) == NULL) {
                        break;
                    } else {
                        printf("El ID ya existe. Ingrese otro ID: ");
                    }
                } while (1);
                printf("Ingrese la descripcion del problema: ");
                getchar(); 
                fgets(descripcion, sizeof(descripcion), stdin);
                descripcion[strcspn(descripcion, "\n")] = 0;
                registrarTicket(listaBaja, id, descripcion);
                printf("Ticket registrado con ID: %d\n", id);
                system("cls||clear");
                break;
            case 2:
                system("cls||clear");
                printf("Ingrese el ID del ticket a modificar: ");
                
                scanf("%d", &id);
                if (buscarTicketPorID(listaBaja, id) == NULL && buscarTicketPorID(listaMedia, id) == NULL && buscarTicketPorID(listaAlta, id) == NULL) {
                    printf("El ID no existe. Ingrese otro ID: \n");
                    break;
                }

                printf("Ingrese la nueva prioridad (1 para baja, 2 para media, 3 para alta): ");
                do {
                    scanf("%d", &nuevaPrioridad);
                    if (nuevaPrioridad < 1 || nuevaPrioridad > 3) {
                        printf("Prioridad no valida. Ingrese nuevamente (1 para baja, 2 para media, 3 para alta): ");
                    }
                } while (nuevaPrioridad < 1 || nuevaPrioridad > 3);
                
                asignarPrioridad(listaBaja, listaMedia, listaAlta, id, nuevaPrioridad);
                printf("Prioridad del ticket %d actualizada correctamente.\n", id);
                getchar();
                break;
            case 3:
                system("cls||clear");
                printf("Mostrar Tickets pendientes:\n");
                mostrarTicketsPendientes(listaBaja, listaMedia, listaAlta);
                break;
            case 4:
                system("cls||clear");
                printf("Procesando siguiente ticket:\n");
                procesarSgteTicket(listaBaja, listaMedia, listaAlta);
                break;
            case 5:
                system("cls||clear");
                printf("Buscar ticket por ID:\n");
                printf("Ingrese el ID del ticket: ");
                
                scanf("%d", &id);
                if (buscarTicketPorID(listaBaja, id) == NULL && buscarTicketPorID(listaMedia, id) == NULL && buscarTicketPorID(listaAlta, id) == NULL) {
                    printf("El ID no existe. Ingrese otro ID: \n");
                    break;
                }
                
                buscarTicketPorIDyDetalles(listaBaja, id);
                buscarTicketPorIDyDetalles(listaMedia, id);
                buscarTicketPorIDyDetalles(listaAlta, id);
                break;
            case 6:
                printf("Saliendo del programa...\n");
                free(listaBaja);
                free(listaMedia);
                free(listaAlta);
                return EXIT_SUCCESS;
            default:
                system("cls||clear");
                printf("Opcion no valida.\n");
                getchar();
                break;
        }
    } while (opcion != 6);

    return EXIT_SUCCESS;
}



