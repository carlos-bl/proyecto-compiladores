/*Carlos Badillo Lora*/


#include <stdio.h>
typedef struct index INDEX; 
typedef struct list_index LINDEX;
//esta va a ser el tipo de las etiquetas me supongo
struct index{
    char * indice;
    INDEX *next;
};

//esta va a ser el tipo de truelist, falselist, nextlist
struct list_index{
    INDEX *head;
    INDEX *tail;
}; 
//Reserva memoria para un node de inidice

INDEX *init_index(){  
    INDEX *miIndex =  malloc(sizeof(INDEX));
    return miIndex;
}

//Reserva memoria para la lista de inidices e inserta el primero
LINDEX *init_list_index (){ 
    LINDEX * miLindex =  malloc(sizeof(LINDEX));
    return miLindex;
}

//Agrega un nodo indice al final de la lista
void append_index(LINDEX* l, INDEX * i){
    l->head = i;
    l->tail = i;
}




/*
// Libera la memoria de un nodo indice
void fnisih_index(INDEX *l); 

 // Libera la memoria de la lista y de todos los nodos dentro
void finish_list_index (CODE *C);



// retorna una lista ligada de la concatenación de l1 con l2
LINDEX *combinar(LINDEX l1, LINDEX l2) 

// Reemplaza label en cada aparicion de un indice en la cuadruplas del codigo c
void backpatch(CODE  *c, LINDEX l, char *label);
*/
