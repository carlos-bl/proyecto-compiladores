%{
/*Carlos Badillo Lora*/
#include <stdio.h>     
#include <stdlib.h>         /* Aquí está malloc                                         */
#include <string.h>         /* Se usará strcmp en la tabla de símbolos                  */
#include "tabla_simbolos.h" /* Tabla de símboleos                                       */
#include "instrucciones.h"  /* Aquí se encuentran los códigos de instruccioń            */
#include "backpatch.h"         
#include "generador.h"      /* Generador de código                                      */
#define YYDEBUG 1       
int errors;                 /* Conteo de errores                                        */
SYMTAB *STG;                /* La tabla de símbolos                                        */

/*-------------------------------------------------------------------------
Esta estructura contiena las etiquetas que se usarán para el backpatching
-------------------------------------------------------------------------*/

struct lbs                              
{
    LINDEX* false_list;
    LINDEX* true_list;
};

// Aparta el espacio para las etiqutas 
struct lbs * newlblrec()              
{
    struct lbs * nuevalbls=  malloc(sizeof(struct lbs));
    nuevalbls->false_list = init_list_index();
    nuevalbls->true_list = init_list_index();

    return nuevalbls;
}


/*-------------------------------------------------------------------------
        Instala un identificador y revisar si ya se había definido antes
-------------------------------------------------------------------------*/

pon_simbolo ( char *sym_name, SYMTAB * STG)
{
    SYM *s;
    s = getsym (STG, sym_name);
    if (s == 0)
        s = putsym (STG, sym_name);
    else { errors++;
        printf( "%s ya fue definida\n", sym_name );
    }
}
/*-------------------------------------------------------------------------
        Si el identificador ya esta definido, general e código recibido
-------------------------------------------------------------------------*/
revisa_tabla( enum code_ops operation, char *sym_name,SYMTAB *STG)
{ SYM *identifier;
    identifier = getsym(STG, sym_name);
    if ( identifier == 0 )
        { errors++;
        printf( "%s", sym_name );
        printf( "%s\n", " es un identificador no declarado" );
        }
    else gen_code( operation, identifier->offset );
}
/*=========================================================================
            Estos son los atributos que tendrán las producciones
=========================================================================*/
%}
%union semrec           
{
    int     intval;     /* Enteros                                       */
    char    *id;        /* Identificadores                               */
    struct lbs *lbls;   /* Listas de etiquetas                           */
    int     direccion ;  /*aqui se guardaran las direcciones             */
}

/*=========================================================================
                              TOKENS
=========================================================================*/

//para debug
%token SKIP


//%start program_prueba
%start programa
%token HOLA          /* Simple integer                    */
%token TIPO_ENT

%token <intval>     NUMBER          /* Simple integer                    */
%token <id>         IDENTIFIER      /* Simple identifier                 */
%token <lbls>       SI MIENTRAS        /* For backpatching labels           */


//tokens para la funcion
%token DEF
%token INICIO
%token SIN

%token ASIGNACION
%token FIN
%token ENTONCES
%token SINO
%token ESCRIBE
%token NUM

//tokens sentencias
%token HACER 
%token LEER

//tokens booleanos
%token O 
%token Y 
%token NO  
%token VERDADERO
%token FALSO


//tokens relacionales 
%token MAYOR_IGUAL 
%token MENOR_IGUAL 
%token DIFERENTE 

/*=========================================================================
                            OPERATOR PRECEDENCE
=========================================================================*/
%left '-' '+'
%left '*' '/'
%right '%'

/*=========================================================================
                    GRAMMAR RULES for the Simple language
=========================================================================*/
%%

//program_prueba : HOLA { printf("hola");              };
programa : declaraciones { gen_code( DATA, data_location() - 1 );              }
 funciones { gen_code( HALT, 0 ); YYACCEPT;                      };
//programa : declaraciones                     ;
funciones : funcion funciones 
|//vacio
;

declaraciones : tipo lista_var ';' declaraciones  { /*printf(" declaracion\n "); */} 
| //vacio
;
tipo : base tipo_arreglo;
base : TIPO_ENT { /*printf(" entero ");*/};
tipo_arreglo : /* empty*/;
lista_var : lista_var ',' IDENTIFIER { /* printf(" ID ");*/ pon_simbolo( $3, STG);  } 
| IDENTIFIER { printf(" ID "); pon_simbolo( $1 ,STG);  } ;//introduce el simbolo en la tabla

funcion : DEF tipo IDENTIFIER '(' argumentos ')' INICIO declaraciones sentencias FIN {/* printf(" ffuncion \n");*/ }
//funciones : DEF tipo IDENTIFIER PAREN_IZQ argumentos PAREN_DER INICIO declaraciones FIN funciones { printf(" f ");              }
//| // empty
;

argumentos : lista_arg | SIN { /*printf(" sin "); */ };

lista_arg : lista_arg ',' arg | arg{ /*printf(" argumento ");*/ };
arg : tipo_arg IDENTIFIER;
tipo_arg: base param_arr;
param_arr : // empty
;

sentencias : sentencias sentencia | sentencia { /*printf(" sentencias\n ");*/ };

sentencia : SKIP

//| LEER variable ';' { revisa_tabla( READ_INT, $2 ,STG);              }
| LEER IDENTIFIER ';' { revisa_tabla( READ_INT, $2,STG );              }

| ESCRIBE exp ';'    { gen_code( WRITE_INT, 0 );  
                                              }

//| variable ASIGNACION exp ';'
| IDENTIFIER ASIGNACION exp ';' { revisa_tabla( STORE, $1,STG );                }

| SI e_bool                 {$<lbls>1 = newlblrec();

                             INDEX* nuevoIndex = init_index();
                             nuevoIndex->indice = reserve_loc();
                             append_index( $<lbls>1->false_list, nuevoIndex);

          }
 ENTONCES sentencia         {/*$1->for_goto = reserve_loc();*/

                                 INDEX* nuevoIndex = init_index();
                             nuevoIndex->indice = reserve_loc();
                             append_index( $1->true_list, nuevoIndex);
                                
                                           }
 SINO                       { /*back_patch( $1->for_jmp_false,
                                JMP_FALSE,
                                gen_label() );*/

                                back_patch( $1->false_list->head->indice,
                                JMP_FALSE,
                                gen_label() );}
 sentencia
 FIN                        { /*back_patch( $1->for_goto, GOTO, gen_label() );*/

                                back_patch( $1->true_list->head->indice, GOTO, gen_label() );        
                                
                                    }


| MIENTRAS                  { /*$1 = (struct lbs *) newlblrec();
                            $1->for_goto = gen_label();      */

                              $1 = (struct lbs *) newlblrec();
                             INDEX* nuevoIndex = init_index();
                             nuevoIndex->indice = reserve_loc();
                             append_index( $1->true_list, nuevoIndex);
                                                                  }

 e_bool                     { /*$1->for_jmp_false = reserve_loc();   */

                                    INDEX *nuevoIndex = init_index();
                             nuevoIndex->indice = reserve_loc();
                             append_index( $1->false_list, nuevoIndex);
                                       }
 HACER
 sentencia
 FIN                        { /*gen_code( GOTO, $1->for_goto );
                            back_patch( $1->for_jmp_false,
                                    JMP_FALSE,
                                    gen_label() );     */ 

                                gen_code( GOTO, $1->true_list->head->indice );
                            back_patch( $1->false_list->head->indice,
                                    JMP_FALSE,
                                    gen_label() );                 }




;

e_bool : e_bool O e_bool
| e_bool Y e_bool
| NO e_bool 
| relacional
| VERDADERO
| FALSO;


relacional : exp                             { /*printf(" expresion \n"); */   }
    | relacional '<' relacional             { genera_codigo( LT,     0, 1, 0 );                      }
    | relacional '>' relacional             { genera_codigo( GT,     0, 1, 0 );                      }
    | relacional '=' relacional             { genera_codigo( EQ,     0, 1, 0 );                      }
    | relacional MAYOR_IGUAL relacional     {     }
    | relacional MENOR_IGUAL relacional     {     }
    | relacional DIFERENTE relacional       {    }
;


exp : NUMBER                 { $<intval>$ = $1 ;                     }
//    | variable              { printf(" expresion \n");                      }
    | IDENTIFIER              { revisa_tabla( LD_VAR, $1,STG );                }
    | exp '+' exp           {     int direccionNueva = data_location();
                                 $<direccion>$= direccionNueva;//se reserva memoria para guardar la expresion
                                 genera_codigo( ADD,    $<intval>1, $<intval>3, direccionNueva );                      }
    | exp '-' exp           { int direccionNueva = data_location();
                                 $<direccion>$= direccionNueva;//se reserva memoria para guardar la expresion
                                 genera_codigo( SUB,    $<intval>1, $<intval>3, direccionNueva );                      }
    | exp '*' exp           { int direccionNueva = data_location();
                                 $<direccion>$= direccionNueva;//se reserva memoria para guardar la expresion
                                 genera_codigo( MULT,    $<intval>1, $<intval>3, direccionNueva );                      }
    | exp '/' exp           { int direccionNueva = data_location();
                                 $<direccion>$= direccionNueva;//se reserva memoria para guardar la expresion
                                 genera_codigo( DIV,    $<intval>1, $<intval>3, direccionNueva );                      }
    | exp '%' exp           {                     }
    | '(' exp ')'
;

//variable : IDENTIFIER variable_comp;
//variable_comp : // empty
//;

%%
/*=========================================================================
                            MAIN
=========================================================================*/
main( int argc, char *argv[] )
{ extern FILE *yyin;
STG = init_sym_tab();
    ++argv; --argc;
    yyin = fopen( argv[0], "r" );
    /*yydebug = 1;*/
    errors = 0;
    yyparse ();
    printf ( "Parsing completado\n" );
    if ( errors == 0 )
    { print_code ();
        printf("Termine sin errores\n");
    }
}
/*=========================================================================
                            YYERROR
=========================================================================*/
yyerror ( char *s ) /* Si hay un error el parser llama a esta función */
{
    errors++;
    printf ("%s\n", s);
}
