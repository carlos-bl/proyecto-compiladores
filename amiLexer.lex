/*Carlos Badillo Lora*/
%{

#include <string.h>         /* se usara strdup                                */
/*#include <stdlib.h> */    
#include "amiParser.tab.h" /* De aqui se sacan las constantes que se devuelven con return*/
%}
/*=========================================================================
                TOKENS
=========================================================================*/
letra [a-zA-Z]
digito [0-9]
numero {digito}+
ID ({letra}+({digito}|{letra})*)

/*=========================================================================
    EXPRESIONES REGULARES
=========================================================================*/
%%

skip        { return(SKIP);  /*para debug*/       }



    /*comentario debe estar identado*/

":="        { return(ASIGNACION);      }

{numero}+    { yylval.intval = atoi( yytext );
                return(NUMBER);     }


sino        { return(SINO);         }
fin         { return(FIN);          
printf(" FIN ");  
return( FIN);
}

entonces    { 
printf(" ENTONCES ");  
return( ENTONCES);
}

entero         { return(TIPO_ENT);          }

escribe     { return(ESCRIBE);      }



def         { return(DEF);          }

inicio      { return(INICIO);       }
sin         { return(SIN);          }


mientras    { return( MIENTRAS);    }
hacer       { return( HACER );      }
leer        { return( LEER);        }
verdadero   {    
printf(" VERDADERO ");  
return( VERDADERO);
}
falso       { return( FALSO);       }
">="        { return( MAYOR_IGUAL );}
"<="        { return( MENOR_IGUAL );}
"<>"        { return( DIFERENTE );  }


si          { 
printf(" SI ");  
return( SI);
}
o           { return( O );          }
y           { return( Y );          }
no          { return( NO  );        }

{ID}        { yylval.id = (char *) strdup(yytext);
            return(IDENTIFIER);     }


[ \t\n]+ /* ignora los espacios */
.           { return(yytext[0]);}



%%
int yywrap(void){} //para que es esto

