/* �﷨������ */
#include "lib.h"

//��ӡ����
void print_error(Error error);

void lr_parser();

//������
void statement(Node** pnode);

//����
void factor();

//���ʽ
void expression(Node** pnode, Node* pHead, Node* pTail);

//��ӡ����
void print_error(Error error);

//��ֵ
void evel(Node** pnode);

//�﷨�ڵ�
void print_grammar(Grammar* pGrammar, int is_end);

//������Ԫʽ���
void emit(char *op, char* arg1, char* arg2, char* result);

//������ֵ
void funcment(Node** pnode, char *func_name);
