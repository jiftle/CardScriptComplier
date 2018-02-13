#include "grammer.h"
#include "grammar_list.h"
#include "util.h"
#include "quad_list.h"
#include "var.h"
#include "arg.h"
#include "lex_list.h"
#include "quad_list.h"
#include "func.h"

//������ֵ
void funcment(Node** pnode, char *func_name)
{
	//--------------------------------------------
	//���裺
	// 1�����Һ�����,���Ҳ������ͷ��ش���
	// 2����麯����������
	// 3�����ú���
	//--------------------------------------------
	int ret = 0;
	int is_expr = 0;
	Node* p = (*pnode)->next;
	Node* pOrg = p;
	Node* pExprHead = NULL;
	Node* pExprTail = NULL;
	char out_result[1024];
	Error error;
	char argv[5][512];
	int argv_index = 0;
	Var result;

	pExprHead = p;
	//�ж��Ƿ��Ǳ��ʽ
	while (p != NULL  && p->token.syn != TOKEN_KEYWORD_CRLF
		) {
		if (p->token.syn == TOKEN_DELIMITER_COMMA || p->token.syn == TOKEN_DELIMITER_FUNC_RIGHT)
		{
			strcpy(argv[argv_index], p->pre->token.token);
			argv_index++;
		}

		if (p->token.syn == TOKEN_DELIMITER_FUNC_RIGHT)
		{
			is_expr = 1;
			break;
		}
		p = p->next;
	}


	//pExprHead �� pExprTail ȷ��һ�����ʽ(1A2B3C4D)
	//��֧����
	if (is_expr == 1) {

		//���Һ����Ƿ����
		ret = look_func(func_name);
		if (ret == 0)
		{
			printf("error, not found func %s\n",func_name);
			return;
		}
		
		//���ú����õ����
		call_func(func_name, argv, argv_index,out_result, &error);
		//�õ�������
		get_parser_result_name(&p, &result, &error);

		//���
		gobal_var_add(result.name, out_result);
	}
	else {
		//....
	}
	*pnode = p;
}

//������Ԫʽ���
void emit(char *op, char* arg1, char* arg2, char* result)
{
	char buf[1024] = {0};
	sprintf(buf, "(%s, %s, %s, %s)", op, arg1, arg2, result);
	DebugLog(gobal_logger, __FILE__, __LINE__, buf);

	int token_syn = 0;
	int n_arg1 = 0;
	int n_arg2 = 0;
	int n_result = -1;
	char buf_result[10] = { 0 };

	token_syn = get_token_type(op);
	n_arg1 = atoi(arg1);
	n_arg2 = atoi(arg2);

	switch (token_syn)
	{
	case TOKEN_ADD:
		n_result = n_arg1 + n_arg2;
		break;
	case TOKEN_SUB:
		n_result = n_arg1 - n_arg2;
		break;
	case TOKEN_MUL:
		n_result = n_arg1 * n_arg2;
		break;
	case TOKEN_DIV:
		n_result = n_arg1 / n_arg2;
		break;
	case TOKEN_MOD:
		n_result = n_arg1 % n_arg2;
		break;
	default:
		break;
	}

	quad_list_add(op, arg1, arg2, result);
	sprintf(buf_result, "%02X", n_result);
	
	gobal_var_add(result, buf_result);
}

void print_grammar(Grammar* pGrammar,int is_end)
{
	char buf[1024] = { 0 };
	Grammar* p = NULL;
	
	//------------------------�滻
	if (gobal_grammar_LinkList_tail != NULL && gobal_grammar_LinkList_tail->endflag == 0) {
		p = gobal_grammar_LinkList_tail;
		p->endflag = is_end;

		strcat(p->node.token.token, pGrammar->node.token.token);

		sprintf(buf, "debug grammar append (%s)\n", p->node.token.token);
		printf(buf);
		return;
	}

	//--------------------�½ڵ�
	gobal_grammar_LinkList_add(pGrammar,is_end);
}



//����
void factor()
{

}

//���
void statement(Node** pnode)
{  
	int ret = 0;
	int is_expr = 0;
	Node* p = (*pnode)->next;
	Node* pOrg = p;
	Node* pExprHead = NULL;
	Node* pExprTail = NULL;
	
	pExprHead = p;
	//�ж��Ƿ��Ǳ��ʽ
	while (p != NULL  && p->token.syn != TOKEN_KEYWORD_CRLF
		) {

		if (p->token.syn == TOKEN_ADD 
			|| p->token.syn == TOKEN_SUB
			|| p->token.syn == TOKEN_MUL
			|| p->token.syn == TOKEN_DIV
			|| p->token.syn == TOKEN_MOD
			) 
		{
			//�ж��Ƿ������ñ��� RES RES_SW1 RES_SW2
			if (p->token.syn == TOKEN_MOD)
			{
				if ((p->next->token.syn == TOKEN_KEYWORD_ID && strcasecmp(p->next->token.token,"RES"))
					|| (p->next->token.syn == TOKEN_KEYWORD_ID && strcasecmp(p->next->token.token,"RES_SW1"))
					|| (p->next->token.syn == TOKEN_KEYWORD_ID && strcasecmp(p->next->token.token,"RES_SW2"))
					)
				{
					return;
// 					p = p->next;
// 					continue;
				}
			}
			
			is_expr = 1;
			break;
		}else if (p->token.syn == TOKEN_EVEL)
		{
			is_expr = 2;
			break;
		}
		p = p->next;
	}
	
	
	//pExprHead �� pExprTail ȷ��һ�����ʽ(1A2B3C4D)
	//��֧����
	if (is_expr == 1) {
		expression(&pOrg,pExprHead, pExprTail);
	}
	else if(is_expr ==2){
		pExprTail = p->pre->pre;
		ret = is_simple_expression(pExprHead, pExprTail);
		if (ret == 1) {
			evel(&pOrg);
		}
	}
	else {
		//....
	}
	*pnode = p;
}

//��ֵ 
//(FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)> {dlk}
void evel(Node** pnode) {
	Node* p = *pnode;
	Var result;
	Var var;
	Error error;

	while (p != NULL && p->token.syn != TOKEN_KEYWORD_CRLF) {

		if (p->token.syn == TOKEN_EVEL)
		{
			get_back_id(p->pre, &var, &error);

			get_parser_result_name(&(p->next), &result, &error);
			emit(">", var.name, "", result.name);

			//���
			gobal_var_add(result.name,var.name);
			break;
		}

		p = p->next;
	}

	*pnode = p;
}

//���ʽ
void expression(Node** pnode,Node* pHead,Node* pTail)
{
	Node* p = *pnode;
	Token token;
	Token token2;
	Var result;
	Error error;
	int ret = 0,ret1 = 0;


	while (p != NULL && p->token.syn != TOKEN_KEYWORD_CRLF
		&& p != pTail
		) {

		switch (p->token.syn)
		{
		//--------------------------���������
		case TOKEN_ADD:
			token.syn = p->pre->token.syn;
			strcpy(token.token, p->pre->token.token);
			token.sum = p->pre->token.sum;

			token2.syn = p->next->token.syn;
			strcpy(token2.token, p->next->token.token);
			token2.sum = p->next->token.sum;

			get_parser_result_name(&(p->next), &result, &error);
			emit("+", token.token, token2.token,result.name);
			break;
		case TOKEN_SUB:
			token.syn = p->pre->token.syn;
			strcpy(token.token, p->pre->token.token);
			token.sum = p->pre->token.sum;

			token2.syn = p->next->token.syn;
			strcpy(token2.token, p->next->token.token);
			token2.sum = p->next->token.sum;

			get_parser_result_name(&(p->next), &result, &error);
			emit("-", token.token, token2.token, result.name);
			break;
		case TOKEN_MUL:
			token.syn = p->pre->token.syn;
			strcpy(token.token, p->pre->token.token);
			token.sum = p->pre->token.sum;

			token2.syn = p->next->token.syn;
			strcpy(token2.token, p->next->token.token);
			token2.sum = p->next->token.sum;

			get_parser_result_name(&(p->next), &result, &error);
			emit("*", token.token, token2.token, result.name);
			break;
		case TOKEN_DIV:
			token.syn = p->pre->token.syn;
			strcpy(token.token, p->pre->token.token);
			token.sum = p->pre->token.sum;

			token2.syn = p->next->token.syn;
			strcpy(token2.token, p->next->token.token);
			token2.sum = p->next->token.sum;

			get_parser_result_name(&(p->next), &result, &error);
			emit("/", token.token, token2.token, result.name);
			break;
		case TOKEN_MOD:
			token.syn = p->pre->token.syn;
			strcpy(token.token, p->pre->token.token);
			token.sum = p->pre->token.sum;

			token2.syn = p->next->token.syn;
			strcpy(token2.token, p->next->token.token);
			token2.sum = p->next->token.sum;

			get_parser_result_name(&(p->next), &result, &error);
			emit("%", token.token, token2.token, result.name);
			break;

		default:
			break;
		}

		p = p->next;
	}

	*pnode = p;
}

//��ӡ����
void print_error(Error error)
{
	printf("Error %d,syntax error,ln:%d,%d ,%s\n", error.errcode, error.line, error.column, error.descript);

}

//������
void lr_parser_line(Node* linkList_head,Node* linkList_tail)
{
	//return;
	//printf("------------------------�﷨����------------------------\n");
	Node* pNode = linkList_head;
	Var var, var1;
	Cnt cnt;
	Error error;
	int ret;
	Grammar grammar;

	while (pNode != NULL && pNode != linkList_tail)
	{
		//ʶ�𵥴ʷ���
		if (pNode->token.syn == TOKEN_KEYWORD_ID)
		{
			ret = is_cmd(pNode);
			if (ret) {
				grammar.node.line = pNode->line;
				grammar.node.column = pNode->column;
				grammar.node.token.syn = TOKEN_CMD;
				strcpy(grammar.node.token.name, pNode->token.name);
				strcpy(grammar.node.token.token, pNode->token.token);
				grammar.node.token.sum = pNode->token.sum;

				print_grammar(&grammar, is_end(pNode));
				//ret = 0;
			}
			else {
				grammar.node.line = pNode->line;
				grammar.node.column = pNode->column;
				grammar.node.token.syn = TOKEN_KEYWORD_ID;
				strcpy(grammar.node.token.name, pNode->token.name);
				strcpy(grammar.node.token.token, pNode->token.token);
				grammar.node.token.sum = pNode->token.sum;

				print_grammar(&grammar, is_end(pNode));
			}

		}

		//ʶ����
		if (pNode->token.syn == TOKEN_DELIMITER_CNT) {//����
			ret = get_next_const(pNode, &cnt, &error);
			if (ret == 0) {
				print_error(error);
				goto next;
			}

			pNode = pNode->next;
			pNode = pNode->next;
			pNode = pNode->next;

			continue;
		}

		//ʶ�����
		if (pNode->token.syn == TOKEN_DELIMITER_ARG) {
			ret = get_next_arg(pNode, &var, &error);
			if (ret == 0) {
				print_error(error);
				goto next;
			}

			//�����ֵ
			ret = lookup_arg(var.name, var.value);
			if (ret) {
				grammar.node.line = pNode->line;
				grammar.node.column = pNode->column;
				grammar.node.token.syn = TOKEN_VAR;
				strcpy(grammar.node.token.name, var.name);
				strcpy(grammar.node.token.token, var.value);
				grammar.node.token.sum = pNode->token.sum;

				print_grammar(&grammar, is_end(pNode->next->next));
			}

			pNode = pNode->next;
			pNode = pNode->next;
			pNode = pNode->next;

			continue;
		}


		//ʶ�� ����
		if (pNode->token.syn == TOKEN_DELIMITER_VAR_LEFT) {
			ret = get_next_var(pNode, &var, &error);
			if (ret == 0) {
				print_error(error);
				goto next;
			}

			//������Ƿ��Ѿ�����
			ret = lookup_var(var.name, &var1);
			if (ret)
			{
				grammar.node.line = pNode->line;
				grammar.node.column = pNode->column;
				grammar.node.token.syn = TOKEN_VAR;
				strcpy(grammar.node.token.name, var1.name);
				strcpy(grammar.node.token.token, var1.value);
				grammar.node.token.sum = pNode->token.sum;

				print_grammar(&grammar, is_end(pNode->next->next));
				//���Խ����滻����
				ret = 0;
			}

			//---------------------ָ�����
			pNode = pNode->next;
			pNode = pNode->next;
			pNode = pNode->next;

			continue;
		}

		//��ƥ��Ľ��
		if (pNode->token.syn == TOKEN_DELIMITER_VAR_RIGHT) {
			error.errcode = 1;
			error.line = pNode->line;
			error.column = pNode->column;
			strcpy(error.descript, "no match token {");

			print_error(error);
		}

		//ʶ�� ����
		if (pNode->token.syn == TOKEN_DELIMITER_FUNC_LEFT) {
			ret = check_match_func(pNode, &error);
			if (ret == 0) {
				print_error(error);
				goto next;
			}

			//��ȡ���������ж��Ƿ��Ǻ���
			ret = get_func_name(pNode, &var, &error);
			if (ret == 0) {//���Ǻ���
				//���
				statement(&pNode);

			}
			else {
				//��������
				funcment(&pNode, var.name);
			}

		}



	next:
		pNode = pNode->next;
	}

	gobal_grammar_LinkList_tail->endflag = 1;


	//printf("------------------------�﷨���� ok------------------------\n");
}




//�﷨������
void lr_parser()
{
	//printf("------------------------�﷨����------------------------\n");
	Node* pList = gobal_lex_LinkList_head;//����ͷָ��
	Node* pHead = NULL;
	Node* pTail = NULL;
	int ret = 0;

	pList = pList->next;

	//ʶ���ÿһ��
	while (pList != NULL) {
		//ʶ�������
		get_next_line_lex_linkList(&pList,&pHead,&pTail);
		lr_parser_line(pHead,pTail); //���д���

		pList = pList->next;
	}

	

	ret = 0;
	//printf("------------------------�﷨���� ok------------------------\n");
}

