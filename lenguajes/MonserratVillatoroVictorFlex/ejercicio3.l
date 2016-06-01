%{

unsigned int nChars = 0;
unsigned int nWords = 0;
unsigned int nLines = 0;

%}

word [a-zA-Zá-úÁ-Úà-ùÀ-Ùâ-ûÂ-Ûä-üÄ-ÜñÑçÇ&\-]+
line \n
char .

%%

{word} {
  nWords++;
  for(size_t i = 0; i < yyleng; i++) {
    if(yytext[i] != -61) {
      nChars++;
    }
  }
}

{line} {
  nLines++;
}

{char} {
  nChars++;
}

%%

int main(int argc, char const *argv[]) {
  char file[256];

  printf("%s", "\E[34mIntroduzca el nombre del \E[1mfichero de entrada\E[22m: \E[1m");
  scanf("%s", file);
  yyin = fopen(file, "r");

  yylex();
  fclose(yyin);

  printf("%s%i\n", "\E[35m\E[22mNúmero de \E[1mcaracteres\E[22m: \E[1m", nChars);
  printf("%s%i\n", "\E[22mNúmero de \E[1mpalabras\E[22m: \E[1m", nWords);
  printf("%s%i\n", "\E[22mNúmero de \E[1mlíneas\E[22m: \E[1m", nLines);

  printf("\E[0m");

  return 0;
}
