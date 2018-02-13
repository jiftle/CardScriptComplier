#pragma once
/*
* 作用：词法分析器
* 作者：李旭
* 日期：2017.5.17
*/


/* 全局符号表 */

//-------------------------宏定义-----------------------------
#define LEX_PRINT_FILE			1  //词法分析结果写入到文件
#define TEST_USE_FILE		    1  //使用文件测试
#define TEST_SHOW_DEBUG			0  //显示调试信息

/* 变量 */
typedef struct Var {
	char name[128]; //变量名
	char value[1024]; //变量值
}Var;


/* 代码行 */
typedef struct Line {
	int line_number; //行号
	char line_context[1024]; //内容
}Line;

//全局变量
#define GOBAL_VAR_SIZE			 10
struct Var gobal_var[GOBAL_VAR_SIZE];
int gobal_var_index;



/* 单词符号 */
typedef struct Token {
	int syn;//种别码
	char name[50]; //token类型，文字描述 eg. id,num
	char token[512]; //单词符号
	int sum;//整型单词
}Token;


//------------------------------词法分析的结果-----------------------
/* 词法分析结果 */
typedef struct Node {
	int line; //行c
	int column; //列
	struct Token token;
	struct Node* pre;
	struct Node* next;
}Node;

//词法分析结果
Node* gobal_lex_LinkList_head;
Node* gobal_lex_LinkList_tail;//尾部指针
Node* gobal_lex_LinkList_cur;


//-------------------------------错误信息-----------------------------
/* 错误信息 */
typedef struct Error {
	int errcode;
	char descript[512];
	int line; //行
	int column; //列
}Error;


/* 语法分析结果 */
typedef struct Grammar {
	struct Node node;
	int endflag; //结束标记
	struct Grammar* pre;
	struct Grammar* next;
}Grammar;

//语法结果链表
Grammar* gobal_grammar_LinkList_head;
Grammar* gobal_grammar_LinkList_tail;
Grammar* gobal_grammar_LinkList_cur;
int gobal_grammar_LinkList_size;

/* 语法分析四元式 */
typedef struct Quad {
	char op[5];
	char arg1[512];
	char arg2[512];
	char result[1024];

	struct Quad* pre;
	struct Quad* next;
}Quad;

/* 全局四元式表 */
Quad* gobal_quad_list_head;
Quad* gobal_quad_list_tail;

//参数
typedef struct Arg {
	char name[30];
	char value[50];
	struct Arg* next;
}Arg;

//参数列表
Arg gobal_arg_LinkList[10];
int gobal_arg_LinkList_index;
#define GOBAL_ARG_LINKLIST_SIZE    10

//常量
typedef struct Cnt {
	char name[30];
	int value;
}Cnt;

//常量列表
Cnt gobal_cnt_list[10];
int gobal_cnt_index;
#define GOBAL_CNT_LIST_SIZE    10
