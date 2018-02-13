#pragma once
/*
* ���ã��ʷ�������
* ���ߣ�����
* ���ڣ�2017.5.17
*/


/* ȫ�ַ��ű� */

//-------------------------�궨��-----------------------------
#define LEX_PRINT_FILE			1  //�ʷ��������д�뵽�ļ�
#define TEST_USE_FILE		    1  //ʹ���ļ�����
#define TEST_SHOW_DEBUG			0  //��ʾ������Ϣ

/* ���� */
typedef struct Var {
	char name[128]; //������
	char value[1024]; //����ֵ
}Var;


/* ������ */
typedef struct Line {
	int line_number; //�к�
	char line_context[1024]; //����
}Line;

//ȫ�ֱ���
#define GOBAL_VAR_SIZE			 10
struct Var gobal_var[GOBAL_VAR_SIZE];
int gobal_var_index;



/* ���ʷ��� */
typedef struct Token {
	int syn;//�ֱ���
	char name[50]; //token���ͣ��������� eg. id,num
	char token[512]; //���ʷ���
	int sum;//���͵���
}Token;


//------------------------------�ʷ������Ľ��-----------------------
/* �ʷ�������� */
typedef struct Node {
	int line; //��c
	int column; //��
	struct Token token;
	struct Node* pre;
	struct Node* next;
}Node;

//�ʷ��������
Node* gobal_lex_LinkList_head;
Node* gobal_lex_LinkList_tail;//β��ָ��
Node* gobal_lex_LinkList_cur;


//-------------------------------������Ϣ-----------------------------
/* ������Ϣ */
typedef struct Error {
	int errcode;
	char descript[512];
	int line; //��
	int column; //��
}Error;


/* �﷨������� */
typedef struct Grammar {
	struct Node node;
	int endflag; //�������
	struct Grammar* pre;
	struct Grammar* next;
}Grammar;

//�﷨�������
Grammar* gobal_grammar_LinkList_head;
Grammar* gobal_grammar_LinkList_tail;
Grammar* gobal_grammar_LinkList_cur;
int gobal_grammar_LinkList_size;

/* �﷨������Ԫʽ */
typedef struct Quad {
	char op[5];
	char arg1[512];
	char arg2[512];
	char result[1024];

	struct Quad* pre;
	struct Quad* next;
}Quad;

/* ȫ����Ԫʽ�� */
Quad* gobal_quad_list_head;
Quad* gobal_quad_list_tail;

//����
typedef struct Arg {
	char name[30];
	char value[50];
	struct Arg* next;
}Arg;

//�����б�
Arg gobal_arg_LinkList[10];
int gobal_arg_LinkList_index;
#define GOBAL_ARG_LINKLIST_SIZE    10

//����
typedef struct Cnt {
	char name[30];
	int value;
}Cnt;

//�����б�
Cnt gobal_cnt_list[10];
int gobal_cnt_index;
#define GOBAL_CNT_LIST_SIZE    10
