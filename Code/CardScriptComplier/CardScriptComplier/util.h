#pragma once
/*
* ���ã�������
* ���ߣ�����
* ���ڣ�2017.5.17
*/
#include "lib.h"

//�Ƿ���β
int is_end(Node* pnode);

//�Ƿ���ָ��
int is_cmd(Node* pnode);

//�Ƿ��Ǳ���
int is_var(char* p);

//��ʶ��
int is_id(char c);

//�ؼ���
int is_keyword(char* p);

//������
int is_operator(char* p);

//���
int is_delimiter(char c);

//�ո�
int is_blank(char c);

//ȡһ������
int get_word(char* p, char* pOut);

//ʮ��������
int is_hex(char c);

//ʮ�����ƴ�
int is_hex_str(char *p);

//ȡ�����
void get_operator(char* p, char* operator_word);

//ע��
int is_comment(char* p);

//�õ���һ��λ��
int get_next_line_pos(char* p);

//ת���ɴ�д
void str_to_upper(char* p);

//ת����Сд
void str_to_lower(char* p);

//��ĸ������
int is_letter_or_num(char c);

// ����תʮ�������ַ���
// void 

//---------------------�﷨����������----------------------------

//ȡ����
int get_next_const(Node* pnode, Cnt* pvar, Error* error);

//ȡ����
int get_next_arg(Node* pnode, Var* pvar, Error* error);

//ȡ����
int get_next_var(Node* pnode, Var* pvar, Error* error);

//��麯���Ƿ�ƥ��
int check_match_func(Node* pnode,Error* error);

//�õ�������
int get_func_name(Node* pnode, Var* var, Error* error);

//ȡ����ֵ������
int get_parser_result_name(Node** pnode,Var* var,Error* error);

//ȡ֮ǰ�ķ���
int get_back_id(Node* pnode, Var* var, Error* error);

//�Ƿ��Ǽ򵥱��ʽ
int is_simple_expression(Node* pHead,Node* pTail);

//ȡ����,�ƶ�ָ��
int get_next_var_movePoint(Node** pnode, Var* pvar, Error* error);

//�ַ�����ȡ
void substring(char* ch, int pos, int length, char *out_data);

//�ַ�����ȡ
void substring_2arg(char* ch, int pos, char *out_data);