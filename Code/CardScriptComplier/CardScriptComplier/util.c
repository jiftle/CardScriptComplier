#include "util.h"


//�Ƿ���ָ��
int is_cmd(Node* pnode) {
	if (pnode->pre->token.syn == TOKEN_KEYWORD_CRLF
		|| pnode->pre == gobal_lex_LinkList_head)
	{
		return 1;
	}
	return 0;
}

//�Ƿ���β
int is_end(Node* pnode) {
	if (pnode->next->token.syn == TOKEN_KEYWORD_CRLF
		|| pnode->next->token.syn == TOKEN_EVEL)
	{
		return 1;
	}
	return 0;
}

//�Ƿ��Ǳ���
int is_var(char* p) {
	char* pre = p-1;
	
	if (*pre == '{')
	{
		return 1;
	}
	
	return 0;
}


//��ʶ��
int is_id(char c) {
	if ((c >= 'a' && c <= 'z')
		|| (c >= 'A' && c <= 'Z')
		|| (c == '_')
		|| (c >= '0' && c <= '9')
		) {
		return 1;
	}

	return 0;
}

//�ؼ���
int is_keyword(char* p) {
	char* pOrg = p;
	int i = 0;

	for (i = 0; i < cnt_keyword_size; i++)
	{
		if (strcmp(pOrg, cnt_keyword[i]) == 0) {
			return 1;
		}
	}
	
	return 0;
}


//������
int is_operator(char* p) {
	int i;
	int operator_len;
	char word[5] = {0};

	for (i = 0; i < cnt_operator_size; i++)
	{
		memset(word, 0, 5);
		operator_len = strlen(cnt_operator[i]);
		strncpy(word, p, operator_len);
		if (strcmp(word, cnt_operator[i]) == 0) {
			return 1;
		}
	}

	return 0;
}

//���
int is_delimiter(char c) {
	int i;

	for (i = 0; i < cnt_delimiter_size; i++)
	{
		if (c == cnt_delimiter[i]) {
			return 1;
		}
	}

	return 0;
}

//�ո�
int is_blank(char c) {
	int i;

	for (i = 0; i < cnt_blank_size; i++)
	{
		if ((int)c == (int)cnt_blank[i]) {
			return 1;
		}
	}

	return 0;
}

//ע��
int is_comment(char* p) {
	int i;
	char word[3];
	int len;
	
	for (i = 0; i < cnt_comment_size; i++)
	{
		len = strlen(cnt_comment[i]);
		memset(word, 0, 3);
		strncpy(word, p, len);
		if (strcmp(word,cnt_comment[i]) == 0) {
			return 1;
		}
	}

	return 0;
}

//ȡ��
int get_word(char* p, char* pOut) {
	int ret;
	char* pOrg = p;

	while (*p != '\0') {
		ret = is_delimiter(*p);
		if (ret ==1) {
			strncpy(pOut, pOrg, p - pOrg);

			return 1;
		}

		//������
		ret = is_operator(p);
		if (ret == 1) {
			strncpy(pOut, pOrg, p - pOrg);

			return 1;
		}

		p++;
	}

	strncpy(pOut, pOrg, p - pOrg);

	return 1;
}

//��ĸ������
int is_letter_or_num(char c) {
	if ((c >= 'a' && c <= 'z')
		|| (c >= 'A' && c <= 'Z')
		|| (c >= '0' && c <= '9')
		) {
		return 1;
	}

	return 0;
}

//ʮ��������
int is_hex(char c) {
	
	if ((c >= 'a' && c <= 'h')
		|| (c >= 'A' && c <= 'H')
		|| (c >= '0' && c <= '9')
		) {
		return 1;
	}

	return 0;
}

//ʮ�����ƴ�
int is_hex_str(char *p) {

	while (*p != '\0') {
		char c = *p;
		int flag = is_hex(c);
		if (flag == 0) {
			return 1;
		}
		p++;
	}

	return 0;
}

//ȡ�����
void get_operator(char* p, char* operator_word) {
	int i;
	int operator_len;
	char word[5] = { 0 };

	for (i = 0; i < cnt_operator_size; i++)
	{
		operator_len = strlen(cnt_operator[i]);
		memset(word, 0, 5);
		strncpy(word, p, operator_len);
		if (strcmp(word, cnt_operator[i]) == 0) {

			strcpy(operator_word, word);
			return;
		}
	}
}

//�õ���һ��λ��
int get_next_line_pos(char* p) {
	char* pOrg = p;
	
	while (*p != '\n') {
		p++;
	}

	return p - pOrg + 1;
}

//ת���ɴ�д
void str_to_upper(char* p) {
	while (*p != '\0') {
		*p = toupper(*p);

		p++;
	}

}

//ת����Сд
void str_to_lower(char* p) {
	while (*p != '\0') {
		if (isalpha(*p))
		{
			*p = tolower(*p);
		}

		p++;
	}

}

//ȡ����
int get_next_const(Node* pnode, Cnt* pvar, Error* error)
{
	Node* p = pnode->next;
	Node* pre = p;

	//��ʼ��
	error->errcode = 0;
	error->column = 0;
	error->line = 0;
	strcpy(error->descript, "");

	while (p != NULL && p->token.syn != TOKEN_KEYWORD_CRLF) {
		if (p->token.syn == TOKEN_DELIMITER_CNT) {

			strcpy(pvar->name, pre->token.token);
			pvar->value = -1;

			return 1;
		}

		pre = p;
		p = p->next;
	}

	error->errcode = 1;
	error->line = pnode->line;
	error->column = pnode->column;
	strcpy(error->descript, "no match token #");

	return 0;
}

//ȡ����
int get_next_arg(Node* pnode, Var* pvar, Error* error)
{
		Node* p = pnode->next;
	Node* pre = p;

	//��ʼ��
	error->errcode = 0;
	error->column = 0;
	error->line = 0;
	strcpy(error->descript, "");



	while (p != NULL && p->token.syn != TOKEN_KEYWORD_CRLF) {
		if (p->token.syn == TOKEN_DELIMITER_ARG) {

			strcpy(pvar->name, pre->token.token);
			strcpy(pvar->value, "");

			return 1;
		}

		pre = p;
		p = p->next;
	}

	error->errcode = 1;
	error->line = pnode->line;
	error->column = pnode->column;
	strcpy(error->descript, "no match token $");

	return 0;
}

//ȡ����,�ƶ�ָ��
int get_next_var_movePoint(Node** pnode, Var* pvar, Error* error)
{

	Node* p = (*pnode)->next;
	Node* pre = p;

	//��ʼ��
	error->errcode = 0;
	error->column = 0;
	error->line = 0;
	strcpy(error->descript, "");

	while (p != NULL && p->token.syn != TOKEN_KEYWORD_CRLF) {
		if (p->token.syn == TOKEN_DELIMITER_VAR_RIGHT) {

			strcpy(pvar->name, pre->token.token);
			strcpy(pvar->value, "");

			*pnode = p->next;
			return 1;
		}

		pre = p;
		p = p->next;
	}

	error->errcode = 1;
	error->line = (*pnode)->line;
	error->column = (*pnode)->column;
	strcpy(error->descript, "no match token }");

	return 0;
}

//ȡ����
int get_next_var(Node* pnode, Var* pvar, Error* error)
{
	
	Node* p = pnode->next;
	Node* pre = p;

	//��ʼ��
	error->errcode = 0;
	error->column = 0;
	error->line = 0;
	strcpy(error->descript, "");

	while (p != NULL && p->token.syn != TOKEN_KEYWORD_CRLF) {
		if (p->token.syn == TOKEN_DELIMITER_VAR_RIGHT) {

			strcpy(pvar->name, pre->token.token);
			strcpy(pvar->value, "");

			return 1;
		}

		pre = p;
		p = p->next;
	}

	error->errcode = 1;
	error->line = pnode->line;
	error->column = pnode->column;
	strcpy(error->descript, "no match token }");

	return 0;
}

//��麯���Ƿ�ƥ��
int check_match_func(Node* pnode, Error* error) 
{
	Node* p = pnode->next;
	Node* pre = p;

	//��ʼ��
	error->errcode = 0;
	error->column = 0;
	error->line = 0;
	strcpy(error->descript, "");

	while (p != NULL && p->token.syn != TOKEN_KEYWORD_CRLF) {
		if (p->token.syn == TOKEN_DELIMITER_FUNC_RIGHT) {
			return 1;
		}

		pre = p;
		p = p->next;
	}

	//������Ϣ
	error->errcode = 1;
	error->line = pnode->line;
	error->column = pnode->column;
	strcpy(error->descript, "no match token )");

	return 0;
}


//�õ�������
int get_func_name(Node* pnode,Var* var, Error* error)
{
	Node* p = pnode->pre;
	Node* pre = p;

	//��ʼ��
	error->errcode = 0;
	error->column = 0;
	error->line = 0;
	strcpy(error->descript, "");

	//���
	strcpy(var->name, "");
	strcpy(var->value, "");

	while (p != NULL && p->token.syn != TOKEN_KEYWORD_CRLF) {
		if (p->token.syn == TOKEN_KEYWORD_ID) {
			strcpy(var->name, p->token.token);
			strcpy(var->value, "");

			return 1;
		}

		pre = p;
		p = p->pre;
	}

	//������Ϣ
	error->errcode = 1;
	error->line = pnode->line;
	error->column = pnode->column;
	strcpy(error->descript, "not found func name");

	return 0;
}

//ȡ����ֵ������
int get_parser_result_name(Node** pnode, Var* var, Error* error)
{
	Node* p = (*pnode)->next;
	Node* pre = p;

	//��ʼ��
	error->errcode = 0;
	error->column = 0;
	error->line = 0;
	strcpy(error->descript, "");

	while (p != NULL && p->token.syn != TOKEN_KEYWORD_CRLF) {
		if (p->token.syn == TOKEN_KEYWORD_ID) {
			strcpy(var->name, p->token.token);
			strcpy(var->value, "");

			*pnode = p->next->next;
			return 1;
		}

		pre = p;
		p = p->next;
	}

	//������Ϣ
	error->errcode = 1;
	error->line = (*pnode)->line;
	error->column = (*pnode)->column;
	strcpy(error->descript, "not found result name");

	*pnode = p;

	return 0;
}

//ȡ֮ǰ�ķ���
int get_back_id(Node* pnode, Var* var, Error* error)
{
	Node* p = NULL;
	struct Node* pre;

	//��ʼ��
	error->errcode = 0;
	error->column = 0;
	error->line = 0;
	strcpy(error->descript, "");

	p = pnode->pre;
	pre = p;

	while (p != NULL && p->token.syn != TOKEN_KEYWORD_CRLF) {
		if (p->token.syn == TOKEN_KEYWORD_ID) {
			strcpy(var->name, p->token.token);
			strcpy(var->value, "");

			return 1;
		}

		pre = p;
		p = p->pre;
	}

	//������Ϣ
	error->errcode = 1;
	error->line = pnode->line;
	error->column = pnode->column;
	strcpy(error->descript, "not found id");

	return 0;
}


//�Ƿ��Ǽ򵥱��ʽ
int is_simple_expression(Node* pHead, Node* pTail)
{
	Node* p = pHead;

	while (p != NULL && p != pTail)
	{
		//ֻҪ����{var}�����Ķ��ǲ��Ǽ򵥱��ʽ
		if (p->token.syn == TOKEN_DELIMITER_VAR_LEFT
			)
		{
			return 0;
		}

		p = p->next;
	}

	return 1;
}

//�ַ�����ȡ
void substring(char* ch, int pos, int length,char *out_data)
{
	char* pch = ch;
	//����һ���ַ�ָ�룬ָ�򴫵ݽ�����ch��ַ��  
	char* subch = (char*)calloc(sizeof(char), length + 1);
	//ͨ��calloc������һ��length���ȵ��ַ����飬���ص����ַ�ָ�롣  
	int i;
	//ֻ����C99��forѭ���вſ�����������������д�����棬��߼����ԡ�  
	pch = pch + pos;
	//��pchָ��ָ��posλ�á�  
	for (i = 0; i < length; i++)
	{
		subch[i] = *(pch++);
		//ѭ��������ֵ���顣  
	}
	subch[length] = '\0';//�����ַ����������� 

	strcpy(out_data, subch);
	free(subch);
}

//�ַ�����ȡ
void substring_2arg(char* ch, int pos, char *out_data)
{
	char* pch = ch;
	//����һ���ַ�ָ�룬ָ�򴫵ݽ�����ch��ַ��  
	char* subch = (char*)calloc(sizeof(char), strlen(pch) + 1);
	//ͨ��calloc������һ��length���ȵ��ַ����飬���ص����ַ�ָ�롣  
	int i =0;
	//ֻ����C99��forѭ���вſ�����������������д�����棬��߼����ԡ�  
	pch = pch + pos;
	//��pchָ��ָ��posλ�á�

	while (*pch != '\0')
	{	//ѭ��������ֵ���顣  
		subch[i] = *(pch++);
		i++;
	}
	subch[i] = '\0';//�����ַ����������� 

	strcpy(out_data, subch);
	free(subch);
}