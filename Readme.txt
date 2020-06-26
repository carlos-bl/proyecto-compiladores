
Carlos Badillo Lora 415083504

Para compilar:

bison -dv amiParser.y

gcc -c amiParser.tab.c

flex amiLexer.lex

gcc -o miCompi amiParser.tab.o lex.yy.c -lm

Los archivos llamados prueba estan escritos en el lenguaje del compilador. Sirven para probar su funcionamiento.
