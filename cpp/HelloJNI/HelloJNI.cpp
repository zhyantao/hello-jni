#include "pch.h"
#include "HelloJNI.h"

#include <iostream>

std::string jstring2string(JNIEnv* env, jstring jstr);

/*
* �� "����̨��Ŀ" ת��Ϊ "DLL ��Ŀ"
*	1. ��Ŀ���� > ���� > �������� > ѡ�� ��̬��(.dll)
*	2. ��Ŀ���� > C/C++ > Ԥ������ > ��� _USRDLL
*
*
* �� "DLL ��Ŀ" ת��Ϊ "����̨��Ŀ"
*	1. ��Ŀ���� > C/C++ > Ԥ������ > ��� _CONSOLE
*	2. ��Ŀ���� > ������ > ϵͳ > ��ϵͳ > ѡ�� ����̨(/SUBSYSTEM:CONSOLE)
*/
API_DLL void main(std::string str) {
	std::cout << "Print By C++\t" << str << std::endl;
}

// �����û����� C++ ��ʵ�� Java �������ķ���
JNIEXPORT jobject JNICALL Java_org_example_HelloJNI_createUser
(JNIEnv* env, jobject thisObject, jstring name, jdouble balance, jobjectArray weekday) {

	// ���� UserData ����
	jclass userDataClass = env->FindClass("org/example/UserData");
	jobject newUserData = env->AllocObject(userDataClass);

	// ��ȡ UserData ���������
	jfieldID nameField = env->GetFieldID(userDataClass, "name", "Ljava/lang/String;"); // Java String ����
	jfieldID balanceField = env->GetFieldID(userDataClass, "balance", "D"); // Java double ����
	jfieldID weekdayField = env->GetFieldID(userDataClass, "weekday", "[Ljava/lang/String;"); // Java String ����

	// ���� env��Java �ķ�����ƣ����ö�������
	env->SetObjectField(newUserData, nameField, name);
	env->SetDoubleField(newUserData, balanceField, balance);
	env->SetObjectField(newUserData, weekdayField, weekday);

	return newUserData;
}

// ��ӡ�û���Ϣ���� C++ ��ʵ�� Java �������ķ���
JNIEXPORT jstring JNICALL Java_org_example_HelloJNI_printUserData
(JNIEnv* env, jobject thisObject, jobject userData) {

	// ��ȡ��Ҫ�����õķ�����Java ������ƣ�
	jclass userDataClass = env->GetObjectClass(userData);
	jmethodID methodId = env->GetMethodID(userDataClass, "getUserInfo", "()Ljava/lang/String;");

	jstring result = (jstring)env->CallObjectMethod(userData, methodId);

	// jstring ת��Ϊ string
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
