//
// Created by Mogua.
// Copyright © 2024 Mogua. All rights reserved.
//

#include "MoguaAndroidBridge.h"
#include <jni.h>

using namespace mogua;

static DataCallback installOnData = nullptr;
static ErrorCallback installOnError = nullptr;
static DataCallback openOnData = nullptr;
static ErrorCallback openOnError = nullptr;

static unordered_map<string, string> pendingInstallData = {};
static string pendingInstallError = "";
static unordered_map<string, string> pendingOpenData = {};
static string pendingOpenError = "";

jstring jobject2jstring(JNIEnv *env, jobject obj) {
    jclass stringClass = env->FindClass("java/lang/String");
    jmethodID valueOfMID = env->GetStaticMethodID(stringClass, "valueOf", "(Ljava/lang/Object;)Ljava/lang/String;");
    jstring str = (jstring)env->CallStaticObjectMethod(stringClass, valueOfMID, obj);
    return str;
}

unordered_map<string, string> javaMap2cppMap(JNIEnv *env, jobject map) {
    jclass mapClass = env->GetObjectClass(map);
    jmethodID getValueMID = env->GetMethodID(mapClass, "get", "(Ljava/lang/Object;)Ljava/lang/Object;");
    jmethodID keySetMID = env->GetMethodID(mapClass, "keySet", "()Ljava/util/Set;");
    jobject keySet = env->CallObjectMethod(map, keySetMID);

    jclass setClass = env->GetObjectClass(keySet);
    jmethodID toArrayMID = env->GetMethodID(setClass, "toArray", "()[Ljava/lang/Object;");
    jobjectArray keyArray = static_cast<jobjectArray>(env->CallObjectMethod(keySet, toArrayMID));

    unordered_map<string, string> umap;
    int keySize = env->GetArrayLength(keyArray);
    for (int i = 0; i < keySize; i++) {
        jstring key = (jstring)env->GetObjectArrayElement(keyArray, i);
        jobject valueObj = env->CallObjectMethod(map, getValueMID, key);
        jstring valueStr = jobject2jstring(env, valueObj);

        const char* keyCStr = env->GetStringUTFChars(key, nullptr);
        const char* valueCStr = env->GetStringUTFChars(valueStr, nullptr);
        umap[keyCStr] = valueCStr;
        env->ReleaseStringUTFChars(key, keyCStr);
        env->ReleaseStringUTFChars(valueStr, valueCStr);
    }
    return umap;
}

string throwable2string(JNIEnv *env, jthrowable throwable) {
    jclass throwableClass = env->FindClass("java/lang/Throwable");
    jmethodID getMessageMID = env->GetMethodID(throwableClass, "getMessage", "()Ljava/lang/String;");
    jstring messageStr = (jstring)env->CallObjectMethod(throwable, getMessageMID);

    const char* messageCStr = env->GetStringUTFChars(messageStr, nullptr);
    string message = string(messageCStr);
    env->ReleaseStringUTFChars(messageStr, messageCStr);
    return message;
}

void MoguaAndroidBridge::getInstallData(DataCallback onData, ErrorCallback onError) {
    installOnData = onData;
    installOnError = onError;
    if (!pendingInstallData.empty()) {
        installOnData(pendingInstallData);
        pendingInstallData.clear();
    }
    if (!pendingInstallError.empty()) {
        installOnError(pendingInstallError);
        pendingInstallError.clear();
    }
}

void MoguaAndroidBridge::getOpenData(DataCallback onData, ErrorCallback onError) {
    openOnData = onData;
    openOnError = onError;
    if (!pendingOpenData.empty()) {
        openOnData(pendingOpenData);
        pendingOpenData.clear();
    }
    if (!pendingOpenError.empty()) {
        openOnError(pendingOpenError);
        pendingOpenError.clear();
    }
}

extern "C"
JNIEXPORT void JNICALL
Java_io_mogua_sdk_MoguaCocosInstallCallback_jniOnData(JNIEnv *env, jobject thiz, jobject data) {
    unordered_map<string, string> umap = javaMap2cppMap(env, data);
    if (installOnData == nullptr) {
        pendingInstallData = umap;
        return;
    }
    installOnData(umap);
}

extern "C"
JNIEXPORT void JNICALL
Java_io_mogua_sdk_MoguaCocosInstallCallback_jniOnError(JNIEnv *env, jobject thiz, jthrowable e) {
    string errStr = throwable2string(env, e);
    if (installOnError == nullptr) {
        pendingInstallError = errStr;
        return;
    }
    installOnError(errStr);
}

extern "C"
JNIEXPORT void JNICALL
Java_io_mogua_sdk_MoguaCocosOpenCallback_jniOnData(JNIEnv *env, jobject thiz, jobject data) {
    unordered_map<string, string> umap = javaMap2cppMap(env, data);
    if (openOnData == nullptr) {
        pendingOpenData = umap;
        return;
    }
    openOnData(umap);
}

extern "C"
JNIEXPORT void JNICALL
Java_io_mogua_sdk_MoguaCocosOpenCallback_jniOnError(JNIEnv *env, jobject thiz, jthrowable e) {
    string errStr = throwable2string(env, e);
    if (openOnError == NULL) {
        pendingOpenError = errStr;
        return;
    }
    openOnError(errStr);
}
