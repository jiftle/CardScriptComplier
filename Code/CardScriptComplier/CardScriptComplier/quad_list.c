#include "quad_list.h"


void quad_list_init()
{
	Quad* pnode = (Quad*)malloc(sizeof(Quad));
	if (pnode == NULL) {
		printf("malloc fail.");
	}

	strcpy(pnode->op, "");
	strcpy(pnode->arg1, "");
	strcpy(pnode->arg2, "");
	strcpy(pnode->result, "");

	pnode->pre = NULL;
	pnode->next = NULL;

	gobal_quad_list_head = pnode;
	gobal_quad_list_tail = pnode;
}

void quad_list_destory()
{
	Quad *p = gobal_quad_list_tail;
	Quad *pTmp = NULL;

	while (p)
	{
		pTmp = p->pre;
		free(p);

		p = pTmp;
	}

	gobal_quad_list_head = NULL;
	gobal_quad_list_tail = NULL;
}

void quad_list_add(char *op, char* arg1, char* arg2, char* result)
{
	Quad *p = gobal_quad_list_tail;
	Quad *pnode = NULL;
	char buf[512] = {0};

	pnode = (Quad*)malloc(sizeof(Quad));
	if (pnode == NULL) {
		printf("malloc fail.");
	}

	strcpy(pnode->op, op);
	strcpy(pnode->arg1, arg1);
	strcpy(pnode->arg2, arg2);
	strcpy(pnode->result, result);

	pnode->pre = gobal_quad_list_tail;
	pnode->next = NULL;

	gobal_quad_list_tail = pnode;

#if TEST_SHOW_DEBUG

	sprintf(buf, "debug (%s,%s,%s,%s)\n", pnode->op, pnode->arg1, pnode->arg2, pnode->result);

	//输出到控制台
	printf(buf);
#endif
}

