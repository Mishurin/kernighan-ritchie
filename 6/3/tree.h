typedef struct llnode {
    int line;
    int count;
    struct llnode *next;
} llnode;

typedef struct tnode
{
    char *word;
    int count;
    struct tnode *left;
    struct tnode *right;
    llnode *lines;
    int wcount;
} tnode;

tnode *addtree(tnode *p, char *w, int line);
tnode *talloc(void);
void treeprint(tnode *p);
void freetree(tnode *p);

llnode *addllnode(int line, llnode **head);
llnode *find_in_llist(int line, llnode *head);
int freellist(llnode **head);
llnode *removellnode(llnode **head);