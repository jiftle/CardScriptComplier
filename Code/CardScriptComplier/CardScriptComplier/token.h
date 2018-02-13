#pragma once
/*
* ���ã����ʷ�����
* ���ߣ�����
* ���ڣ�2017.5.17
*/
#include "lib.h"

//==============================�ؼ���===================================
static char* cnt_keyword[] = {
	"if","else","return","null"
};
static int cnt_keyword_size = 4;

//==============================�����===================================
static char* cnt_operator[] = {
	"==", "!=", "<", "<=" //��ϵ�����
	, "+", "-", "*", "/", "%", "&", "|","^" //���������
	, "&&", "||" //�߼������
	,">" //��ֵ��
};
static int cnt_operator_size = 15;

//==============================���=====================================
static char cnt_delimiter[] = {
	'#', //����
	'$' //����
	,'{'  //����
	,'}'
	,','
	,'('
	,')'
};
static int cnt_delimiter_size = 7;

//===============================�ո�==============================
static char* cnt_blank[] = {
	" " //�ո�
	,"\t" //�Ʊ��
};
static int cnt_blank_size = 2;

//===============================ע��==============================
static char* cnt_comment[] = {
	";"//ע��
};
static int cnt_comment_size = 1;

//===============================�ֱ���1-10==============================
#define TOKEN_DELIMITER_CNT 1 //����#
#define TOKEN_DELIMITER_ARG   2 //����$
#define TOKEN_DELIMITER_RES   3 //ϵͳ���ñ���
#define TOKEN_DELIMITER_VAR_LEFT   4 //����Left {
#define TOKEN_DELIMITER_VAR_RIGHT   5 //����Right
#define TOKEN_DELIMITER_FUNC_LEFT   6 //����Left (
#define TOKEN_DELIMITER_FUNC_RIGHT   7 //����Right )
#define TOKEN_DELIMITER_COMMA          8 //����
#define TOKEN_KEYWORD_ID          9 //��ʶ��
#define TOKEN_KEYWORD_CRLF          10 //����
#define TOKEN_VAR			11 //����
#define TOKEN_CMD			12 //����
#define TOKEN_EVEL  100 //��ֵ

//==============================�����20-60===================================
#define TOKEN_RELATE_EQUAL              21 //���
#define TOKEN_RELATE_NOT_EQUAL          22 //�����
#define TOKEN_RELATE_LESS               23 //С��
#define TOKEN_RELATE_LESS_EQUAL         24 //С�ڵ���

//���������
#define TOKEN_ADD   31 //��
#define TOKEN_SUB   32 //��
#define TOKEN_MUL   33 //��
#define TOKEN_DIV   34 //��
#define TOKEN_MOD   35 //ȡģ

//λ����
#define TOKEN_BIN_AND   41 //and
#define TOKEN_BIN_OR    42 //or
#define TOKEN_BIN_XOR   43 //xor

//�߼�����
#define TOKEN_AND       51
#define TOKEN_OR        52

//==============================�ؼ���70-80===================================
//�ؼ��� "if","else","return","null"
#define TOKEN_KEYWORD_IF        71
#define TOKEN_KEYWORD_ELSE      72
#define TOKEN_KEYWORD_RETURN    73
#define TOKEN_KEYWORD_NULL      74


#define TOKEN_STRING    222
#define TOKEN_FUNC    221

//����ֱ���
int get_token_type(char* p);
//������
void get_token_str(int syn,char* name);