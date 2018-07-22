typedef struct llnode {
    char *word;
    struct llnode *next;
} llnode;


llnode *addllnode(char *word, llnode **head, int *count);
llnode *removellnode(llnode **head, int *count);
int find_in_llist(char *word, llnode *head);
int freellist(llnode **head, int *count);
void llisttoarray(llnode *head, char *words[]);

typedef struct tnode
{
    char *word;
    int count;
    struct tnode *left;
    struct tnode *right;
    llnode *words;
    int wcount;
} tnode;

tnode *addtree(tnode *p, char *w, int n);
void treeprint(tnode *);
void varstobuffer(tnode *p);
void printvars();
tnode *talloc(void);
void freetree(tnode *p);
char *str_dup(char *);
