#define NKEYS (sizeof keytab / sizeof(keytab[0]))
char *binsearch(char *word, char *keys[], int n);
int is_keyword(char *word);