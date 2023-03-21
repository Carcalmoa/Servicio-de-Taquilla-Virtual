#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int main(){
  
  int i;
  int j;
  clock_t start;
  clock_t end;
  double seconds;
  start=clock();
  pid_t getpid(void);
  int pid = getpid();
  

  printf("Empieza proceso de RESERVA (PID=%d)\n",pid);
  for(i=0; i<100000;i++){
    if(i==100){
      printf("Se está ejecutando RESERVA (PID=%d)\n", pid);
    }
    if(i==7500){
      printf("Se está ejecutando RESERVA (PID=%d)\n", pid);
    }

    for(j=0;j<12500;j++){
    }
  }
  end=clock();
  seconds=((double)(end-start))/CLOCKS_PER_SEC;
  printf("Termina proceso de RESERVA (PID=%d), duró: %f segundos\n",pid, seconds);
}
