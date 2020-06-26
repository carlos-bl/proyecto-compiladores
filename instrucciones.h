/*Carlos Badillo Lora*/

/* Representación interna de las operación */

enum code_ops { HALT, STORE, JMP_FALSE, GOTO,
                DATA, LD_INT, LD_VAR,
                READ_INT, WRITE_INT,
                LT, EQ, GT, ADD, SUB, MULT, DIV, PWR };

/* Representación externa de las operaciones */

char *op_name[] = {"halt", "store", "jmp_false", "goto",
                    "datos", "ld_int", "carga_var",
                    "lee", "escribe",
                "menor_que", "igual", "mayor_que", "suma", "resta", "mult", "div", "pwr" };
struct instruction
{
    enum code_ops op;
    int arg;
};

struct cuad {
    enum code_ops op;
    int  arg1;
    int  arg2;
    int  res;
    //CUAD *next;
};

/* En este arreglo se guardan las instrucciones generadas */



//arreglo de cuadruplas
struct cuad arr_cuad[999];


