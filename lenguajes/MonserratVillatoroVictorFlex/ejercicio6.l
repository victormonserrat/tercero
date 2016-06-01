%{

unsigned int option = 0;
char         user[256];
char         rUser[256];
char         rFile[256];
unsigned int nFiles = 0;
char         date[256];
char         rDate[256];

%}

string [a-zA-Zá-úÁ-Úà-ùÀ-Ùâ-ûÂ-Ûä-üÄ-ÜñÑçÇ&0-9\-_]+
user [a-zA-Zá-úÁ-Úà-ùÀ-Ùâ-ûÂ-Ûä-üÄ-ÜñÑçÇ&]{string}
file {string}\.{string}
date [0-3][0-9]\-[0-1][0-9]\-[0-9]{4,4}
time [0-2][0-9]:[0-5][0-9]

%%

{user} {
  strcpy(rUser, yytext);
}

{file} {
  strcpy(rFile, yytext);
}

{date} {
  strcpy(rDate, yytext);
  if(strcmp(rUser, user) == 0) {
    if(option == 0) {
      nFiles++;
    } else {
      if(strcmp(rDate, date) == 0) {
        nFiles++;
      }
    }
  }
}

.|\n

%%

int main(int argc, char const *argv[]) {
  if(argc != 3 && argc != 4) {
    printf("%s\n", "\E[31mUso del programa: \E[1m<input_file> <user> [date]\E[0m");
    return -1;
  }
  yyin = fopen(argv[1], "r");
  strcpy(user, argv[2]);

  if(argc == 4) {
    strcpy(date, argv[3]);
    option = 1;
  }

  yylex();
  fclose(yyin);

  printf("%s%s%s%i%s", "\E[35mEl usuario \E[1m", user, "\E[22m ha imprimido \E[1m", nFiles, "\E[22m trabajos");
  if(option == 1) {
    printf("%s%s", "\E[22m el día \E[1m", date);
  }
  printf("\n");

  printf("\E[0m");

  return 0;
}
