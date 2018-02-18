from ctypes import *


#load dll _cdel方式
dll = cdll.LoadLibrary('CardScriptComplier\Debug\CardScriptComplier.dll');

print("dll handle=",dll);


#获取版本号
p_version = create_string_buffer(512);
ret = dll.get_version(p_version);

s = string_at(p_version,-1).decode('gbk');

print("ret=",ret," version= ",s);

# 调用结果例子
# ret= 0  version=  model: CardScriptComplier | version: v1.0.1.20180214

