#include <stdio.h>
#include <dlfcn.h>

//-----------------定义动态库接口-----------------
typedef int(*fn_get_version)(char* ver);
typedef int(*fn_max)(int a, int b);
typedef int (*fn_csc)(char* filename);

void* dll_handle = NULL;
char szLibName[] = { "libCardScriptComplier.so" };

fn_get_version get_version = NULL;
fn_max max = NULL;
fn_csc csc = NULL;

//-----------------动态库加载和释放-----------------
int dll_load(void* hdl)
{
	char* perr = NULL;

	//加载动态库
	hdl = dlopen(szLibName, RTLD_NOW);//RTLD_LAZY
	if (!hdl)
	{
		printf("load dll fail,dll:%s.\n", szLibName);
		return;
	}

	//绑定函数指针
	get_version = (fn_get_version)dlsym(hdl, "get_version");
	perr = dlerror();
	if (perr)
	{
		printf("load symbol failed: %s\n", perr);
		return;
	}

	/*max = (fn_max)dlsym(hdl, "max");
	perr = dlerror();
	if (perr)
	{
		printf("load symbol failed: %s\n", perr);
		return;
	}*/

	csc = (fn_csc)dlsym(hdl, "csc");
	perr = dlerror();
	if (perr)
	{
		printf("load symbol failed: %s\n", perr);
		return;
	}


}

int dll_unload(void* hdl)
{
	if (!hdl)
	{
		printf("hdl is null\n");
		return;
	}
	dlclose(hdl);
}

int main()
{
	dll_load(dll_handle);

	char szVer[256] = { 0 };
	int ret = get_version(szVer);
	if (ret == 0)
	{
		printf("verinfo: %s\n", szVer);
	}


	ret = csc("/root/sotest/testcase/1-1.txt");
	if (ret == 0)
	{
		printf("csc success\n");
	}
	else
	{
		printf("csc failed\n");
	}
	

	dll_unload(dll_handle);

	return 0;
}

//int main()
//{
//    //printf("entery in main\n");
//	char* perr = NULL;
//
//	void* hdl = dlopen("liblinuxdlltest.so.1.0", RTLD_NOW);//RTLD_LAZY
//	if (!hdl)
//	{
//		printf("load dll fail\n");
//		return;
//	}
//
//	fn_get_version get_version = (fn_get_version)dlsym(hdl, "get_version");
//	perr = dlerror();
//	if (perr)
//	{
//		printf("load symbol failed: %s\n", perr);
//		return;
//	}
//
//	char szVer[256] = { 0 };
//	int ret = get_version(szVer);
//	if (ret == 0)
//	{
//		printf("verinfo: %s\n", szVer);
//	}
//
//	fn_max max = (fn_max)dlsym(hdl, "max");
//	perr = dlerror();
//	if (perr)
//	{
//		printf("load symbol failed: %s\n", perr);
//		return;
//	}
//
//	/*for (int i=0;i<1000*100 * 100 * 1000 * 1000;i++)
//	{*/
//		int result = max(200, 123);
//
//		printf("the max is %d\n", result);
//		/*}
//		*/
//
//	dlclose(hdl);
//
//
//	//printf("exit main\n");
//
//    return 0;
//}