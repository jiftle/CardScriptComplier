#pragma once

#include "lib.h"
/*
* 作用：词法分析器
* 作者：李旭
* 日期：2017.5.17
*/

/************************************************/
//  词法分析器
//  	作用：识别出独立的单词符号
//  	输入：给定文法的源程序字符串
//  	输出：二元组(syn,token或sum)构成的序列
//  	      syn 种别码
//  	      token 单词符号
//  	      sum 数字
/************************************************/



//扫描单行
void scaner_sigle_line(const char* pbuf, int lineno);

//打印记号
void print_token(int token_type, char* token_str, int token_sum, struct Line line, int cloumn_number);
