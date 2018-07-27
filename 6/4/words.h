#define EOL '\n'
#define NKEYS (sizeof BLACKLIST / sizeof(BLACKLIST[0]))

int getword(char *word, int lim);
int is_word_in_black_list(char *word);