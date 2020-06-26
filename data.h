/*Carlos Badillo Lora*/
typedef struct arg ARG;

struct arg{
int arg;
ARG *next ;
};

typedef struct args{
ARG *head;
ARG * tail ;
int num; // numero de elementos en la lista
} ARGS;

typedef struct sym SYM;
struct sym{
int dir ; //direccion para la variable
int tipo ; // tipo como indice a la_tabla de tipos
char *id ; // identificador
ARGS *args ; // Lista de argumentos
int num; // numero de argumentos
int var ; // tipo de variable
SYM *next ; // apuntador al siguiente simbolo
int offset;
};

typedef struct sym_tab SYMTAB;
struct sym_tab{
SYM *head;
SYM * tail ;
int num; //Numero de elementos en la_tabla
SYMTAB *next ; // apuntador a la_tabla siguiente
};

typedef struct sym_stack{
SYMTAB *top;
SYMTAB * tail ;
}SSTACK;

typedef struct tipobase{
int is_est ; // 1: s i es estructura 0: s i es tipo simple −1: s i no tiene tipo base
union{
SYMTAB *est ;
int tipo ;
} tipo ;
}TB ;

typedef struct type TYP ;
struct type{
int id ;
char nombre[12];
TB tb ;
int tam;
TYP *next ; //apuntador al siguiente tipo en la_tabla de tipos
};

typedef struct type_tab TYPTAB;
struct type_tab{
TYP *head;
TYP * tail ;
int num; //Contador de elementos en la_tabla
TYPTAB *next ; //apuntador a la_tabla siguiente
};

typedef struct typ_stack{
TYPTAB *top;
TYPTAB * tail ;
}TSTACK;
