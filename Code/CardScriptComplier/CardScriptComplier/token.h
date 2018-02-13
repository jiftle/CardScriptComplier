#pragma once
/*
* 作用：单词符号类
* 作者：李旭
* 日期：2017.5.17
*/
#include "lib.h"

//==============================关键字===================================
static char* cnt_keyword[] = {
	"if","else","return","null"
};
static int cnt_keyword_size = 4;

//==============================运算符===================================
static char* cnt_operator[] = {
	"==", "!=", "<", "<=" //关系运算符
	, "+", "-", "*", "/", "%", "&", "|","^" //算术运算符
	, "&&", "||" //逻辑运算符
	,">" //赋值符
};
static int cnt_operator_size = 15;

//==============================界符=====================================
static char cnt_delimiter[] = {
	'#', //常量
	'$' //参数
	,'{'  //变量
	,'}'
	,','
	,'('
	,')'
};
static int cnt_delimiter_size = 7;

//===============================空格==============================
static char* cnt_blank[] = {
	" " //空格
	,"\t" //制表符
};
static int cnt_blank_size = 2;

//===============================注释==============================
static char* cnt_comment[] = {
	";"//注释
};
static int cnt_comment_size = 1;

//===============================种别码1-10==============================
#define TOKEN_DELIMITER_CNT 1 //常量#
#define TOKEN_DELIMITER_ARG   2 //参数$
#define TOKEN_DELIMITER_RES   3 //系统内置变量
#define TOKEN_DELIMITER_VAR_LEFT   4 //变量Left {
#define TOKEN_DELIMITER_VAR_RIGHT   5 //变量Right
#define TOKEN_DELIMITER_FUNC_LEFT   6 //函数Left (
#define TOKEN_DELIMITER_FUNC_RIGHT   7 //函数Right )
#define TOKEN_DELIMITER_COMMA          8 //逗号
#define TOKEN_KEYWORD_ID          9 //标识符
#define TOKEN_KEYWORD_CRLF          10 //换行
#define TOKEN_VAR			11 //变量
#define TOKEN_CMD			12 //命令
#define TOKEN_EVEL  100 //赋值

//==============================运算符20-60===================================
#define TOKEN_RELATE_EQUAL              21 //相等
#define TOKEN_RELATE_NOT_EQUAL          22 //不相等
#define TOKEN_RELATE_LESS               23 //小于
#define TOKEN_RELATE_LESS_EQUAL         24 //小于等于

//算术运算符
#define TOKEN_ADD   31 //加
#define TOKEN_SUB   32 //减
#define TOKEN_MUL   33 //乘
#define TOKEN_DIV   34 //除
#define TOKEN_MOD   35 //取模

//位运算
#define TOKEN_BIN_AND   41 //and
#define TOKEN_BIN_OR    42 //or
#define TOKEN_BIN_XOR   43 //xor

//逻辑运算
#define TOKEN_AND       51
#define TOKEN_OR        52

//==============================关键字70-80===================================
//关键字 "if","else","return","null"
#define TOKEN_KEYWORD_IF        71
#define TOKEN_KEYWORD_ELSE      72
#define TOKEN_KEYWORD_RETURN    73
#define TOKEN_KEYWORD_NULL      74


#define TOKEN_STRING    222
#define TOKEN_FUNC    221

//获得种别码
int get_token_type(char* p);
//获得类别
void get_token_str(int syn,char* name);