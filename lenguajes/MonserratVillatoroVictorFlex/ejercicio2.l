%{

int n1, n2;

%}

number    [0-9]*
nan       .|\n

%%

{number} {
  int n;
  if((n = atoi(yytext)) % n2 == 0) {
    n += n1;
  }
  fprintf(yyout, "%i", n);
}

{nan} { fprintf(yyout, "%s", yytext); }

%%

int main(int argc, char const *argv[]) {
  if(argc != 5) {
    printf("%s\n", "\E[31mUso del programa: \E[1m<input_file> <output_file> <n1> <n2>\E[0m");
    return -1;
  }
  n1 = atoi(argv[3]);
  n2 = atoi(argv[4]);
  yyin = fopen(argv[1], "r");
  yyout = fopen(argv[2], "w");

  yylex();
  fclose(yyin);
  fclose(yyout);

  printf("\E[0m");

  return 0;
}
