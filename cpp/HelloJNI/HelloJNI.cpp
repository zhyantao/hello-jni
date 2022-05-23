#include "pch.h"
#include "HelloJNI.h"

#include <iostream>

std::string jstring2string(JNIEnv* env, jstring jstr);

/*
* 将 "控制台项目" 转换为 "DLL 项目"
*	1. 项目属性 > 常规 > 配置类型 > 选择 动态库(.dll)
*	2. 项目属性 > C/C++ > 预处理器 > 添加 _USRDLL
*
*
* 将 "DLL 项目" 转换为 "控制台项目"
*	1. 项目属性 > C/C++ > 预处理器 > 添加 _CONSOLE
*	2. 项目属性 > 链接器 > 系统 > 子系统 > 选择 控制台(/SUBSYSTEM:CONSOLE)
*/
API_DLL void main(std::string str) {
	std::cout << "Print By C++\t" << str << std::endl;
}

// 创建用户：在 C++ 中实现 Java 中声明的方法
JNIEXPORT jobject JNICALL Java_org_example_HelloJNI_createUser
(JNIEnv* env, jobject thisObject, jstring name, jdouble balance, jobjectArray weekday) {

	// 创建 UserData 对象
	jclass userDataClass = env->FindClass("org/example/UserData");
	jobject newUserData = env->AllocObject(userDataClass);

	// 获取 UserData 对象的属性
	jfieldID nameField = env->GetFieldID(userDataClass, "name", "Ljava/lang/String;"); // Java String 类型
	jfieldID balanceField = env->GetFieldID(userDataClass, "balance", "D"); // Java double 类型
	jfieldID weekdayField = env->GetFieldID(userDataClass, "weekday", "[Ljava/lang/String;"); // Java String 数组

	// 利用 env（Java 的反射机制）设置对象属性
	env->SetObjectField(newUserData, nameField, name);
	env->SetDoubleField(newUserData, balanceField, balance);
	env->SetObjectField(newUserData, weekdayField, weekday);

	return newUserData;
}

// 打印用户信息：在 C++ 中实现 Java 中声明的方法
JNIEXPORT jstring JNICALL Java_org_example_HelloJNI_printUserData
(JNIEnv* env, jobject thisObject, jobject userData) {

	// 获取需要被调用的方法（Java 反射机制）
	jclass userDataClass = env->GetObjectClass(userData);
	jmethodID methodId = env->GetMethodID(userDataClass, "getUserInfo", "()Ljava/lang/String;");

	jstring result = (jstring)env->CallObjectMethod(userData, methodId);

	// jstring 转换为 string
	std::string str = jstring2string(env, result);
	main(str);

	return result;
}


std::string jstring2string(JNIEnv* env, jstring jstr) {

	jclass clsstring = env->FindClass("java/lang/String");

	jstring strencode = env->NewStringUTF("UTF8");
	jmethodID mid = env->GetMethodID(clsstring, "getBytes", "(Ljava/lang/String;)[B");

	jbyteArray barr = (jbyteArray)env->CallObjectMethod(jstr, mid, strencode);
	jsize alen = env->GetArrayLength(barr);
	jbyte* ba = env->GetByteArrayElements(barr, JNI_FALSE);

	char* tmp = NULL;
	if (alen > 0) {
		tmp = (char*)malloc(alen + 1);
		if (tmp == NULL) {
			std::cout << "malloc error" << std::endl;
			exit(-1);
		}
		else {
			memcpy(tmp, ba, alen);
			tmp[alen] = '\0';
			env->ReleaseByteArrayElements(barr, ba, 0);
			std::string str(tmp);
			free(tmp);
			return str;
		}
	}
	else {
		exit(-1);
	}
}
