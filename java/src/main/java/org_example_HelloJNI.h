/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class org_example_HelloJNI */

#ifndef _Included_org_example_HelloJNI
#define _Included_org_example_HelloJNI
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     org_example_HelloJNI
 * Method:    createUser
 * Signature: (Ljava/lang/String;D[Ljava/lang/String;)Lorg/example/UserData;
 */
JNIEXPORT jobject JNICALL Java_org_example_HelloJNI_createUser
  (JNIEnv *, jobject, jstring, jdouble, jobjectArray);

/*
 * Class:     org_example_HelloJNI
 * Method:    printUserData
 * Signature: (Lorg/example/UserData;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_example_HelloJNI_printUserData
  (JNIEnv *, jobject, jobject);

#ifdef __cplusplus
}
#endif
#endif
