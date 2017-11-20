/*
 * Contains somme commonly used functions which are needed for most JNI projects
 */

#ifndef JNI_COMMON_H
#define JNI_COMMON_H

typedef long __int64;

#include <jni.h>

typedef struct JNICallbackReference_t {
    jclass jobj;
    jmethodID jmid;
} JNICallbackReference_t;

typedef uint8_t byte_t;

JNIEnv * get_jni_env();

void save_g_vm(JNIEnv * env);

jbyteArray asJbyteArray(byte_t* in, jsize len);

jlong save_callback_reference(JNIEnv *env, jobject callback, const char *sig, JNICallbackReference_t *jniCallbackReference);

uint8_t* asByteArray(jint count, jbyteArray in, uint8_t *target);
uint16_t* asShortArray(jint count, jshortArray in, uint16_t *target);
uint32_t* asIntArray(jint count, jintArray in, uint32_t *target);

#endif //JNI_COMMON_H
