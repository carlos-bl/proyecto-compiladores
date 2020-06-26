/*Carlos Badillo Lora*/
/***************************************************************************
                        Generación de Código
***************************************************************************/
/*-------------------------------------------------------------------------
                        Segmento de Datos
-------------------------------------------------------------------------*/
int data_offset = 0;        /* Aquí se indicara la celda de memoria actual  */
int data_location()         /* Reserva una celda de memoria                 */
{
    return data_offset++;
}
/*-------------------------------------------------------------------------
                        Segmento de Código
-------------------------------------------------------------------------*/
int code_offset = 0;        /* Aquí se indica el número de instrucción actual  */
int gen_label()             /* Regresa el número de instrucción actual                    */
{
    return code_offset;
} 
int reserve_loc()           /* Rserva una celda de código, esto se usa para backpatching
                                se reserva la celda que después se llenará  */
{
    return code_offset++;
} 
                            /* Genera el código en la ubicación actual*/
void gen_code( enum code_ops operation, int arg )
{ arr_cuad[code_offset].op      = operation;
  arr_cuad[code_offset++].arg1   = arg;
}

                            
void genera_codigo( enum code_ops operation, int arg1, int arg2, int resultado)
{ arr_cuad[code_offset].op      = operation;
  arr_cuad[code_offset].arg1   = arg1;
  arr_cuad[code_offset].arg2   = arg2;
  arr_cuad[code_offset].res   = resultado;
  code_offset++;
}
                            /*Genera el código en una celda previamente reservada    */
void back_patch( int addr, enum code_ops operation, int arg )
{
    arr_cuad[addr].op = operation;
    arr_cuad[addr].arg1 = arg;
}
/*-------------------------------------------------------------------------
                   Imprime el código
-------------------------------------------------------------------------*/
void print_code()
{
    int i = 0;
        
        while (i < code_offset) {
            //printf("%3ld: %-10s%4ld\n",i,op_name[(int) arr_cuad[i].op], arr_cuad[i].arg1 );
            printf("%3ld: %-10s%4ld %d %d\n",i,op_name[(int) arr_cuad[i].op], arr_cuad[i].arg1,  arr_cuad[i].arg2, arr_cuad[i].res);
            i++;
    }
}

