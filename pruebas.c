#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sched.h>
#include </home/henar/linux_src/include/linux/prioridades.h> // PARA CONOCER LOS LIMITES DE CAPACIDAD L, N Y EL TIMEOUT

int main(){

  int N_mas_1 = CAPACIDAD_N+1 ;
  int L_mas_1= CAPACIDAD_L+1;
  int num_prueba=1;
  int i;
  int k;

  printf("\n  ******************************************************************************\n");
  printf("  *                  PRUEBAS - SERVICIO DE TAQUILLA VIRTUAL                    *\n");
  printf("  ******************************************************************************\n");

  printf("\n  Límite de capacidad N= %d, límite de capacidad  L= %d y timeout= %d segundos \n", CAPACIDAD_N, CAPACIDAD_L, TIMEOUT);
    
  printf("\n  1. Lanzar un proceso de cliente de cada tipo. (Comprobación prioridades) \n ");
  printf(" 2. Lanzar dos procesos de mantenimiento y dos de administración. (Comprobación prioridades)\n ");
  printf(" 3. Lanzar un proceso de cada tipo. (Comprobación de prioridades)\n ");
  printf(" 4. Lanzar cuatro procesos de pagos. (Comprobación de RR)\n ");
  printf(" 5. Lanzar un proceso que supere el timeout. (Comprobación timeout)\n ");
  printf(" 6. Lanzar L+1 procesos de consulta. (Comprobación límite L)\n ");
  printf(" 7. Lanzar L+2 procesos de mantenimiento. (Comprobación límite L)\n ");
  printf(" 8. Lanzar L procesos de consulta, uno de administración y otro de pago. (Comprobación límite L)\n ");
  printf(" 9. Lanzar N+1 procesos de mantenimiento. (Comprobación límite N)\n ");
  printf("10. Lanzar N procesos de administración y uno de mantenimiento. (Comprobación límite N).\n ");
  printf("\n Introduzca el número de prueba a ejecutar [1-10]: ");
    
  scanf("%d", &num_prueba);  


  switch (num_prueba){
      
   case 1:  // LANZAR UN PROCESO CLIENTE DE CADA TIPO
     if(fork()==0){
       if(fork()==0){
	 if(fork()==0){
	   execl("anulacion", NULL); 
	 }else{
	   execl("pago", NULL);
	 }
       }else{
	 execl("reserva", NULL);
       }
     }else{
       execl("consulta", NULL);
     }
     
     break;
     
  case 2:  // LANZAR 2 DE ADMIN Y 2 DE MANTENIMIENTO
    if(fork()==0){
      if(fork()==0){
	if(fork()==0){
	  execl("administracion", NULL); 
	}else{
	  execl("mantenimiento", NULL);
	}
      }else{
	execl("administracion", NULL);
      }
    }else{
      execl("mantenimiento", NULL);
    }
    
    break;
    
  case 3: //LANZAR UN PROCESO DE CADA TIPO
    if(fork()==0){
      if(fork()==0){
	if(fork()==0){
	  if(fork()==0){
	    if(fork()==0){
	      execl("consulta", NULL); 
	    }else{
	      execl("reserva", NULL);
	    }
	  }else{
	    execl("anulacion", NULL);
	  }
	}else{
	  execl("pago", NULL);
	}
      }else{
	execl("administracion", NULL);
      } 
    }else{
      execl("mantenimiento", NULL);
    }
    
    break;
    
  case 4: // LANZAR 4 DE PAGOS
    if(fork()==0){
      if(fork()==0){
	if(fork()==0){
	  execl("pago", NULL);
	}else{
	execl("pago", NULL);
	}
      }else{
	execl("pago", NULL);
      }
    }else{
      execl("pago", NULL);
    }
    
    break;
    
  case 5:  // LANZAR PAGO LARGO
    if(fork()==0){
      execl("pagoLargo",NULL);
    }
    break;
    
  case 6: // L+1 CONSULTA
    for(i=0;i<CAPACIDAD_L+1;i++){
      if(fork()==0){
	execl("consulta",NULL);
      }
    }
    break;
    
  case 7: // L+2 MANTENIMIENTO
    for(i=0;i<L_mas_1+1;i++){
      if(fork()==0){
	execl("mantenimiento",NULL);
      }
    }    
    break;
    
  case 8: // L CONSULTA, 1 ADMIN 1 PAGO
    if(fork()==0){
      if(fork()==0){
	if(fork()==0){
	  if(fork()==0){
	    if(fork()==0){
	      if(fork()==0){
		if(fork()==0){
		  execl("pago",NULL);
		}else{
		  execl("administracion", NULL); 
		}
	      }else{
		  execl("consulta",NULL);
		}
	      }else{
		execl("consulta", NULL);
	      }
	    }else{
	      execl("consulta", NULL);
	    }
	  }else{
	    execl("consulta", NULL);
	  }
	}else{
	  execl("consulta", NULL);
	} 
      }else{
	execl("consulta", NULL);
      }

      break;
      
  case 9: // N+1 DE ADMINISTRACIÓN
    for(i=0;i<N_mas_1;i++){ 
      if(fork()==0){
	execl("mantenimiento",NULL);
      }
    }
    
    break;
    
  case 10: // N DE ADMINISTRACIÓN Y UNO D
    if(fork()==0){
      if(fork()==0){
	if(fork()==0){
	  if(fork()==0){
	    if(fork()==0){
	      if(fork()==0){
		if(fork()==0){
		  if(fork()==0){
		    execl("mantenimiento",NULL);
		  }else{
		    execl("administracion",NULL);
		  }
		}else{
		  execl("administracion", NULL); 
		}
	      }else{
		execl("administracion",NULL);
	      }
	    }else{
	      execl("administracion", NULL);
	    }
	  }else{
	    execl("administracion", NULL);
	  }
	}else{
	  execl("administracion", NULL);
	}
      }else{
	execl("administracion", NULL);
      } 
    }else{
      execl("administracion", NULL);
    }
    
    break;
    
  default:
    
    break;
  }
  
  return 0;
  
}
