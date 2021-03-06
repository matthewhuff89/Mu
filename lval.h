#ifndef lval_h
#define lval_h

#include "mpc.h"
#include "builtin.h"
#include "lenv.h"

/* Declare new lval struct */
typedef struct lval lval;
struct lenv;
typedef lval*(*lbuiltin)(struct lenv*, lval*);

struct lval {
  int type;

  /* Basic */
  long num;
  char* err;
  char* sym;
  char* bool;
  char* str;

  /* Function */
  lbuiltin builtin;
  struct lenv* env;
  struct lval* formals;
  struct lval* body;

  /* Expression */
  int count;
  struct lval** cell;
};

/* Declare Enumerations for lval types */
enum lval_types { LVAL_NUM, LVAL_ERR, LVAL_SYM, LVAL_SEXPR, LVAL_QEXPR, LVAL_FUN, LVAL_BOOL, LVAL_STR };


/* Create lval declarations */
lval* lval_num(long num);
lval* lval_err(char* fmt, ...);
lval* lval_sym(char* sym);
lval* lval_bool(char* bool);
lval* lval_sexpr(void);
lval* lval_qexpr(void);
lval* lval_fun(lbuiltin fun);
lval* lval_str(char* str);

/* lval operations */
lval* lval_add(lval* val, lval* x);
void lval_del(lval* val);
lval* lval_pop(lval* val, int index);
lval* lval_take(lval* val, int index);
lval* lval_join(lval* x, lval* y);
lval* lval_copy(lval* val);
lval* lval_eq(lval* x, lval* y);


/* Read, Evaluate, Print functions */
lval* lval_eval_sexpr(struct lenv* env, lval* val);
lval* lval_eval(struct lenv* env, lval* val);
void lval_println(lval* val);
lval* lval_read_num(mpc_ast_t* tree);
lval* lval_read(mpc_ast_t* tree);
lval* lval_read_str(mpc_ast_t* tree);
void lval_expr_print(lval* val, char open, char close);
void lval_print(lval* val);
void lval_print_str(lval* val);

/* Function creation and calling */
lval* lval_lambda(lval* formals, lval* body);
lval* lval_call(struct lenv* env, lval* func, lval* args);

/* utils */
char* ltype_name(int type);

#endif
