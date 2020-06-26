/*Carlos Badillo Lora*/
typedef struct cuad QUAD;

struct cuad {
    char *op;
    char *arg1;
    char *arg2;
    char *res;
    CUAD *next;
};

typedef struct code{
    CUAD *head;
    CUAD *tail;
} CODE;

CUAD *init_quad(); //Reserva memoria para una cuadrupla
void finish_quad(QUAD *c); // Libera la memoria de una cuadrupla

CODE *init_code (); //Rserva memoria para el codigo
void finish_code (CODE *c); // Libera la memoria de la lista ligada del codigo

void append_quad(CODE* c, CUAD *cd);// Agrega una cuadrupla al final de la lista
