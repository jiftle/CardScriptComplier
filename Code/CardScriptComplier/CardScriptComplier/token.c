#include "token.h"
#include "util.h"

//获得类别
void get_token_str(int syn,char* name){
	switch (syn)
	{
	case TOKEN_KEYWORD_IF:
		strcpy(name,"if");
		break;
	case TOKEN_KEYWORD_ELSE:
		strcpy(name,"if");
		break;
	case TOKEN_KEYWORD_RETURN:
		strcpy(name,"return");
		break;
	case TOKEN_KEYWORD_NULL:
		strcpy(name,"null");
		break;
	case TOKEN_EVEL:
		strcpy(name,"evel");
		break;
	case TOKEN_KEYWORD_ID:
		strcpy(name,"id");
		break;
	case TOKEN_DELIMITER_FUNC_LEFT:
		strcpy(name,"func_left");
		break;
	case TOKEN_DELIMITER_FUNC_RIGHT:
		strcpy(name,"func_right");
		break;
	case TOKEN_DELIMITER_VAR_LEFT:
		strcpy(name,"var_left");
		break;
	case TOKEN_DELIMITER_VAR_RIGHT:
		strcpy(name,"var_right");
		break;
	case TOKEN_DELIMITER_COMMA:
		strcpy(name, ",");
		break;
	case TOKEN_KEYWORD_CRLF:
		strcpy(name,"line feed");
		break;
	case TOKEN_DELIMITER_CNT:
		strcpy(name, "const");
		break;
	case TOKEN_DELIMITER_ARG:
		strcpy(name, "arg");
		break;
	case TOKEN_CMD:
		strcpy(name, "cmd");
		break;
	case TOKEN_VAR:
		strcpy(name, "var");
		break;
	case TOKEN_ADD:
		strcpy(name, "add");
		break;
	case TOKEN_SUB:
		strcpy(name, "sub");
		break;
	case TOKEN_MUL:
		strcpy(name, "mul");
		break;
	case TOKEN_DIV:
		strcpy(name, "div");
		break;
	case TOKEN_MOD:
		strcpy(name, "mod");
		break;
	case TOKEN_BIN_AND:
		strcpy(name, "and");
		break;
	case TOKEN_BIN_OR:
		strcpy(name, "or");
		break;
	case TOKEN_BIN_XOR:
		strcpy(name, "xor");
		break;
	case TOKEN_RELATE_EQUAL:
		strcpy(name, "==");
		break;
	case TOKEN_RELATE_NOT_EQUAL:
		strcpy(name, "!=");
		break;
	case TOKEN_RELATE_LESS:
		strcpy(name, "<");
		break;
	case TOKEN_RELATE_LESS_EQUAL:
		strcpy(name, "<=");
		break;
	
	default:
		strcpy(name,"unkown token");
		break;
	}
}

//获得种别码
int get_token_type(char* p) {

	//转换成小写
	str_to_lower(p);

	//"if", "else", "return", "null"
	if (strcmp(p,"if") == 0) {
		return TOKEN_KEYWORD_IF;
	}
	else if (strcmp(p,"else") == 0) {
		return TOKEN_KEYWORD_ELSE;
	}
	else if (strcmp(p, "return") == 0) {
		return TOKEN_KEYWORD_RETURN;
	}
	else if (strcmp(p, "null") == 0) {
		return TOKEN_KEYWORD_NULL;
	}
	//"==", "!=", "<", "<=" //关系运算符
	//	, "+", "-", "*", "/", "%", "&", "|" //算术运算符
	//	, "&&", "||" //逻辑运算符
	//	, ">" //赋值符
	else if (strcmp(p, "==") == 0) {
		return TOKEN_RELATE_EQUAL;
	}
	else if (strcmp(p, "!=") == 0) {
		return TOKEN_RELATE_NOT_EQUAL;
	}
	else if (strcmp(p, "<") == 0) {
		return TOKEN_KEYWORD_NULL;
	}
	else if (strcmp(p, "<=") == 0) {
		return TOKEN_KEYWORD_NULL;
	}
	else if (strcmp(p, "+") == 0) {
		return TOKEN_ADD;
	}
	else if (strcmp(p, "-") == 0) {
		return TOKEN_SUB;
	}
	else if (strcmp(p, "*") == 0) {
		return TOKEN_MUL;
	}
	else if (strcmp(p, "/") == 0) {
		return TOKEN_DIV;
	}
	else if (strcmp(p, "%") == 0) {
		return TOKEN_MOD;
	}
	else if (strcmp(p, "&") == 0) {
		return TOKEN_KEYWORD_NULL;
	}
	else if (strcmp(p, "|") == 0) {
		return TOKEN_KEYWORD_NULL;
	}
	else if (strcmp(p, "&&") == 0) {
		return TOKEN_KEYWORD_NULL;
	}
	else if (strcmp(p, "||") == 0) {
		return TOKEN_KEYWORD_NULL;
	}
	else if (strcmp(p, ">") == 0) {
		return TOKEN_EVEL;
	}
	
	//'#', //常量
	//	'$' //参数
	//	, '{'  //变量
	//	, '}'
	//	, ','
	//	, '('
	//	, ')'
	//===============================种别码==============================
//#define TOKEN_DELIMITER_CNT 1 //常量
//#define TOKEN_DELIMITER_ARG   2 //参数
//#define TOKEN_DELIMITER_RES   3 //系统内置变量
//#define TOKEN_DELIMITER_VAR   4 //变量
	else if (strcmp(p, "#") == 0) {
		return TOKEN_DELIMITER_CNT;
	}
	else if (strcmp(p, "$") == 0) {
		return TOKEN_DELIMITER_ARG;
	}
	else if (strcmp(p, "{") == 0) {
		return TOKEN_DELIMITER_VAR_LEFT;
	}
	else if (strcmp(p, "}") == 0) {
		return TOKEN_DELIMITER_VAR_RIGHT;
	}
	else if (strcmp(p, ",") == 0) {
		return TOKEN_DELIMITER_COMMA;
	}
	else if (strcmp(p, "(")==0) {
		return TOKEN_DELIMITER_FUNC_LEFT;
	}
	else if (strcmp(p, ")")==0) {
		return TOKEN_DELIMITER_FUNC_RIGHT;
	}else{
		return -1;
	}
	
}