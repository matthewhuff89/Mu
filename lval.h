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
enum lval_types { LVAL_NUM, LVAL_ERR, LVAL_SYM, LVAL_SEXPR, LVAL_QEXPR, LVAL_FUN };

lval* lval_num(long x);
lval* lval_err(char* fmt, ...);
lval* lval_sym(char* sym);
lval* lval_sexpr(void);
lval* lval_qexpr(void);
lval* lval_fun(lbuiltin fun);
void lval_del(lval* v);
lval* lval_eval_sexpr(struct lenv* e, lval* v);
lval* lval_eval(struct lenv* e, lval* v);
void lval_println(lval* v);
lval* lval_read_num(mpc_ast_t* t);
lval* lval_read(mpc_ast_t* t);
void lval_expr_print(lval* v, char open, char close);
void lval_print(lval* v);
lval* lval_pop(lval* v, int i);
lval* lval_take(lval* v, int i);
lval* lval_join(lval* x, lval* y);
lval* lval_copy(lval* v);
lval* lval_lambda(lval* formals, lval* body);
char* ltype_name(int t);

#endif