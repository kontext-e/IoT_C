#include "JniInterface.h"
#include "common.h"
#include <jni.h>
#include <stdint.h>
#include "library.h"


JNICallbackReference_t Open_GlobalRef;
JNICallbackReference_t Close_GlobalRef;
JNICallbackReference_t GetVersion_GlobalRef;
JNICallbackReference_t SetStartGeneration_GlobalRef;
JNICallbackReference_t CalculateGenerations_GlobalRef;

void Open_callback(uint8_t Return_Code) {
  JNIEnv *g_env = get_jni_env();
  if(g_env != NULL) {
    (*(g_env))->CallVoidMethod(g_env, Open_GlobalRef.jobj, Open_GlobalRef.jmid, Return_Code);
  }
}

void Close_callback(uint8_t Return_Code) {
  JNIEnv *g_env = get_jni_env();
  if(g_env != NULL) {
    (*(g_env))->CallVoidMethod(g_env, Close_GlobalRef.jobj, Close_GlobalRef.jmid, Return_Code);
  }
}

void GetVersion_callback(uint8_t Return_Code, byte_t* version) {
  JNIEnv *g_env = get_jni_env();
  if(g_env != NULL) {
    (*(g_env))->CallVoidMethod(g_env, GetVersion_GlobalRef.jobj, GetVersion_GlobalRef.jmid, Return_Code, asJbyteArray(version, 14));
  }
}

void SetStartGeneration_callback(uint8_t Return_Code) {
  JNIEnv *g_env = get_jni_env();
  if(g_env != NULL) {
    (*(g_env))->CallVoidMethod(g_env, SetStartGeneration_GlobalRef.jobj, SetStartGeneration_GlobalRef.jmid, Return_Code);
  }
}

void CalculateGenerations_callback(uint8_t Return_Code, uint8_t width, uint8_t height, byte_t* living_x, byte_t* living_y) {
  JNIEnv *g_env = get_jni_env();
  if(g_env != NULL) {
    (*(g_env))->CallVoidMethod(g_env, CalculateGenerations_GlobalRef.jobj, CalculateGenerations_GlobalRef.jmid, Return_Code, width, height, asJbyteArray(living_x, 1), asJbyteArray(living_y, 1));
  }
}

JNIEXPORT jlong JNICALL Java_de_kontext_1e_golaas_jni_JniInterface_registerOpenCB(JNIEnv *env, jclass cls, jobject java_callback) {
  const jlong status = save_callback_reference(env, java_callback, "(B)V", &Open_GlobalRef);
  if(status != 0) {
    return status;
  }
  
  return RegOpen(Open_callback);
}

JNIEXPORT jlong JNICALL Java_de_kontext_1e_golaas_jni_JniInterface_registerCloseCB(JNIEnv *env, jclass cls, jobject java_callback) {
  const jlong status = save_callback_reference(env, java_callback, "(B)V", &Close_GlobalRef);
  if(status != 0) {
    return status;
  }
  
  return RegClose(Close_callback);
}

JNIEXPORT jlong JNICALL Java_de_kontext_1e_golaas_jni_JniInterface_registerGetVersionCB(JNIEnv *env, jclass cls, jobject java_callback) {
  const jlong status = save_callback_reference(env, java_callback, "(B[B)V", &GetVersion_GlobalRef);
  if(status != 0) {
    return status;
  }
  
  return RegGetVersion(GetVersion_callback);
}

JNIEXPORT jlong JNICALL Java_de_kontext_1e_golaas_jni_JniInterface_registerSetStartGenerationCB(JNIEnv *env, jclass cls, jobject java_callback) {
  const jlong status = save_callback_reference(env, java_callback, "(B)V", &SetStartGeneration_GlobalRef);
  if(status != 0) {
    return status;
  }
  
  return RegSetStartGeneration(SetStartGeneration_callback);
}

JNIEXPORT jlong JNICALL Java_de_kontext_1e_golaas_jni_JniInterface_registerCalculateGenerationsCB(JNIEnv *env, jclass cls, jobject java_callback) {
  const jlong status = save_callback_reference(env, java_callback, "(BBB[B[B)V", &CalculateGenerations_GlobalRef);
  if(status != 0) {
    return status;
  }
  
  return RegCalculateGenerations(CalculateGenerations_callback);
}

JNIEXPORT jlong JNICALL Java_de_kontext_1e_golaas_jni_JniInterface_Open(JNIEnv *env, jclass cls) {
  
  return Open();
}

JNIEXPORT jlong JNICALL Java_de_kontext_1e_golaas_jni_JniInterface_Close(JNIEnv *env, jclass cls) {
  
  return Close();
}

JNIEXPORT jlong JNICALL Java_de_kontext_1e_golaas_jni_JniInterface_GetVersion(JNIEnv *env, jclass cls) {
  
  return GetVersion();
}

JNIEXPORT jlong JNICALL Java_de_kontext_1e_golaas_jni_JniInterface_SetStartGeneration(JNIEnv *env, jclass cls, jint Width, jint Height, jbyteArray Living_x, jbyteArray Living_y) {
  const jsize Living_x_count = (*(env))->GetArrayLength(env, Living_x);
  const jsize Living_y_count = (*(env))->GetArrayLength(env, Living_y);
  uint8_t Living_x_target[Living_x_count+1];
  uint8_t Living_y_target[Living_y_count+1];
  
  return SetStartGeneration(Width, Height, asByteArray(Living_x_count, Living_x, Living_x_target), asByteArray(Living_y_count, Living_y, Living_y_target));
}

JNIEXPORT jlong JNICALL Java_de_kontext_1e_golaas_jni_JniInterface_CalculateGenerations(JNIEnv *env, jclass cls, jint number_of_generations) {
  
  return CalculateGenerations(number_of_generations);
}

JNIEXPORT jlong JNICALL Java_de_kontext_1e_golaas_jni_JniInterface_initialize(JNIEnv *env, jclass cls) {
  save_g_vm(env);

  return 0;
}

JNIEXPORT jlong JNICALL Java_de_kontext_1e_golaas_jni_JniInterface_testCallbackCalls(JNIEnv *env1, jclass cls) {
  {
    uint8_t Return_Code = {0};
    Open_callback(Return_Code);
  }
  {
    uint8_t Return_Code = {0};
    Close_callback(Return_Code);
  }
  {
    uint8_t Return_Code = {0};
    byte_t* version = {0};
    GetVersion_callback(Return_Code, version);
  }
  {
    uint8_t Return_Code = {0};
    SetStartGeneration_callback(Return_Code);
  }
  {
    uint8_t Return_Code = {0};
    uint8_t width = {0};
    uint8_t height = {0};
    byte_t* living_x = {0};
    byte_t* living_y = {0};
    CalculateGenerations_callback(Return_Code, width, height, living_x, living_y);
  }
  return 0;
}

