#include "complier.h"
#include "lib.h"
#include "lex_list.h"
#include "grammar_list.h"
#include "arg.h"
#include "var.h"
#include "const.h"
#include "scanner.h"
#include "lex.h"
#include "grammer.h"
#include "quad_list.h"

void init() {
	lex_LinkList_Init();
	quad_list_init();
	gobal_grammar_LinkList_Init();
	gobal_arg_LinkList_init();
	gobal_var_init();
	gobal_cnt_list_init();
}

void destroy() {
	quad_list_destory();
	lex_LinkList_destory();
	//�ͷ�������Դ
	gobal_grammar_LinkList_destory();

}

/************************************************************************/
/* ����ű�                                                             */
/************************************************************************/
int CardScriptComplier(char* filename)
{
	char text[10240] = { 0 };
	FILE* file;
	int line;
	char path[512] = { 0 };

	strcpy(path, filename);

	init();

	//���ļ��ж�ȡ
	file = fopen(path, "r");
	if (file == NULL)
	{
		ErrorLog(gobal_logger, __FILE__, __LINE__, "file no fund,filename is \"%s\"\n", path);
		return 0;
	}

	line = 0;

	while (fgets(text, sizeof(text), file) != NULL) {
		scaner_sigle_line(text, line);
		line++;
	}


	fclose(file);

	InfoLog(gobal_logger, __FILE__, __LINE__, "-----the 1st scanner");

	//1��ɨ�裬�滻����
	scanner_first();

	//lex_LinkList_print();
	lex_list_merge_node();//�ϲ��ڵ�
	//lex_LinkList_print();

	InfoLog(gobal_logger, __FILE__, __LINE__, "----the 2nd scanner");

	scanner_second();
	lex_list_merge_node();//�ϲ��ڵ�
	lex_LinkList_print();

	//�﷨����LR����
	InfoLog(gobal_logger, __FILE__, __LINE__, "-----LR parser");

	lr_parser();

	//��ӡ
	//gobal_cnt_list_print();
	//gobal_arg_LinkList_print();
	gobal_var_LinkList_print();
	gobal_grammar_LinkList_print();


	destroy();
}

int test_main()
{
	char prop[] = "(1AEC004B659BCE20B00E47203218EDC0)>{dlk2}";
	//char prop[] = "if(";
	//char prop[] = "(1AEC004B659BCE20B00E47203218EDC0)>{dlk2}";
	//char prop[] = "(#KeyBlock_INIKey#)>{offset}";
	//char prop[] = "($iKeyDvsNum$)>{iKeyDvsNum}";
	//char prop[] = "(01{VAR0})>{psn}";
	//char prop[] = ";�ⲿ��֤";
	//char prop[] = "SubStr({psn},2)>{VAR0}";

	//char prop[] = "(1 + 2)>{dlk2}\n(2+3)>{var0}\n";
	//char prop[] = "(1 / 2)>{var1}";

	char text[10240] = { 0 };
	FILE* file;
	int line;
	char filename[1024] = { 0 };
	char path[512] = { 0 };

	strcpy(path, "/root/lex/cardscript/testcase/");


	//-------------------------�����滻����-------------------------------
	strcpy(filename, "1-1.txt");
	/*strcpy(filename, "1.�򵥸�ֵ.txt");*/
	//strcpy(filename,"2.�����滻��ֵ.txt");
	//strcpy(filename,"3.ָ���еĳ����滻.txt");
	//strcpy(filename,"4.���ж�������滻.txt");

	//-------------------------�����滻����-------------------------------
	// 	strcpy(filename,"2-1-�����滻-��ֵ���ʽ�еĲ����滻.txt");
	// 	strcpy(filename,"2-2-�����滻-��Ƭָ���еĲ����滻.txt);
	// 	strcpy(filename,"2-3-�����滻-���ж�������滻.txt);

	//-------------------------�������ʽ����-------------------------------
	//strcpy(filename,"3-1-�������ʽ��ֵ.txt");

	//-------------------------��������-------------------------------
	//strcpy(filename,"4-1-��������-�򵥵��ú�ֵ.txt");


	init();


	strcat(path, filename);

	//���ļ��ж�ȡ
	file = fopen(path, "r");


	if (file == NULL)
	{
		printf("file no fund,filename is \"%s\"\n", path);
		return 0;
	}

	line = 0;

	while (fgets(text, sizeof(text), file) != NULL) {
		scaner_sigle_line(text, line);
		line++;
	}


	fclose(file);


	//1��ɨ�裬�滻����
	scanner_first();

	lex_LinkList_print();
	lex_list_merge_node();//�ϲ��ڵ�
	lex_LinkList_print();

	scanner_second();
	lex_list_merge_node();//�ϲ��ڵ�
	lex_LinkList_print();

	//�﷨����LR����
	lr_parser();

	//��ӡ
	gobal_cnt_list_print();
	gobal_arg_LinkList_print();
	gobal_var_LinkList_print();
	gobal_grammar_LinkList_print();


	destroy();


	return 0;
}
