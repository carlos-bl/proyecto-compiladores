#include <stdio.h>
# include <stdlib.h>

typedef struct cuad QUAD;

struct cuad {
    char *op;
    char *arg1;
    char *arg2;
    char *res;
    QUAD *next;
};

typedef struct code{
    QUAD *head; //cambiado de cuad
    QUAD *tail;
} CODE;

//Reserva memoria para una cuadrupla
QUAD *init_quad(){ 
    struct cuad * nuevaCuad;
    nuevaCuad = malloc(sizeof(struct cuad));
    return nuevaCuad;

}
// Libera la memoria de una cuadrupla
void finish_quad(QUAD *c){ 
    free(c);
}

//Rserva memoria para el codigo
CODE *init_code (){ 
    struct code * nuevoCode;
    nuevoCode = malloc(sizeof(struct code));
    return nuevoCode;
}
 // Libera la memoria de la lista ligada del codigo
void finish_code (CODE *c){
    free(c);
}


//hay dos listas? de quad y de code?
// Agrega una cuadrupla al final de la lista
void append_quad(CODE* c, QUAD *cd){

    c->tail->next = cd;
    c->tail =cd;

}

    

int main(){
}
