// lex.cpp : �������̨Ӧ�ó������ڵ㡣
#include "lex.h"
#include "util.h"

//ɨ�赥��
void scaner_sigle_line(const char* pbuf,int lineno)
{
	char* p = (char*)pbuf;
	char word[512] = { 0 };
	int word_len = 0;
	int offset = 0;
	int ret = 0;
	int token_type = 0;
	int column = 0;
	int flag_cmd = 0; //ָ��

	struct Line line;
	line.line_number = lineno;
	strcpy(line.line_context, pbuf);

	if (*p == ';') //ע��
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
		
		//�ж��Ƿ�����ĸ������
		if (is_letter_or_num(*p)) {
			memset(word, 0, 512);
			//��ȡ����
			ret = get_word(p, word);
			if (ret) {
				//�ж��Ƿ��ǹؼ���
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


		//�ж��Ƿ��� 1���ַ�
		if (is_delimiter(*p)) {
			memset(word, 0, 512);
			strncpy(word, p, 1);
			token_type = get_token_type(word);
			
			print_token(token_type, word, 0, line, column);
			column++;
			p++;

			continue;
		}

		//�����
		if (is_operator(p)) {
			memset(word, 0, 512);
			get_operator(p, word);
			
			token_type = get_token_type(word);
			print_token(token_type, word, 0, line, column);
			column = column + strlen(word);
			p = p+ strlen(word);

			continue;
		}

		//ע��
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



//��ӡ�Ǻ�
void print_token(int token_type,char* token_str,int token_sum,struct Line line,int cloumn_number)
{
	struct Node* p = gobal_lex_LinkList_head;
	struct Node* pOrg = p;
	struct Node* pnode = NULL;
	Token token;
	
	token.syn = token_type;
	token.sum = token_sum;
	strcpy(token.token, token_str);

	//�洢�ʷ��������������
	{
		pOrg = gobal_lex_LinkList_tail;

		//����\n����Ϊ1��\n
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
