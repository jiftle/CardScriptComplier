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
	//释放链表资源
	gobal_grammar_LinkList_destory();

}

/************************************************************************/
/* 编译脚本                                                             */
/************************************************************************/
int CardScriptComplier(char* filename)
{
	char text[10240] = { 0 };
	FILE* file;
	int line;
	char path[512] = { 0 };

	strcpy(path, filename);

	init();

	//从文件中读取
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

	//1趟扫描，替换常量
	scanner_first();

	//lex_LinkList_print();
	lex_list_merge_node();//合并节点
	//lex_LinkList_print();

	InfoLog(gobal_logger, __FILE__, __LINE__, "----the 2nd scanner");

	scanner_second();
	lex_list_merge_node();//合并节点
	lex_LinkList_print();

	//语法分析LR分析
	InfoLog(gobal_logger, __FILE__, __LINE__, "-----LR parser");

	lr_parser();

	//打印
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
	//char prop[] = ";外部认证";
	//char prop[] = "SubStr({psn},2)>{VAR0}";

	//char prop[] = "(1 + 2)>{dlk2}\n(2+3)>{var0}\n";
	//char prop[] = "(1 / 2)>{var1}";

	char text[10240] = { 0 };
	FILE* file;
	int line;
	char filename[1024] = { 0 };
	char path[512] = { 0 };

	strcpy(path, "/root/lex/cardscript/testcase/");


	//-------------------------常量替换测试-------------------------------
	strcpy(filename, "1-1.txt");
	/*strcpy(filename, "1.简单赋值.txt");*/
	//strcpy(filename,"2.常量替换赋值.txt");
	//strcpy(filename,"3.指令中的常量替换.txt");
	//strcpy(filename,"4.含有多个常量替换.txt");

	//-------------------------参数替换测试-------------------------------
	// 	strcpy(filename,"2-1-参数替换-赋值表达式中的参数替换.txt");
	// 	strcpy(filename,"2-2-参数替换-卡片指令中的参数替换.txt);
	// 	strcpy(filename,"2-3-参数替换-含有多个参数替换.txt);

	//-------------------------算术表达式测试-------------------------------
	//strcpy(filename,"3-1-算术表达式求值.txt");

	//-------------------------函数测试-------------------------------
	//strcpy(filename,"4-1-函数测试-简单调用后赋值.txt");


	init();


	strcat(path, filename);

	//从文件中读取
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


	//1趟扫描，替换常量
	scanner_first();

	lex_LinkList_print();
	lex_list_merge_node();//合并节点
	lex_LinkList_print();

	scanner_second();
	lex_list_merge_node();//合并节点
	lex_LinkList_print();

	//语法分析LR分析
	lr_parser();

	//打印
	gobal_cnt_list_print();
	gobal_arg_LinkList_print();
	gobal_var_LinkList_print();
	gobal_grammar_LinkList_print();


	destroy();


	return 0;
}
