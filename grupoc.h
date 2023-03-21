#define PRI_MANTENIMIENTO 99
#define PRI_ADMINISTRACION 75
#define PRI_PAGO 60
#define PRI_ANULACION 45
#define PRI_RESERVA 30
#define PRI_CONSULTA 15
#define CAPACIDAD_N 8
#define CAPACIDAD_L 6
#define TIMEOUT 8


void crearProceso(struct task_struct*);
int buscarMenosPrio(struct task_struct*);
void mirarTiempo(void);
void matarProceso(struct task_struct*);
