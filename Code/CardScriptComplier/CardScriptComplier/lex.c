// lex.cpp : 定义控制台应用程序的入口点。
#include "lex.h"
#include "util.h"

//扫描单行
void scaner_sigle_line(const char* pbuf,int lineno)
{
	char* p = (char*)pbuf;
	char word[512] = { 0 };
	int word_len = 0;
	int offset = 0;
	int ret = 0;
	int token_type = 0;
	int column = 0;
	int flag_cmd = 0; //指令

	struct Line line;
	line.line_number = lineno;
	strcpy(line.line_context, pbuf);

	if (*p == ';') //注释
	{
		return;
	}

	if (*p == '\n') {
		strcpy(word,"crlf");
		print_token(TOKEN_KEYWORD_CRLF, word, 0, line, 0);
		return;
	}

	while (*p != '\0')
	{
		
		//判断是否是字母或数字
		if (is_letter_or_num(*p)) {
			memset(word, 0, 512);
			//获取单词
			ret = get_word(p, word);
			if (ret) {
				//判断是否是关键字
				if (is_keyword(word)) {
					token_type = get_token_type(word);
					print_token(token_type, word, 0,line,column);
				}
				else {
					print_token(TOKEN_KEYWORD_ID, word, 0, line, column);
				}
				column = column + strlen(word);
				p = p + strlen(word);
				

				continue;
			}
			else {
				printf("find word fail,%s\n", p);
				p++;

				continue;
			}
		}


		//判断是否界符 1个字符
		if (is_delimiter(*p)) {
			memset(word, 0, 512);
			strncpy(word, p, 1);
			token_type = get_token_type(word);
			
			print_token(token_type, word, 0, line, column);
			column++;
			p++;

			continue;
		}

		//运算符
		if (is_operator(p)) {
			memset(word, 0, 512);
			get_operator(p, word);
			
			token_type = get_token_type(word);
			print_token(token_type, word, 0, line, column);
			column = column + strlen(word);
			p = p+ strlen(word);

			continue;
		}

		//注释
		if (is_comment(p)) {
			offset = get_next_line_pos(p);
			p = p + offset;

			continue;
		}

		p++;
	}

	strcpy(word, "crlf");
	print_token(TOKEN_KEYWORD_CRLF, word, 0, line, column);

	return;
}



//打印记号
void print_token(int token_type,char* token_str,int token_sum,struct Line line,int cloumn_number)
{
	struct Node* p = gobal_lex_LinkList_head;
	struct Node* pOrg = p;
	struct Node* pnode = NULL;
	Token token;
	
	token.syn = token_type;
	token.sum = token_sum;
	strcpy(token.token, token_str);

	//存储词法分析结果到链表
	{
		pOrg = gobal_lex_LinkList_tail;

		//多行\n处理为1行\n
		if (pOrg != NULL 
			&& pOrg->token.syn == TOKEN_KEYWORD_CRLF
			&& token.syn == TOKEN_KEYWORD_CRLF)
		{
			return;
		}

		pnode = (Node*)malloc(sizeof(struct Node));
		if (pnode == NULL) {
			printf("malloc fail.");
		}

		pnode->token.syn = token.syn;
		get_token_str(token.syn,pnode->token.name);
		strcpy(pnode->token.token, token.token);
		pnode->token.sum = token.sum;
		pnode->line = line.line_number;
		pnode->column = cloumn_number;

		pnode->pre = pOrg;
		pnode->next = NULL;

		pOrg->next = pnode;
		gobal_lex_LinkList_tail = pnode;
	}
	
}
