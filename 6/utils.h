#define BUFSIZE 100
int getch(void);
void ungetch(int c);

void q_sort(void *v[], int left, int right, int (*comp)(void *, void *));
void swap(void *v[], int i, int j);
int str_cmp(char *s, char *t);