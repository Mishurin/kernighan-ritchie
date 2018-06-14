#define NUMBER '0'
#define COMMAND '1'
#define VARIABLE '2'
#define ASSIGNMENT '3'
#define END_OF_LINE '\0'
#define VARIABLES_MAX_RANGE 26
#define PRINT_STACK_COMMAND "printstack"
#define DUPLICATE_STACK_COMMAND "duplicatestack"
#define SWAP_FIRST_PAIR_COMMAND "swapfirstpair"
#define CLEAR_STACK_COMMAND "clearstack"
#define DRAW_RULLER_COMMAND "drawruller"
#define SIN_COMMAND "sin"
#define EXP_COMMAND "exp"
#define POW_COMMAND "pow"
#define RULLER "-----------------------------------------\n"

int getop(char[]);
void push(double);
double pop(void);
void printstack(int);
void duplicatestack(void);
void swapfirstpair(void);
void clearstack(void);
void process_command(char[]);
void process_variable(char, double[], double);
void process_assignment(char, double[]);
void drawruller(void);
int getch(void);
void ungetch(int);
int is_space(char);