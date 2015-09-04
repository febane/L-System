
#define FREE(p) if(p!=NULL){free(p);p=NULL;}

#define EXIT(msgStr) {fprintf(stderr,"\n%s\nExitus...\n",msgStr);exit(1);}
#define STRLEN 200
#define WAIT  {char _str[STRLEN+1];fprintf(stderr,"...");\
	if(fgets(_str,STRLEN,stdin)==NULL) {EXIT("Problems with 'fgets'")};}


#define BRACE_OPEN '{'
#define BRACE_CLOSE '}'
#define BRACE_CLOSE_STR "}"
#define SLASH '/'	
	
typedef char str[STRLEN+1];

typedef enum {FALSE = 0, TRUE} boolean;

typedef unsigned int uint;


// Keywords
typedef enum {ANGLE, ORDER, ROTATE, AXIOM, RULE, EMPTY} keyval;


typedef struct keyword	{
	const keyval key;
	const char *keystr;
	const int offset;
} Keyword;


typedef struct rule {
	char lhs;
	char *rhs;
	size_t lenrhs;
	struct rule *next;
} Rule;


typedef enum {PREORDER, INORDER, POSORDER} treeorder;


