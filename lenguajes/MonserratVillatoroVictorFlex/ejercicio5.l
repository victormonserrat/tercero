%{

char current[256], new[256], buffer[1024] = "";

%}

word [a-zA-Zá-úÁ-Úà-ùÀ-Ùâ-ûÂ-Ûä-üÄ-ÜñÑçÇ&\-]+
naw  .|\n

%%

{word} {
  if(strcmp(yytext, current) == 0) {
    strcat(buffer, new);
  } else {
    strcat(buffer, yytext);
  }
}

{naw} { strcat(buffer, yytext); }

%%

int main(int argc, char const *argv[]) {
  char file[256];

  printf("%s", "\E[34mIntroduzca el nombre del \E[1mfichero de entrada\E[22m: \E[1m");
  scanf("%s", file);
  yyin = fopen(file, "r");

  printf("%s", "\E[22mIntroduzca la \E[1mpalabra que desea sustituir\E[22m: \E[1m");
  scanf("%s", current);

  printf("%s", "\E[22mIntroduzca la \E[1mpalabra reemplazadora\E[22m: \E[1m");
  scanf("%s", new);

  yylex();

  fclose(yyin);

  yyout = fopen(file, "w");
  fprintf(yyout, "%s", buffer);
  fclose(yyout);

  printf("\E[0m");

  return 0;
}
