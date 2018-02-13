/* 语法分析器 */
#include "lib.h"

//打印错误
void print_error(Error error);

void lr_parser();

//语句分析
void statement(Node** pnode);

//因子
void factor();

//表达式
void expression(Node** pnode, Node* pHead, Node* pTail);

//打印错误
void print_error(Error error);

//赋值
void evel(Node** pnode);

//语法节点
void print_grammar(Grammar* pGrammar, int is_end);

//填入四元式表格
void emit(char *op, char* arg1, char* arg2, char* result);

//函数求值
void funcment(Node** pnode, char *func_name);
