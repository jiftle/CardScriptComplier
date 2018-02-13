#pragma once
/*
* 作用：工具类
* 作者：李旭
* 日期：2017.5.17
*/
#include "lib.h"

//是否行尾
int is_end(Node* pnode);

//是否是指令
int is_cmd(Node* pnode);

//是否是变量
int is_var(char* p);

//标识符
int is_id(char c);

//关键字
int is_keyword(char* p);

//操作符
int is_operator(char* p);

//界符
int is_delimiter(char c);

//空格
int is_blank(char c);

//取一个单词
int get_word(char* p, char* pOut);

//十六进制数
int is_hex(char c);

//十六进制串
int is_hex_str(char *p);

//取运算符
void get_operator(char* p, char* operator_word);

//注释
int is_comment(char* p);

//得到下一行位置
int get_next_line_pos(char* p);

//转换成大写
void str_to_upper(char* p);

//转换成小写
void str_to_lower(char* p);

//字母或数字
int is_letter_or_num(char c);

// 数字转十六进制字符串
// void 

//---------------------语法分析器工具----------------------------

//取常量
int get_next_const(Node* pnode, Cnt* pvar, Error* error);

//取参数
int get_next_arg(Node* pnode, Var* pvar, Error* error);

//取变量
int get_next_var(Node* pnode, Var* pvar, Error* error);

//检查函数是否匹配
int check_match_func(Node* pnode,Error* error);

//得到函数名
int get_func_name(Node* pnode, Var* var, Error* error);

//取被赋值变量名
int get_parser_result_name(Node** pnode,Var* var,Error* error);

//取之前的符号
int get_back_id(Node* pnode, Var* var, Error* error);

//是否是简单表达式
int is_simple_expression(Node* pHead,Node* pTail);

//取变量,移动指针
int get_next_var_movePoint(Node** pnode, Var* pvar, Error* error);

//字符串截取
void substring(char* ch, int pos, int length, char *out_data);

//字符串截取
void substring_2arg(char* ch, int pos, char *out_data);