
Carlos Badillo Lora 415083504

Para compilar:

bison -dv amiParser.y

gcc -c amiParser.tab.c

gcc -o miCompi amiParser.tab.o lex.yy.c
