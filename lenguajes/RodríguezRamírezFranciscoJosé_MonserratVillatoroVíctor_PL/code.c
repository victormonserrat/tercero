#include <stdio.h>
#include  <math.h>
#include <stdlib.h>
#include <string.h>

#include "ipe.h"
#include "ipe.tab.h"

#include "macros.h"

#define NSTACK 256              /* Dimension maxima de la pila */
static Datum stack[NSTACK];     /* La pila */
static Datum *stackp;           /* siguiente lugar libre en la pila */

#define NPROG 2000
Inst prog[NPROG];  /* La maquina */
Inst *progp;       /* Siguiente lugar libre para la generacion de codigo */

Inst *pc; /* Contador de programa durante la ejecucion */

void initcode() /* inicializacion para la generacion de codigo */
{
 stackp = stack;
 progp = prog;
}

void push(Datum d) /* meter d en la pila */
{

/* Comprobar que hay espacio en la pila para el nuevo valor o variable */

 if (stackp >= &stack[NSTACK])
     execerror (" Desborde superior de la pila ", (char *) 0);

 *stackp++ =d; /* Apilar la variable o el numero y */
               /* desplazar el puntero actual de la pila */
}


Datum pop() /* sacar y devolver de la pila el elemento de la cima */
{

/* Comprobar que no se intenta leer fuera de la pila */
/* En teoria no ocurrira nunca */

 if (stackp <= stack)
     execerror (" Desborde inferior de la pila ", (char *) 0);

 --stackp;          /* Volver hacia atras una posicion en la pila */
 return(*stackp);   /* Devolver variable o numero */
}

void pop2() /* sacar y  NO devolver el elemento de la cima de la pila */
{

/* Comprobar que no se intenta leer fuera de la pila */
/* En teoria no ocurrira nunca */

 if (stackp <= stack)
     execerror (" Desborde inferior de la pila ", (char *) 0);

 --stackp;          /* Volver hacia atras una posicion en la pila */
}

Inst *code(Inst f) /* Instalar una instruccion u operando */
{
 Inst *oprogp = progp;   /* Puntero auxiliar */

/* Comprobar que hay espacio en el vector de instrucciones */

 if (progp >= &prog[NPROG])
     execerror (" Programa demasiado grande", (char *) 0);

 *progp=f;        /* Asignar la instruccion o el puntero a la estructura */
 progp++;         /* Desplazar una posicion hacia adelante */
 return (oprogp);
}


void execute(Inst *p)  /* Ejecucion con la maquina */
{

/* El contador de programa pc se inicializa con la primera instruccion a */
/* ejecutar */

 for (pc=p; *pc != STOP;   )
    (*(*pc++))();              /* Ejecucion de la instruccion y desplazar */
}                              /* el contador de programa pc */

/****************************************************************************/
/****************************************************************************/

void assign() /* asignar el valor superior al siguiente valor */
{
 Datum d1,d2;
 d1=pop();    /* Obtener variable */
 d2=pop();    /* Obtener numero o cadena   */

 if (d1.sym->tipo != VAR && d1.sym->tipo != INDEFINIDA)
   execerror(" asignacion a un elemento que no es una variable ",
	     d1.sym->nombre);

  if (d2.subtipo == NUMBER) {
    d1.sym->u.val=d2.val;   /* Asignar valor   */
  } else if (d2.subtipo == CADENA) {
    d1.sym->u.cad = emalloc (strlen(d2.cad)*sizeof(char));
    strcpy(d1.sym->u.cad, d2.cad);   /* Asignar valor   */
  }
  d1.sym->tipo=VAR;
  d1.sym->subtipo = d2.subtipo;
  push(d2);               /* Apilar variable */
}

void constpush()  /* meter una constante en la pila */
{
 Datum d;

 d.val= ((Symbol *)*pc++)->u.val;
 d.subtipo = NUMBER;
 push(d);
}

void dividir() /* dividir los dos valores superiores de la pila */
{
 Datum d1,d2;

 d2=pop();      /* Obtener el primer numero  */
 d1=pop();      /* Obtener el segundo numero */

/* Comprobar si hay division por 0 */

 if (d2.val == 0.0)
     execerror (" Division por cero ", (char *) 0);

  if (d1.subtipo == CADENA || d2.subtipo == CADENA ) {
    execerror (" Division de cadenas ", (char *) 0);
  }

 d1.val = d1.val / d2.val;    /* Dividir             */
 push(d1);                    /* Apilar el resultado */
}

void dividirenteros() /* dividir los dos valores superiores de la pila */
{
 Datum d1,d2;

 d2=pop();      /* Obtener el primer numero  */
 d1=pop();      /* Obtener el segundo numero */

 if (d1.subtipo == CADENA || d2.subtipo == CADENA ) {
   execerror (" Division de cadenas ", (char *) 0);
 }

/* Comprobar si hay division por 0 */

  d1.val = (int) d1.val;
  d2.val = (int) d2.val;

 if (d2.val == 0)
     execerror (" Division por cero ", (char *) 0);

 d1.val = (int) d1.val / (int) d2.val;    /* Dividir             */
 push(d1);                    /* Apilar el resultado */
}

void escribir() /* sacar de la pila el valor superior y escribirlo */
{
 Datum d;

 d=pop();  /* Obtener numero */

 if (d.subtipo != NUMBER) {
   execerror (" Impresión de cadena ", (char *) 0);
 }

 printf("%.8g",d.val);
}

void escribircadena() /* sacar de la pila el valor superior y escribirlo */
{
  Datum d;

  d=pop();

  if (d.subtipo != CADENA) {
    execerror (" Impresión de número ", (char *) 0);
  }

  printf("%s",d.cad);
}

void eval() /* evaluar una variable en la pila */
{
 Datum d;

 d=pop();  /* Obtener variable de la pila */

/* Si la variable no esta definida */
 if (d.sym->tipo == INDEFINIDA)
     execerror (" Variable no definida ", d.sym->nombre);

 if (d.sym->subtipo == NUMBER) {
   d.val=d.sym->u.val;  /* Sustituir variable por valor */
 } else if (d.sym->subtipo == CADENA) {
   d.cad = emalloc (strlen(d.sym->u.cad)*sizeof(char));
   strcpy(d.cad, d.sym->u.cad);   /* Sustituir variable por valor */
 }
 push(d);             /* Apilar valor */
}

void funcion0() /* evaluar una funcion predefinida sin parametros */
{
 Datum d;

 d.val= (*(double (*)())(*pc++))();
 push(d);
}

void funcion1() /* evaluar una funcion predefinida con un parametro */
{
 Datum d;

 d=pop();  /* Obtener parametro para la funcion */

 d.val= (*(double (*)())(*pc++))(d.val);
 push(d);
}

void funcion2() /* evaluar una funcion predefinida con dos parametros */
{
 Datum d1,d2;

 d2=pop();  /* Obtener parametro para la funcion */
 d1=pop();  /* Obtener parametro para la funcion */

 d1.val= (*(double (*)())(*pc++))(d1.val,d2.val);
 push(d1);
}

/* resto de la division entera del segundo valor de la pila */
/* por el valor de la cima */
void modulo()
{
 Datum d1,d2;

 d2=pop();      /* Obtener el divisor */
 d1=pop();      /* Obtener el dividendo */

 if (d1.subtipo == CADENA || d2.subtipo == CADENA ) {
   execerror (" Módulo de cadenas ", (char *) 0);
 }

/* Comprobar si hay division por 0 */

 if (d2.val == 0.0)
     execerror (" Division por cero ", (char *) 0);

 d1.val = (int) d1.val % (int)  d2.val;  /* Resto */
 push(d1);                               /* Apilar el resultado */
}

void multiplicar() /* multiplicar los dos valores superiores de la pila */
{
 Datum d1,d2;

 d2=pop();                   /* Obtener el primer numero  */
 d1=pop();                   /* Obtener el segundo numero */

 if (d1.subtipo == CADENA || d2.subtipo == CADENA ) {
   execerror (" Producto de cadenas ", (char *) 0);
 }

 d1.val = d1.val * d2.val;   /* Multiplicar               */
 push(d1);                   /* Apilar el resultado       */
}

void negativo() /* negacion del valor superior de la pila */
{
 Datum d1;

 d1=pop();              /* Obtener numero   */

 if (d1.subtipo == CADENA) {
   execerror (" Negación de cadena ", (char *) 0);
 }

 d1.val = - d1.val;     /* Aplicar menos    */
 push(d1);              /* Apilar resultado */
}

/* Esta funcion se puede omitir   */
void positivo() /* tomar el valor positivo del elemento superior de la pila */
{
 Datum d1;

 d1=pop();              /* Obtener numero   */
 /* d1.val = + d1.val;*/     /* Aplicar mas    */

 if (d1.subtipo == CADENA) {
   execerror (" Positivización de cadena ", (char *) 0);
 }

 push(d1);              /* Apilar resultado */
}

void potencia()  /* exponenciacion de los valores superiores de la pila */
{
 Datum d1,d2;

 d2=pop();                      /* Obtener exponente   */
 d1=pop();                      /* Obtener base        */

 if (d1.subtipo == CADENA || d2.subtipo == CADENA ) {
   execerror (" Potencia de cadenas ", (char *) 0);
 }

 if ( (d1.val>=0) || ((int)d2.val == d2.val) )
  {
   d1.val = pow(d1.val,d2.val);   /* Elevar a potencia   */
   push(d1);                      /* Apilar el resultado */
  }
 else
  {
   char digitos[20];
   sprintf(digitos,"%lf",d1.val);
   execerror(" radicando negativo ", digitos);
  }

}

void restar()   /* restar los dos valores superiores de la pila */
{
 Datum d1,d2;

 d2=pop();                   /* Obtener el primer numero  */
 d1=pop();                   /* Obtener el segundo numero */

 if (d1.subtipo == CADENA || d2.subtipo == CADENA ) {
   execerror (" Resta de cadenas ", (char *) 0);
 }

 d1.val = d1.val - d2.val;   /* Restar                    */
 push(d1);                   /* Apilar el resultado       */
}

void sumar()   /* sumar los dos valores superiores de la pila */
{
 Datum d1,d2;

 d2=pop();                   /* Obtener el primer numero  */
 d1=pop();                   /* Obtener el segundo numero */

 if (d1.subtipo == CADENA || d2.subtipo == CADENA ) {
   execerror (" Suma de cadenas ", (char *) 0);
 }

 d1.val = d1.val + d2.val;   /* Sumar                     */
 push(d1);                   /* Apilar el resultado       */
}

void concatenacion() {
  Datum d1, d2;

  d2 = pop();
  d1 = pop();

  if (d1.subtipo != CADENA || d2.subtipo != CADENA) {
    execerror (" Concatenación de no cadenas ", (char *) 0);
  }

  strcat(d1.cad, d2.cad);
  push(d1);
}

void varpush()  /* meter una variable en la pila */
{
 Datum d;

 d.sym=(Symbol *)(*pc++);
 d.subtipo = d.sym->subtipo;
 push(d);
}
/****************************************************************************/
/****************************************************************************/

void leervariable() /* Leer una variable numerica por teclado */
{
 Symbol *variable;
 char c;

 variable = (Symbol *)(*pc);

 /* Se comprueba si el identificador es una variable */
  if ((variable->tipo == INDEFINIDA) || (variable->tipo == VAR))
    {
    while((c=getchar())=='\n') ;
    ungetc(c,stdin);
    scanf("%lf",&variable->u.val);
    variable->tipo=VAR;
    variable->subtipo=NUMBER;
    pc++;

   }
 else
     execerror("No es una variable",variable->nombre);
}

void leercadena() /* Leer una variable alfanumerica por teclado */
{
 Symbol *variable;
 char c;

 variable = (Symbol *)(*pc);

 /* Se comprueba si el identificador es una variable */
  if ((variable->tipo == INDEFINIDA) || (variable->tipo == VAR))
    {
    while((c=getchar())=='\n') ;
    ungetc(c,stdin);
    variable->u.cad = emalloc(1024*sizeof(char));
    fgets(variable->u.cad, 1024, stdin);
    variable->u.cad = (char *) realloc(variable->u.cad, (strlen(variable->u.cad))*sizeof(char));
    variable->u.cad[strlen(variable->u.cad)-1] = '\0';
    variable->tipo=VAR;
    variable->subtipo=CADENA;
    pc++;

   }
 else
     execerror("No es una variable",variable->nombre);
}

void mayor_que()
{
 Datum d1,d2;

 d2=pop();   /* Obtener el primer numero  */
 d1=pop();   /* Obtener el segundo numero */

 if (d1.subtipo != d2.subtipo) {
   execerror (" Comparación de distinto tipo ", (char *) 0);
 }

 if (d1.subtipo == NUMBER) {
   if (d1.val > d2.val)
     d1.val= 1;
   else
     d1.val=0;
 } else if (d1.subtipo == CADENA){
   if (strcmp(d1.cad, d2.cad) > 0)
     d1.val= 1;
   else
     d1.val=0;
 }

 push(d1);  /* Apilar resultado */
}


void menor_que()
{
 Datum d1,d2;

 d2=pop();    /* Obtener el primer numero  */
 d1=pop();    /* Obtener el segundo numero */

 if (d1.subtipo != d2.subtipo) {
   execerror (" Comparación de distinto tipo ", (char *) 0);
 }

 if (d1.subtipo == NUMBER) {
   if (d1.val < d2.val)
     d1.val= 1;
   else
     d1.val=0;
 } else if (d1.subtipo == CADENA){
   if (strcmp(d1.cad, d2.cad) < 0)
     d1.val= 1;
   else
     d1.val=0;
 }

 push(d1);    /* Apilar el resultado */
}


void igual()
{
 Datum d1,d2;

 d2=pop();    /* Obtener el primer numero  */
 d1=pop();    /* Obtener el segundo numero */

 if (d1.subtipo != d2.subtipo) {
   execerror (" Comparación de distinto tipo ", (char *) 0);
 }

 if (d1.subtipo == NUMBER) {
   if (d1.val == d2.val)
     d1.val= 1;
   else
     d1.val=0;
 } else if (d1.subtipo == CADENA){
   if (strcmp(d1.cad, d2.cad) == 0)
     d1.val= 1;
   else
     d1.val=0;
 }

 push(d1);    /* Apilar resultado */
}

void mayor_igual()
{
 Datum d1,d2;

 d2=pop();    /* Obtener el primer numero  */
 d1=pop();    /* Obtener el segundo numero */

 if (d1.subtipo != d2.subtipo) {
   execerror (" Comparación de distinto tipo ", (char *) 0);
 }

 if (d1.subtipo == NUMBER) {
   if (d1.val >= d2.val)
     d1.val= 1;
   else
     d1.val=0;
 } else if (d1.subtipo == CADENA){
   if (strcmp(d1.cad, d2.cad) >= 0)
     d1.val= 1;
   else
     d1.val=0;
 }

 push(d1);    /* Apilar resultado */
}


void menor_igual()
{
 Datum d1,d2;

 d2=pop();     /* Obtener el primer numero  */
 d1=pop();     /* Obtener el segundo numero */

 if (d1.subtipo != d2.subtipo) {
   execerror (" Comparación de distinto tipo ", (char *) 0);
 }

 if (d1.subtipo == NUMBER) {
   if (d1.val <= d2.val)
     d1.val= 1;
   else
     d1.val=0;
 } else if (d1.subtipo == CADENA){
   if (strcmp(d1.cad, d2.cad) <= 0)
     d1.val= 1;
   else
     d1.val=0;
 }

 push(d1);     /* Apilar resultado */
}

void distinto()
{
 Datum d1,d2;

 d2=pop();    /* Obtener el primer numero  */
 d1=pop();    /* Obtener el segundo numero */

 if (d1.subtipo != d2.subtipo) {
   execerror (" Comparación de distinto tipo ", (char *) 0);
 }

 if (d1.subtipo == NUMBER) {
   if (d1.val != d2.val)
     d1.val= 1;
   else
     d1.val=0;
 } else if (d1.subtipo == CADENA){
   if (strcmp(d1.cad, d2.cad) != 0)
     d1.val= 1;
   else
     d1.val=0;
 }

 push(d1);    /* Apilar resultado */
}


void y_logico()
{
 Datum d1,d2;

 d2=pop();    /* Obtener el primer numero  */
 d1=pop();    /* Obtener el segundo numero */

 if (d1.val==1 && d2.val==1)
   d1.val= 1;
 else
   d1.val=0;

 push(d1);    /* Apilar el resultado */
}


void o_logico()
{
 Datum d1,d2;

 d2=pop();    /* Obtener el primer numero  */
 d1=pop();    /* Obtener el segundo numero */

 if (d1.val==1 || d2.val==1)
   d1.val= 1;
 else
   d1.val=0;

 push(d1);    /* Apilar resultado */
}


void negacion()
{
 Datum d1;

 d1=pop();   /* Obtener numero */

 if (d1.val==0)
   d1.val= 1;
 else
   d1.val=0;

 push(d1);   /* Apilar resultado */
}


void whilecode()
{
 Datum d;
 Inst *savepc = pc;    /* Puntero auxiliar para guardar pc */

 execute(savepc+2);    /* Ejecutar codigo de la condicion */

 d=pop();    /* Obtener el resultado de la condicion de la pila */

 while(d.val)   /* Mientras se cumpla la condicion */
    {
     execute(*((Inst **)(savepc)));   /* Ejecutar codigo */
     execute(savepc+2);               /* Ejecutar condicion */
     d=pop();              /* Obtener el resultado de la condicion */
    }

/* Asignar a pc la posicion del vector de instrucciones que contiene */
/* la siguiente instruccion a ejecutar */

 pc= *((Inst **)(savepc+1));
}

void ifcode()
{
 Datum d;
 Inst *savepc = pc;   /* Puntero auxiliar para guardar pc */

 execute(savepc+3);   /* Ejecutar condicion */
 d=pop();             /* Obtener resultado de la condicion */


/* Si se cumple la condici\A2n ejecutar el cuerpo del if */

 if(d.val)
   execute(*((Inst **)(savepc)));

/* Si no se cumple la condicion se comprueba si existe parte else   */
/* Esto se logra ya que la segunda posicion reservada contendria el */
/* puntero a la primera instruccion del cuerpo del else en caso de  */
/* existir, si no existe sera\A0 STOP, porque a la hora de generar    */
/* codigo se inicializa con STOP.                                   */

 else if  (*((Inst **)(savepc+1)))  /* parte else */
   execute(*((Inst **)(savepc+1)));


/* Asignar a pc la posicion del vector de instrucciones que contiene */
/* la siguiente instruccion a ejecutar */

 pc= *((Inst **)(savepc+2));
}

void borrar() {
  BORRAR;
}

void lugar() {
  Datum d1, d2;

  d2 = pop();
  d1 = pop();

  LUGAR((int)d1.val, (int)d2.val);
}

void cadenapush() {
  Datum d;

  d.cad = emalloc(strlen(((Symbol *)*pc)->u.cad)*sizeof(char));
  strcpy(d.cad, ((Symbol *)*pc++)->u.cad);
  d.subtipo = CADENA;

  push(d);
}

void paracode() {
  Datum d, expr1, expr2, expr3;
  Inst *savepc = pc;
  Symbol *variable;

  variable = *((Symbol **)(savepc+5));
  variable->tipo = VAR;
  variable->subtipo = NUMBER;

  execute(*((Inst **)(savepc)));
  expr1 = pop();
  execute(*((Inst **)(savepc+1)));
  expr2 = pop();
  execute(*((Inst **)(savepc+2)));
  expr3 = pop();

  if (expr3.val == 0 ||
     (expr3.val > 0) && (expr1.val > expr2.val) ||
     (expr3.val < 0) && (expr1.val < expr2.val)) {
    execerror (" Bucle infinito ", (char *) 0);
  }
  if (expr3.val > 0) {
    for (variable->u.val = expr1.val; variable->u.val <= expr2.val; variable->u.val += expr3.val) {
      execute(*((Inst **)(savepc+3)));
    }
  } else {
    for (variable->u.val = expr1.val; variable->u.val >= expr2.val; variable->u.val -= expr3.val) {
      execute(*((Inst **)(savepc+3)));
    }
  }
}

void repetircode() {
  Datum d;
  Inst *savepc = pc;

  do {
    execute(savepc+2);
    execute(*((Inst **)(savepc)));
    d=pop();
  } while(!d.val);

  pc= *((Inst **)(savepc+1));
}
