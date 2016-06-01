#ifndef IPE_H
#define IPE_H

 /* ipe.h */


int yylex();

void yyerror(char *s);

void warning(char *s, char *t);

void execerror(char *s,char *t);

void init();

typedef struct Symbol
            { /* elementos de la tabla de simbolos */
	        char *nombre;
	        short tipo; /* NUMBER,VAR,FUNCION,INDEFINIDA,CONSTANTE */
          short subtipo; /* NUMBER, CADENA */
	        struct {
		       double val;      /* VAR, NUMBER, INDEFINIDA, CONSTANTE */
           char *cad;         /* CADENA */
		       double (*ptr)(); /* FUNCION  */
		      } u;
                 struct Symbol *siguiente;
	     } Symbol;

Symbol *install(), *lookup(), *installcadena();
char *emalloc(unsigned n);

typedef struct Datum { /* tipo de la pila del interprete */
                     short tipo; /* NUMBER,VAR,FUNCION,INDEFINIDA,CONSTANTE */
                     short subtipo; /* NUMBER, CADENA */
                     double val;
                     char *cad;
                     Symbol *sym;
                    } Datum;

void push(Datum d);
extern Datum pop();
extern void pop2();

typedef void (*Inst)(); /* instruccion maquina */
#define STOP (Inst) 0

extern Inst prog[];

/* NOVEDAD */
extern Inst* progp;

void initcode();

Inst *code(Inst f);

void execute(Inst *p);

/**************************/
extern void assign();
extern void constpush();
extern void cadenapush();
void dividir();
void dividirenteros();
void escribir();
void escribircadena();
void eval();

void funcion();
void funcion0();
void funcion1();
void funcion2();


void modulo();
void multiplicar();
void negativo();
void positivo();
void potencia();
void restar();
void sumar();
void concatenacion();
void varpush();

void ifcode();
void whilecode();
void repetircode();
void paracode();

void mayor_que();
void menor_que();
void mayor_igual();
void menor_igual();
void igual();
void distinto();
void y_logico();
void o_logico();
void negacion();

void leervariable();
void leercadena();

void borrar();
void lugar();

#endif
