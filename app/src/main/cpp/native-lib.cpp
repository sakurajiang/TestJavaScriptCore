#include <jni.h>
#include <string>
#include "JavaScriptCore/JavaScript.h"
#include <iostream>
#include <android/log.h>
#define LOG_TAG "HELLO_JNI"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG ,__VA_ARGS__) // 定义LOGD类型

JSValueRef ObjectCallAsFunctionCallback(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception) {
    LOGD("Hello World");
    return JSValueMakeUndefined(ctx);
}

extern "C" JNIEXPORT jstring

JNICALL
Java_com_example_sakurajiang_testjavascriptcore_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    JSContextGroupRef contextGroup = reinterpret_cast<JSContextGroupRef>(JSContextGroupCreate());
    JSGlobalContextRef globalContext = JSGlobalContextCreateInGroup(contextGroup, nullptr);
    JSObjectRef globalObject = JSContextGetGlobalObject(globalContext);

    JSStringRef logFunctionName = JSStringCreateWithUTF8CString("document");
    JSObjectRef functionObject = JSObjectMakeFunctionWithCallback(globalContext, logFunctionName,
                                                                  ObjectCallAsFunctionCallback);

    JSObjectSetProperty(globalContext, globalObject, logFunctionName, functionObject, kJSPropertyAttributeNone, nullptr);

    JSStringRef logCallStatement = JSStringCreateWithUTF8CString("document()");

    JSEvaluateScript(globalContext, logCallStatement, nullptr, nullptr, 1,nullptr);

    /* memory management code to prevent memory leaks */

    JSGlobalContextRelease(globalContext);
    JSContextGroupRelease(contextGroup);
    JSStringRelease(logFunctionName);
    JSStringRelease(logCallStatement);
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}


