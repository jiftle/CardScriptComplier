#pragma once
#include "lib.h"

void gobal_cnt_list_init();
void gobal_cnt_list_add(char* name, int value);

int gobal_cnt_list_get(char* name, int *value);

int lookup_cnt(char* name, int* value);

void gobal_cnt_list_print();