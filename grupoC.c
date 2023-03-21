#include <linux/sched.h>
#include <linux/proc_fs.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/unistd.h>
#include <linux/signal.h>
#include <linux/string.h>
#include <linux/types.h>
#include <linux/pid.h>
#include <linux/grupoc.h>

//VARIABLES GLOBALES
extern int capacidad_actual; 

void crearProceso(struct task_struct *tipo_proceso){ // FUNCION DONDE CREAMOS LOS PROCESOS SEGUN LA CAPACIDAD DISPONIBLE Y LOS ENCOLAMOS CON SUS ARGUMENTOS CORRESPONDIENTES

  int politica = SCHED_RR;
  struct sched_param prioridad;
  int hayMenor; // VARIABLE PARA SABER SI HAY UN PROCESO MENOS PRIORITARIO (1) O NO (0)

  if (capacidad_actual>CAPACIDAD_N){ // COMPROBAMOS SI LA CAPACIDAD ACTUAL EXCEDE EL LIMITE  
    printk(KERN_INFO "*PRUEBAS*: Se ha excedido la capacidad del sistema.");
    hayMenor= buscarMenosPrio(tipo_proceso); // LLAMAMOS A buscarMenosPrio PARA VER SI HAY ALGUN PROCESO EN LA LISTA DE PCBS MENOS PRIORITARIO QUE EL ACTUAL

    if(hayMenor==0){ // NO ENCONTRO NINGUNO MENOS PRIORITARIO
	printk(KERN_INFO "*PRUEBAS*: kill proceso de %s (PID=%d), capacidad > N \n", tipo_proceso->comm, tipo_proceso->pid);
	matarProceso(tipo_proceso); // LLAMAMOS A matarProceso PARA MATAR AL PROCESO ACTUAL
   
    }else{ // ENCONTRO UNO MENOS PRIORITARIO Y ENCOLAMOS EL PROCESO ACTUAL, COMO NOS PASAMOS DEL LIMITE DE CAPACIDAD L, SOLO SE ENCOLARAN PROCESOS DE MANTENIMIENTO O ADMINISTRACION
      
      //********** PROCESO DE MANTENIMIENTO **********
      if(strcmp(tipo_proceso->comm,"mantenimiento")==0){
	prioridad.sched_priority= PRI_MANTENIMIENTO;
	sched_setscheduler(tipo_proceso, politica, &prioridad);
      }
      
      //********** PROCESO DE ADMINISTRACION **********
      if(strcmp(tipo_proceso->comm,"administracion")==0){
	prioridad.sched_priority= PRI_ADMINISTRACION;
	sched_setscheduler(tipo_proceso, politica, &prioridad);
      }
    }    
  }
  
  else{ // NO SOBREPASAMOS EL LIMITE DE CAPACIDAD N
    
    //********** PROCESO DE MANTENIMIENTO **********
    if(strcmp(tipo_proceso->comm,"mantenimiento")==0){
      prioridad.sched_priority= PRI_MANTENIMIENTO;
      sched_setscheduler(tipo_proceso, politica, &prioridad);
    }
    
    //********** PROCESO DE ADMINISTRACION **********
    if(strcmp(tipo_proceso->comm,"administracion")==0){
      prioridad.sched_priority= PRI_ADMINISTRACION;
      sched_setscheduler(tipo_proceso, politica, &prioridad); 
    }
    
    // PROCESOS QUE EJECUTA EL CLIENTE, SI CAPACIDAD > L LO MATAMOS, SINO SE ENCOLA
    
   //********** PROCESO DE PAGO **********
    if(strcmp(tipo_proceso->comm,"pago")==0 ||(strcmp(tipo_proceso->comm,"pagoLargo")==0)){
     if(capacidad_actual>CAPACIDAD_L){
       printk(KERN_INFO "*PRUEBAS*: kill proceso de %s (PID=%d), capacidad > L \n",tipo_proceso->comm, tipo_proceso->pid);
       matarProceso(tipo_proceso);
     }
     else{
       prioridad.sched_priority= PRI_PAGO;
       sched_setscheduler(tipo_proceso, politica, &prioridad);
     }
    } 

    //********** PROCESO DE ANULACION **********
   if(strcmp(tipo_proceso->comm,"anulacion")==0){
     if(capacidad_actual>CAPACIDAD_L){
       printk(KERN_INFO "*PRUEBAS*: kill proceso de %s (PID=%d), capacidad > L \n",tipo_proceso->comm, tipo_proceso->pid);
       matarProceso(tipo_proceso);
     }
     else{
       prioridad.sched_priority= PRI_ANULACION;
       sched_setscheduler(tipo_proceso, politica, &prioridad);
     }
   }
   
   //********** PROCESO DE RESERVA **********
   if(strcmp(tipo_proceso->comm,"reserva")==0){
     if(capacidad_actual>CAPACIDAD_L){
       printk(KERN_INFO "*PRUEBAS*: kill proceso de %s (PID=%d), capacidad > L \n",tipo_proceso->comm, tipo_proceso->pid);
       matarProceso(tipo_proceso);
     }
     else{
       prioridad.sched_priority= PRI_RESERVA;
       sched_setscheduler(tipo_proceso, politica, &prioridad);
     }
   }

   //********** PROCESO DE CONSULTA **********
   if(strcmp(tipo_proceso->comm,"consulta")==0){
     if(capacidad_actual>CAPACIDAD_L){
       printk(KERN_INFO "*PRUEBAS*: kill proceso de %s (PID=%d), capacidad > L \n",tipo_proceso->comm, tipo_proceso->pid);
       matarProceso(tipo_proceso);
     }
     else{
       prioridad.sched_priority= PRI_CONSULTA;
       sched_setscheduler(tipo_proceso, politica, &prioridad);  
     }
   }
 
  }
}

int buscarMenosPrio(struct task_struct *tipo_proceso){
  
  int i=0;
  struct task_struct *recorrer;
    for_each_process(recorrer){
      if(strcmp(recorrer->comm,"consulta")==0){
        printk(KERN_INFO "*PRUEBAS*: kill proceso de %s (PID=%d), capacidad > N \n", recorrer->comm, recorrer->pid);
	i=1;
	matarProceso(recorrer);
	break;
      }
    }
    if(i==0){
      for_each_process(recorrer){
	if(strcmp(recorrer->comm,"reserva")==0){
	  printk(KERN_INFO "*PRUEBAS*: kill proceso de %s (PID=%d), capacidad > N \n", recorrer->comm, recorrer->pid);
	i=1;
	matarProceso(recorrer);
	break;
	}
      }
    }
    if(i==0){
      for_each_process(recorrer){
	if(strcmp(recorrer->comm,"anulacion")==0){
	  printk(KERN_INFO "*PRUEBAS*: kill proceso de %s (PID=%d), capacidad > N \n", recorrer->comm, recorrer->pid);
	  i=1;
	  matarProceso(recorrer);
	break;
	}
      }
    }
    if(i==0){
      for_each_process(recorrer){
	if(strcmp(recorrer->comm,"pago")==0){
	  printk(KERN_INFO "*PRUEBAS*: kill proceso de %s (PID=%d), capacidad > N \n", recorrer->comm, recorrer->pid);
	  i=1;
	  matarProceso(recorrer);
	break;
	}
      }
    }
    if(i==0 && (strcmp(tipo_proceso->comm,"mantenimiento")==0)){
      for_each_process(recorrer){
	if(strcmp(recorrer->comm,"administracion")==0){
	  printk(KERN_INFO "*PRUEBAS*: kill proceso de %s (PID=%d), capacidad > N \n", recorrer->comm, recorrer->pid);
	  i=1;
	  matarProceso(recorrer);
	  break;
	}
      }
    }
    
    return i;
}

void mirarTiempo(){
  struct task_struct *recorrer;
  for_each_process(recorrer){ // USAMOS for_each_process PARA RECORRER LA LISTA DE PCBS
    // TENEMOS UN IF PARA SOLO AFECTAR A NUESTROS PROCESOS
    if( (strcmp(recorrer->comm,"mantenimiento")==0) || 
        (strcmp(recorrer->comm,"administracion")==0)||
        (strcmp(recorrer->comm,"pago")==0) ||
        (strcmp(recorrer->comm,"reserva")==0)|| 
        (strcmp(recorrer->comm,"consulta")==0) ||
        (strcmp(recorrer->comm,"anulacion")==0) ||
        (strcmp(recorrer->comm,"pagoLargo")==0))
	{

	if(cputime_to_secs(recorrer->utime)>TIMEOUT){ // PASAMOS EL TIEMPO DE EJECUCION DEL PROCESO DE TICKS A SEGUNDOS Y LO COMPARAMOS CON EL LIMITE TIMEOUT
	printk(KERN_INFO "*PRUEBAS*: El proceso de %s (PID=%d) se mata porque lleva más de %d segundos", recorrer->comm, recorrer->pid, TIMEOUT);
	matarProceso(recorrer);
      }
    }
  }
}

void matarProceso(struct task_struct *tipo_proceso){ 
// LLAMAMOS A KILL PARA MATAR EL PROCESO PASADO POR ARGUMENTO
  kill_pid(find_vpid(tipo_proceso->pid),SIGTERM,1);
}

