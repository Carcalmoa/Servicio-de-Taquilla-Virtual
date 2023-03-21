# Servicio-de-Taquilla-Virtual
Diseño y desarrollo del Sistema de Planificación de la CPU.

## exec.c (/home/carlos/linux_src/fs)
Inicializo la variable global capacidad_actual.
Dentro de la función set_task_comm, en la que entra cuando hacemos un execl, if para que solo entren nuestros procesos comparando el tsk->comm con el nombre de nuestros .c,
sumamos 1 a la capacidad_actual, pritnk para mostrar que la capacidad_actual aumentó y llamamos a crearProceso().
	
## exit.c (/home/carlos/linux_src/kernel)
Dentro de la función do_exit, entra automáticamente cuando se termina un proceso, if para que solo entren nuestros procesos comparando el tsk->comm con el nombre de nuestros .c
restamos -1 a la capacidad_actual, printk capacidad_actual para ver que salió.

## core.c (/home/carlos/linux_src/kernel/sched) 
Dentro de la función scheduler_tick, donde entra cada tick, tenemos una variable llamada tiempo_comprobar donde vamos contando los ticks, sumándole 1 debajo de su declaración (cada vez que entra en la función se suma 1 entonces cuenta los ticks) y cuando llega a 50, mediante un if, llamamos a la función mirarTiempo para ver cuánto tiempo llevan ejecutándose nuestros procesos y matarlos si sobrepasan el TIMEOUT.

## grupo.c (/home/carlos/linux_src/kernel) 
- **crearProceso()**
Comparamos si capacidad_actual > Capacidad N, TRUE llamamos a buscarMenosPrio(), si retorna 0 es que no encontró ninguno menos prioritario y mata a este. FALSE busca qué proceso es el que se va a ejecutar comparando el tipo_proceso->comm con el nombre de todos nuestros .c. Cuando lo encuentra lo encola con shed_setscheduler con sus parámetros correspondientes (struct task_struct *, política y prioridad).
En los procesos del cliente compara si capacidad_actual > capacidad_L: TRUE printk diciendo que lo mata y llama a matarProceso(tipo_proceso), FALSE lo encola como a los anteriores.
- **buscarMenosPrio()**
Tenemos un for_each_process para recorrer la lista de PCBs. Dentro del for_each_process tenemos de menor prioridad a mayor prioridad if para comparar recorrer->comm con los nombres de nuestros procesos ordenados de menor a mayor prioridad, de esta forma mata primero al que menor prioridad tenga.
Retorna la variable “i”, inicializada a 0 que se pone a 1 justo antes de matar a un proceso, antes de cada if comparamos si i=0 porque si i=1 significa que ya hemos matado a un proceso y ya podemos salir de la función.
- **mirarTiempo()**
Con for_each_process recorremos la lista de PCBs. Dentro tenemos un if que compara el recorrer->comm con el nombre de nuestros .c para que solo lo haga con nuestros procesos.
Pasamos el tiempo de ejecución del proceso en ticks (recorrer->utime), lo pasamos a segundos y lo comparamos con el límite. Si el proceso se pasa del TIMEOUT (establecido por nosotros declarado con un define en el grupoc.h) hace un printk y lo mata.
- **matarProceso()**
llamamos a kill_pid(find_vpid(tipo_proceso->pid),SIGTERM,1), función del sistema que mata al proceso. Cuando hacemos kill_pid del proceso también pasa por el do_exit entonces no hace falta restarle aquí 1 a la capacidad_actual porque ya lo hace en el do_exit.

## grupoc.h (/home/carlos/linux_src/include/linux)
incluída en core.c, exec.c, grupo.c

Cabeceras de las funciones: crearProceso, matarProceso, mirarTiempo, buscarMenosPrio.

Definiciones de todas las constantes: Prioridad de cada tipo de proceso, Límite Capacidad L, Límite Capacidad N, Timeout.
## grupoc_definiciones.h (/home/carlos/linux_src/include/linux)
Se usa para el pruebas.c porque ahí no podemos meter el grupoc.h 

Definiciones de todas las constantes: Prioridad de cada tipo de proceso, Límite Capacidad L, Límite Capacidad N, Timeout.




