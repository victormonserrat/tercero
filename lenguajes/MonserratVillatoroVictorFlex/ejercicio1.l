number    [0-9]*
nan       .|\n

%%

{number} {
  int n;
  if((n = atoi(yytext)) % 4 == 0) {
    n += 5;
  }
  fprintf(yyout, "%i", n);
}

{nan} { fprintf(yyout, "%s", yytext); }

%%

int main(int argc, char const *argv[]) {
  char file[256];

  printf("%s", "\E[34mIntroduzca el nombre del \E[1mfichero de entrada\E[22m: \E[1m");
  scanf("%s", file);
  yyin = fopen(file, "r");

  printf("%s", "\E[22mIntroduzca el nombre del \E[1mfichero de salida\E[22m: \E[1m");
  scanf("%s", file);
  yyout = fopen(file, "w");

  yylex();
  fclose(yyin);
  fclose(yyout);

  printf("\E[0m");

  return 0;
}
