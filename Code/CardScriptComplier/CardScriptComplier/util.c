#include "util.h"


//是否是指令
int is_cmd(Node* pnode) {
	if (pnode->pre->token.syn == TOKEN_KEYWORD_CRLF
		|| pnode->pre == gobal_lex_LinkList_head)
	{
		return 1;
	}
	return 0;
}

//是否行尾
int is_end(Node* pnode) {
	if (pnode->next->token.syn == TOKEN_KEYWORD_CRLF
		|| pnode->next->token.syn == TOKEN_EVEL)
	{
		return 1;
	}
	return 0;
}

//是否是变量
int is_var(char* p) {
	char* pre = p-1;
	
	if (*pre == '{')
	{
		return 1;
	}
	
	return 0;
}


//标识符
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

//关键字
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


//操作符
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

//界符
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

//空格
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

//注释
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

//取词
int get_word(char* p, char* pOut) {
	int ret;
	char* pOrg = p;

	while (*p != '\0') {
		ret = is_delimiter(*p);
		if (ret ==1) {
			strncpy(pOut, pOrg, p - pOrg);

			return 1;
		}

		//操作符
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

//字母或数字
int is_letter_or_num(char c) {
	if ((c >= 'a' && c <= 'z')
		|| (c >= 'A' && c <= 'Z')
		|| (c >= '0' && c <= '9')
		) {
		return 1;
	}

	return 0;
}

//十六进制数
int is_hex(char c) {
	
	if ((c >= 'a' && c <= 'h')
		|| (c >= 'A' && c <= 'H')
		|| (c >= '0' && c <= '9')
		) {
		return 1;
	}

	return 0;
}

//十六进制串
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

//取运算符
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

//得到下一行位置
int get_next_line_pos(char* p) {
	char* pOrg = p;
	
	while (*p != '\n') {
		p++;
	}

	return p - pOrg + 1;
}

//转换成大写
void str_to_upper(char* p) {
	while (*p != '\0') {
		*p = toupper(*p);

		p++;
	}

}

//转换成小写
void str_to_lower(char* p) {
	while (*p != '\0') {
		if (isalpha(*p))
		{
			*p = tolower(*p);
		}

		p++;
	}

}

//取常量
int get_next_const(Node* pnode, Cnt* pvar, Error* error)
{
	Node* p = pnode->next;
	Node* pre = p;

	//初始化
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

//取参数
int get_next_arg(Node* pnode, Var* pvar, Error* error)
{
		Node* p = pnode->next;
	Node* pre = p;

	//初始化
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

//取变量,移动指针
int get_next_var_movePoint(Node** pnode, Var* pvar, Error* error)
{

	Node* p = (*pnode)->next;
	Node* pre = p;

	//初始化
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

//取变量
int get_next_var(Node* pnode, Var* pvar, Error* error)
{
	
	Node* p = pnode->next;
	Node* pre = p;

	//初始化
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

//检查函数是否匹配
int check_match_func(Node* pnode, Error* error) 
{
	Node* p = pnode->next;
	Node* pre = p;

	//初始化
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

	//错误信息
	error->errcode = 1;
	error->line = pnode->line;
	error->column = pnode->column;
	strcpy(error->descript, "no match token )");

	return 0;
}


//得到函数名
int get_func_name(Node* pnode,Var* var, Error* error)
{
	Node* p = pnode->pre;
	Node* pre = p;

	//初始化
	error->errcode = 0;
	error->column = 0;
	error->line = 0;
	strcpy(error->descript, "");

	//清空
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

	//错误信息
	error->errcode = 1;
	error->line = pnode->line;
	error->column = pnode->column;
	strcpy(error->descript, "not found func name");

	return 0;
}

//取被赋值变量名
int get_parser_result_name(Node** pnode, Var* var, Error* error)
{
	Node* p = (*pnode)->next;
	Node* pre = p;

	//初始化
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

	//错误信息
	error->errcode = 1;
	error->line = (*pnode)->line;
	error->column = (*pnode)->column;
	strcpy(error->descript, "not found result name");

	*pnode = p;

	return 0;
}

//取之前的符号
int get_back_id(Node* pnode, Var* var, Error* error)
{
	Node* p = NULL;
	struct Node* pre;

	//初始化
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

	//错误信息
	error->errcode = 1;
	error->line = pnode->line;
	error->column = pnode->column;
	strcpy(error->descript, "not found id");

	return 0;
}


//是否是简单表达式
int is_simple_expression(Node* pHead, Node* pTail)
{
	Node* p = pHead;

	while (p != NULL && p != pTail)
	{
		//只要含有{var}变量的都是不是简单表达式
		if (p->token.syn == TOKEN_DELIMITER_VAR_LEFT
			)
		{
			return 0;
		}

		p = p->next;
	}

	return 1;
}

//字符串截取
void substring(char* ch, int pos, int length,char *out_data)
{
	char* pch = ch;
	//定义一个字符指针，指向传递进来的ch地址。  
	char* subch = (char*)calloc(sizeof(char), length + 1);
	//通过calloc来分配一个length长度的字符数组，返回的是字符指针。  
	int i;
	//只有在C99下for循环中才可以声明变量，这里写在外面，提高兼容性。  
	pch = pch + pos;
	//是pch指针指向pos位置。  
	for (i = 0; i < length; i++)
	{
		subch[i] = *(pch++);
		//循环遍历赋值数组。  
	}
	subch[length] = '\0';//加上字符串结束符。 

	strcpy(out_data, subch);
	free(subch);
}

//字符串截取
void substring_2arg(char* ch, int pos, char *out_data)
{
	char* pch = ch;
	//定义一个字符指针，指向传递进来的ch地址。  
	char* subch = (char*)calloc(sizeof(char), strlen(pch) + 1);
	//通过calloc来分配一个length长度的字符数组，返回的是字符指针。  
	int i =0;
	//只有在C99下for循环中才可以声明变量，这里写在外面，提高兼容性。  
	pch = pch + pos;
	//是pch指针指向pos位置。

	while (*pch != '\0')
	{	//循环遍历赋值数组。  
		subch[i] = *(pch++);
		i++;
	}
	subch[i] = '\0';//加上字符串结束符。 

	strcpy(out_data, subch);
	free(subch);
}