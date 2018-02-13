#pragma once

#define DLL_EXPORT		EXTERN_C __declspec(dllexport)

DLL_EXPORT int get_version(char* ver);
DLL_EXPORT int csc(char* filename);


