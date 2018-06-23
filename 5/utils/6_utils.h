#define NUMBER '0'
#define COMMAND '1'
#define VARIABLE '2'
#define ASSIGNMENT '3'
#define END_OF_LINE '\0'

int str_len(char *);
int get_line(char *, int);
int atoi(char *);
int atois(char *);
void itoa(int, char *);
void itoar(int, char *);
void swap(char *, char *);
void reverse(char *);
int strindex(char *, char *);
int getch(void);
void ungetch(int);
int getop(char *s);
