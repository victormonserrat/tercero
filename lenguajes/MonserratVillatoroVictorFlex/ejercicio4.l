%{

unsigned int nWords = 0;
char word[256];

%}

word [a-zA-Zá-úÁ-Úà-ùÀ-Ùâ-ûÂ-Ûä-üÄ-ÜñÑçÇ&\-]+

%%

{word} {
  if(strcmp(yytext, word) == 0) {
    nWords++;
  }
}

.|\n

%%

int main(int argc, char const *argv[]) {
  char file[256];

  printf("%s", "\E[34mIntroduzca el nombre del \E[1mfichero de entrada\E[22m: \E[1m");
  scanf("%s", file);
  yyin = fopen(file, "r");

  printf("%s", "\E[22mIntroduzca la \E[1mpalabra\E[22m que desea buscar: \E[1m");
  scanf("%s", word);

  yylex();
  fclose(yyin);

  printf("%s%i\n", "\E[35m\E[22mNúmero de \E[1mcoincidencias\E[22m: \E[1m", nWords);

  printf("\E[0m");

  return 0;
}
