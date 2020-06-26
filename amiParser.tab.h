/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YY_AMIPARSER_TAB_H_INCLUDED
# define YY_YY_AMIPARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    SKIP = 258,
    HOLA = 259,
    TIPO_ENT = 260,
    NUMBER = 261,
    IDENTIFIER = 262,
    SI = 263,
    MIENTRAS = 264,
    DEF = 265,
    INICIO = 266,
    SIN = 267,
    ASIGNACION = 268,
    FIN = 269,
    ENTONCES = 270,
    SINO = 271,
    ESCRIBE = 272,
    NUM = 273,
    HACER = 274,
    LEER = 275,
    O = 276,
    Y = 277,
    NO = 278,
    VERDADERO = 279,
    FALSO = 280,
    MAYOR_IGUAL = 281,
    MENOR_IGUAL = 282,
    DIFERENTE = 283
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
#line 66 "amiParser.y" /* yacc.c:1909  */
union semrec
{
#line 67 "amiParser.y" /* yacc.c:1909  */

    int     intval;     /* Enteros                                       */
    char    *id;        /* Identificadores                               */
    struct lbs *lbls;   /* Listas de etiquetas                           */
    int     direccion ;  /*aqui se guardaran las direcciones             */

#line 90 "amiParser.tab.h" /* yacc.c:1909  */
};
#line 66 "amiParser.y" /* yacc.c:1909  */
typedef union semrec YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_AMIPARSER_TAB_H_INCLUDED  */
