typedef struct tnode
{
    char *word;
    int count;
    struct tnode *left;
    struct tnode *right;
} tnode;

tnode *addtree(tnode *p, char *w);
tnode *talloc(void);
void freetree(tnode *p);
int get_wcount();
void treetoarr(tnode *p, tnode *arrpt[]);
int cmpbywcount(tnode *a, tnode *b);
void print_words(tnode *root);