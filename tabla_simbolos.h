/*Carlos Badillo Lora*/
#include "data.h"
//#include "tabla_simbolos.h"
//#include "tabla_tipos.h"
#include <stdio.h>
 # include <stdlib.h>
#include <string.h>
# include <assert.h>

// SYMTAB STG = (SYMTAB *)0;

SYMTAB *init_sym_tab ()  //Reserva memoria para una_tabla de simbolos vacia
{
    SYMTAB *nuevosymtab;
    nuevosymtab = malloc(sizeof(struct sym_tab));
    nuevosymtab->num = 0;
    return nuevosymtab;
}

ARG *init_arg ( int dato){
    ARG *nuevoarg;
    nuevoarg = malloc(sizeof(struct arg));
    nuevoarg->arg = dato;
    //printf("dato");
    //printf("%i",nuevoarg->arg);
    return nuevoarg;
}

void printarg(ARG* arg){
    //assert(arg != NULL);
    printf("el argumento es:");
    printf("%d",arg->arg);
}
ARGS *init_args (){
    ARGS *nuevoargs;
    nuevoargs = malloc(sizeof(struct args));
    nuevoargs->num = 0;
    //printf("dato");
    //printf("%i",nuevoarg->arg);
    return nuevoargs;
}


void append_arg(ARGS* args , int arg){ //Agrega un_argumento al final
    ARG* nuevoarg =init_arg(arg);
    if(args->tail != NULL)
        nuevoarg->next =args->tail;
    args->tail=nuevoarg;
    args->num++;
    if(args->head==NULL)
    args->head=nuevoarg;
    
}

int compare_arg(ARG *a1, ARG *a2){
    if(a1->arg != a2->arg)
        return 0;
    if(a1->next!=NULL)
        compare_arg(a1->next, a2->next);
    else
        return 1;
}

int compare_args(ARGS *a1,ARGS *a2){
    if(a1->num != a2->num)
        return 0;
    int a;
    a =compare_arg(a1->tail, a2->tail);
    return a;
        
}
void finish_arg (ARG *S) { // libera memoria para un_arg 
        
       free(S);
 }
/**********************************************
 *********Este es importante*******************
 *********************************************
 Crea un nuevo simbolo, lo añade a la cola de la tabla de simbolos y 
 apunta a la anterior cola de la tabla en el argumento next
 
 
 */
SYM *putsym (SYMTAB * STG, char *name){
    SYM *nuevosym;
    nuevosym = malloc(sizeof(struct sym));
    nuevosym -> num =0;
    nuevosym ->id = (char *) malloc(strlen(name)+1);
    strcpy(nuevosym->id, name);
    nuevosym->offset = data_location();
    nuevosym->next = STG->tail;
    STG->tail = nuevosym;
    STG->num++;
    return nuevosym;
}
 


SSTACK *init_sym_tab_stack ()  //Reserva memoria para una_tabla de simbolos vacia
{
    SSTACK *nuevosymtab;
    nuevosymtab = malloc(sizeof(struct sym_stack));
    return nuevosymtab;
}


/* Pone el nuevo simbolo en la cola
 la cola de NUEVA guarda la anterior cola en su next
 H <-  <-  <- T
 S1  S2  S3  S4
 */
// void append_sym(SYMTAB *t ,SYM *s )//añade un simbolo al final
// {
//     if(t->tail != NULL)
//         s->next =t->tail;
//     t->tail=s;
//     t->num++;
//     if(t->head==NULL)
//     t->head=s;
// }



void clear_sym_tab(SYMTAB *t )
{
    SYM *temp;
    while (t->tail != NULL){
         temp = t->tail->next;
         free (t->tail);
        t->tail = temp;
    }
    free (t->head);
    free (t->tail);
    free (t);
}
/**************************************
 compara un id recursivamente hasta encontrar y retornar un simbolo que coincida
 SI no  regresa un NULL
 
 */
SYM * comp_sym (SYM *S, char *id){
assert ( S != NULL);
    if(strcmp(S->id,id)==0)
        return S;
    if(S->next != NULL)
        comp_sym(S -> next, id);
    else return NULL;
}
/**************************************
 regresa un simbolo con el id dado, si es que existe
 
 */
SYM * getsym (SYMTAB *STG, char *id)
{
   SYM * S;
    if (STG->tail == NULL){
        return 0;
    }
    S = comp_sym(STG -> tail, id);

    if (S != NULL)
        return S;
    else 
        return 0;

}


int getDir (SYMTAB *T ,char *id ){
    SYM * S;
    S = comp_sym(T -> tail, id);
    if (S != NULL)
        return S->dir;
}

int getTipo(SYMTAB *T ,char *id )
{
    SYM * S;
    S = comp_sym(T -> tail, id);
    if (S != NULL)
        return S->tipo;
}

int getVar(SYMTAB *T ,char *id )
{
    SYM * S;
    S = comp_sym(T -> tail, id);
    if (S != NULL)
        return S->var;
}


int getNumArgs(SYMTAB *T ,char *id )
{
    SYM * S;
    S = comp_sym(T -> tail, id);
    if (S != NULL)
        return S->num;
}

void print_tab (SYMTAB *t ) //imprime tablas de simbolos
{
    SYM *s;
    printf("Pos\tID\ttipo\tdir\tvar\tnum\n");
    int i;
    i = t->num;
    for ( s = t->tail;
        s != NULL;
        s = s->next){
    printf("%i\t", i);
    printf("%s\t", s->id);
    printf("%i\t", s->tipo);
    printf("%i\t", s-> dir);
    printf("%i\t", s->var);
    printf("%i\n", s->num);
    i= i-1;
    }
}
/* 
Pos ID tipo dir var arg num 
0   x   0   0   var -   -
1   y   1   4   var -   -
 */


