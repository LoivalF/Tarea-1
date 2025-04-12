# Tarea-1
Sistema de gestión de tickets

El programa consiste en el manejo de tickets por prioridad mediante el uso de el TDA lista,
cuenta con un menu principal con 6 opciones, incluida la opcion de salir del programa. Tiene 
distintas funcionalidades como lo son crear tickets nuevos, asignarle una nueva prioridad a 
tickets preexistentes, buscar un ticket por su ID y mostrar sus detalles, mostrar todos los 
tickets pendientes en orden descendente y procesar/eliminar el siguiente ticket. No esta 
ligado a ningun campo especifico, por lo que es un programa para el fin que se estime 
conveniente.

# Como ejecutar el programa
En el GitHub estan adjuntos tanto el archivo **main.c** como **a.exe**, el cual es el ejecutable, unicamente hace falta descargar el archivo **a.exe** y ejecutarlo para acceder al programa.
https://github.com/LoivalF/Tarea-1/blob/main/a.exe  es el link al archivo a descargar.

# Requisitos previos
Trabaja desde la terminal, por lo que no existen prerrequisitos mas que abrir el archivo, el cual abre la terminal con el programa listo para su uso.

# Aviso
Dentro del archivo de codigo del programa, esta comentado a detalle que es lo que hace cada una de las funcionalidades del mismo.

# Funcionalidades

# Funcionando correctamente:
1) Registrar nuevo ticket: Luego de presionar esta opcion, entraras a otro menu, el cual te pedira ingresar un ID, el programa no toma en cuenta ID ya existentes, por lo que si ingresas uno que ya existe, te devolvera al 
menu principal. En cualquier otro caso, a continuacion te pedira ingresar la descripcion del problema con un 
maximo de 255 caracteres, luego de eso, se muestra si el ticket se creo correctamente y te retorna al menu
principal.

2) Asignar nueva prioridad a ticket: En este apartado, el programa te pide ingresar el ID del ticket a modificar, en caso de ingresar un ID no existente, el programa te regresa al menu principal. Si se ingresa
un ID existente, se pregunta a que prioridad se desea cambiar, a 1, 2 o 3; baja, media, alta respectivamente.
Si no se ingresa un numero entre 1 y 3 el programa preguntara hasta que se uno correctamente, a continuacion
se muestra cuando se actualiza la prioridad y se devuelve al menu principal.

3) Mostrar tickets pendientes: Muestra los tickets pendientes en prioridad descendente (alto, medio, bajo), en
caso de no existir tickets se mostrara un aviso de que no hay tickets pendientes, habra una separacion indicando a cual prioridad corresponde.

4) Procesar siguiente ticket: En caso de no existir tickets pendientes, se mostrara el pantalla. Si existen tickets, se procesara el ticket que cumpla dos condiciones: Ser el ticket con la mayor y el mas antiguo.
A continuacion se muestran los datos del ticket a procesar y finalmente se procesa (elimina). Luego regresa al menu principal.

5) Buscar ticket por ID: Para buscar un ticket por ID te pide ingresar ingresar el ID, en caso de que no exista te regresa al menu principal. Si existe el ID te muestra los detalles del ticket que tiene ese ID.

6) Salir: Finaliza el programa.

# Ejemplo de uso

# Paso 1: Registrar nuevo paciente
Opcion seleccionada: 1) Registrar nuevo ticket
Ingrese el ID del ticket: 1
Ingrese la descripcion del problema: Se esta incendiando mi casa

# Paso 2: Buscar ticket por ID
Opcion seleccionada: 5) Buscar ticket por ID
Buscar ticket por ID:
Ingrese el ID del ticket: 1
ID: 1
Descripcion: Se esta incendiando mi casa
Prioridad: Baja
Hora de registro: 15:04:12

# Paso 3: Asignar nueva prioridad a ticket
Opcion seleccionada: 3) Asignar nueva prioridad a ticket
Ingrese el ID del ticket a modificar: 1
Ingrese la nueva prioridad (1 para baja, 2 para media, 3 para alta): 3
Prioridad del ticket 1 actualizada correctamente.

# Paso 4: Mostrar tickets pendientes
Opcion seleccionada: 3) Mostrar tickets pendientes
Mostrar Tickets pendientes:

=== Tickets Pendientes ===

Prioridad Alta:
ID: 1
Descripcion: Se esta incendiando mi casa
Prioridad: Alta
Hora de registro: 15:04:12

# Paso 5: Procesar siguiente ticket
Opcion seleccionada: 4) Procesar siguiente ticket
Procesando siguiente ticket:

Procesando ticket de prioridad alta:
ID: 1
Descripcion: Se esta incendiando mi casa
Prioridad: Alta
Hora de registro: 15:04:12

# Paso 6: Buscar ticket por ID
Opcion seleccionada: 5) Buscar ticket por ID
Buscar ticket por ID:
Ingrese el ID del ticket: 1
El ID no existe. Ingrese otro ID:

# Paso 7: Salir
Opcion seleccionada: 6) Salir

# A mejorar
Mejorar la interfaz dentro de cada funcionalidad y el menu principal.
Permitir cambiar la descripcion del problema.