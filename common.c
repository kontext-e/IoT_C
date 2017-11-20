#include <stdint.h>
#include <stdlib.h>
#include "common.h"
#include <jni.h>

// global reference to the JVM
static JavaVM *g_vm;

void printError(char *msg) {
    // maybe you want to call a special registered callback for messages
}

void save_g_vm(JNIEnv *env)
{
    (*env)->GetJavaVM(env, &g_vm);
}

jlong save_callback_reference(JNIEnv *env, jobject callback, const char *sig, JNICallbackReference_t *jniCallbackReference)
{
	// convert local to global reference
	// (local will die after this method call)
	jniCallbackReference->jobj = (*env)->NewGlobalRef(env, callback);

	// save refs for callback
	jclass g_clazz = (*env)->GetObjectClass(env, jniCallbackReference->jobj);
	if (g_clazz == NULL) {
		return 1;
	}

	jniCallbackReference->jmid = (*env)->GetMethodID(env, g_clazz, "callback", sig);
	if (jniCallbackReference->jmid == NULL) {
		return 1;
	}

	return 0;
}

JNIEnv * get_jni_env()
{
	JNIEnv * g_env1 = NULL;

	if (g_vm == NULL) {
		printError("g_vm == NULL\n");
		return g_env1;
	}

	int getEnvStat = (*g_vm)->GetEnv(g_vm, (void **)&g_env1, JNI_VERSION_1_8);

	if (getEnvStat == JNI_EDETACHED) {
		if ((*g_vm)->AttachCurrentThread(g_vm, (void **)&g_env1, NULL) != 0) {
			printError("Failed to attach\n");
		}
	}
	else if (getEnvStat == JNI_EVERSION) {
		printError("GetEnv: version not supported\n");
	}

	return g_env1;
}

uint8_t* asByteArray(jint count, jbyteArray in, uint8_t *target)
{
	JNIEnv *g_env = get_jni_env();

	if ((count < 1) || (target == NULL)) {
		return target;
	}

    target[0] = count;
	jbyte *body = (*(g_env))->GetByteArrayElements(g_env, in, 0);
	for (int i = 0; i < count; i++) {
		target[i+1] = body[i];
	}
	(*(g_env))->ReleaseByteArrayElements(g_env, in, body, 0);
	return target;
}

uint16_t* asShortArray(jint count, jshortArray in, uint16_t *target)
{
	JNIEnv *g_env = get_jni_env();

	if ((count < 1) || (target == NULL) || (in == NULL) || ((*(g_env))->GetArrayLength(g_env, in) < 1) ) {
		return target;
	}

	jshort *body = (*(g_env))->GetShortArrayElements(g_env, in, 0);
	for (int i = 0; i < count; i++) {
		target[i] = body[i];
	}
	(*(g_env))->ReleaseShortArrayElements(g_env, in, body, 0);
	return target;
}

uint32_t* asIntArray(jint count, jintArray in, uint32_t *target)
{
	JNIEnv *g_env = get_jni_env();

	if ((count < 1) || (target == NULL) || (in == NULL) || ((*(g_env))->GetArrayLength(g_env, in) < 1 ) ) {
		printError("Array length is lower than 1, returning an empty array instead\n");
		return target;
	}

	jint *body = (*(g_env))->GetIntArrayElements(g_env, in, 0);
	for (int i = 0; i < count; i++) {
		target[i] = body[i];
	}
	(*(g_env))->ReleaseIntArrayElements(g_env, in, body, 0);
	return target;
}

jbyteArray asJbyteArray(byte_t* in, jsize len)
{
	JNIEnv *g_env = get_jni_env();

	if ( (len < 1) || (in == NULL)) {
		printError("Array length is lower than 1, returning an empty array instead\n");
		return (*(g_env))->NewByteArray(g_env, 1);
	}

	jbyteArray ret = (*(g_env))->NewByteArray(g_env, len);
	(*(g_env))->SetByteArrayRegion(g_env, ret, 0, len, in);
	return ret;
}
