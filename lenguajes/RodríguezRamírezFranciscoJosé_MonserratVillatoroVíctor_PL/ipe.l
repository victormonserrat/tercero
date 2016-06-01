%{
#include "macros.h"
#include "ipe.h"
#include "ipe.tab.h"
extern char *progname;
extern int lineno;
char *cadena;
int size;
%}
/* definiciones regulares */
numero        [0-9]
letra         [a-zA-Z]
identificador {letra}(_?({letra}|{numero}))*

%x ESTADO_CADENA
%x ESTADO_COMENTARIO

%%
[ \t] { ; } /* saltar los espacios y los tabuladores */

(?i:_mod)            {return _MOD;}
(?i:_div)            {return _DIV;}
(?i:_o)              {return _O;}
(?i:_y)              {return _Y;}
(?i:_no)             {return _NO;}
(?i:leer)            {return LEER;}
(?i:leer_cadena)     {return LEER_CADENA;}
(?i:escribir)        {return ESCRIBIR;}
(?i:escribir_cadena) {return ESCRIBIR_CADENA;}
(?i:SI)              {return SI;}
(?i:entonces)        {return ENTONCES;}
(?i:si_no)           {return SI_NO;}
(?i:fin_si)          {return FIN_SI;}
(?i:mientras)        {return MIENTRAS;}
(?i:hacer)           {return HACER;}
(?i:fin_mientras)    {return FIN_MIENTRAS;}
(?i:repetir)         {return REPETIR;}
(?i:hasta)           {return HASTA;}
(?i:para)            {return PARA;}
(?i:desde)           {return DESDE;}
(?i:paso)            {return PASO;}
(?i:fin_para)        {return FIN_PARA;}
(?i:_borrar)         {return _BORRAR;}
(?i:_lugar)          {return _LUGAR;}

{numero}+(\.{numero}+)?([eE][+-]?{numero}+)? {double d;
                                   sscanf(yytext,"%lf",&d);
                                 /* Instala el numero en la tabla de simbolos */
				   yylval.sym=install("",NUMBER,d);
				   return NUMBER;}

{identificador} { Symbol *s;
                   if ((s=lookup(yytext)) == 0)
                               s = install (yytext, INDEFINIDA, 0.0);
                    yylval.sym = s;
                    return s->tipo == INDEFINIDA ? VAR : s->tipo;}

"\'" {
  BEGIN ESTADO_CADENA;
  cadena = (char *) malloc(sizeof(char));
  size = 0;
}

<ESTADO_CADENA>"\'" {
  cadena = (char *) realloc(cadena, (size+1)*sizeof(char));
  cadena[size] = '\0';
  yylval.sym=installcadena("",CADENA,cadena);
  free(cadena);
  BEGIN 0;
  return CADENA;
}

<ESTADO_CADENA>"\\\'" {
  cadena = (char *) realloc(cadena, (size+1)*sizeof(char));
  cadena[size] = '\'';
  size++;
}

<ESTADO_CADENA>"\\n" {
  cadena = (char *) realloc(cadena, (size+1)*sizeof(char));
  cadena[size] = '\n';
  size++;
}

<ESTADO_CADENA>"\\t" {
  cadena = (char *) realloc(cadena, (size+1)*sizeof(char));
  cadena[size] = '\t';
  size++;
}

<ESTADO_CADENA>. {
  cadena = (char *) realloc(cadena, (size+1)*sizeof(char));
  cadena[size] = *yytext;
  size++;
}

<ESTADO_CADENA>\n {
  cadena = (char *) realloc(cadena, (size+1)*sizeof(char));
  cadena[size] = *yytext;
  size++;
  lineno++;
}

"||" {return CONCATENACION;}
"**" {return POTENCIA;}

">="	{return MAYOR_IGUAL;}
"<="	{return MENOR_IGUAL;}
"="	{return IGUAL;}
"<>"	{return DISTINTO;}
">"	{return MAYOR_QUE;}
"<"	{return MENOR_QUE;}
":="      {return ASIGNACION;}

"#" {
  BEGIN ESTADO_COMENTARIO;
}

<ESTADO_COMENTARIO>"#" {
  BEGIN 0;
}

<ESTADO_COMENTARIO>.|\n {lineno++;}

"@".* {;}

<<EOF>>       {
  	  return 0;
	}
\n      {lineno++; } /* no se devuelve nada, contin�a el analisis l�xico */
.       {return yytext[0];}
