/*
 * Copyright (C) 2009 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */
#include <string.h>
#include <jni.h>

/* This is a trivial JNI example where we use a native method
 * to return a new VM String. See the corresponding Java source
 * file located at:
 *
 *   apps/samples/hello-jni/project/src/com/example/hellojni/HelloJni.java
 */
JNIEXPORT jstring JNICALL Java_com_example_fred_javatocpp_JavaToCpp_stringFromJNI( JNIEnv* env,
                                                  jobject thiz )
{
#if defined(__arm__)
  #if defined(__ARM_ARCH_7A__)
    #if defined(__ARM_NEON__)
      #if defined(__ARM_PCS_VFP)
        #define ABI "armeabi-v7a/NEON (hard-float)"
      #else
        #define ABI "armeabi-v7a/NEON"
      #endif
    #else
      #if defined(__ARM_PCS_VFP)
        #define ABI "armeabi-v7a (hard-float)"
      #else
        #define ABI "armeabi-v7a"
      #endif
    #endif
  #else
   #define ABI "armeabi"
  #endif
#elif defined(__i386__)
   #define ABI "x86"
#elif defined(__x86_64__)
   #define ABI "x86_64"
#elif defined(__mips64)  /* mips64el-* toolchain defines __mips__ too */
   #define ABI "mips64"
#elif defined(__mips__)
   #define ABI "mips"
#elif defined(__aarch64__)
   #define ABI "arm64-v8a"
#else
   #define ABI "unknown"
#endif

    return (*env)->NewStringUTF(env, "Hello from JNI !  Compiled with ABI " ABI ".");
}
//java中传递String并返回java显示
JNIEXPORT jstring JNICALL Java_com_example_fred_javatocpp_JavaToCpp_StringFromJava(JNIEnv *env,  jobject thiz ,jstring str){
    const jbyte* cstr;
    jboolean isCopy;
    cstr = (*env)->GetStringUTFChars(env, str , &isCopy);
    jstring returnstr;
    returnstr =  (*env)->NewStringUTF(env, cstr);
    (*env) ->ReleaseStringUTFChars(env, str, cstr);
    return returnstr;
}

JNIEXPORT jintArray JNICALL Java_com_example_fred_javatocpp_JavaToCpp_IntArrayFromJava(JNIEnv env, jobject thiz, jintArray javaArray){
    jintArray returnArray;
    int length;
    length = (*env).GetArrayLength(env, javaArray);
    returnArray = (*env).NewIntArray(env,length);
    jint nativeArray[10];
    (*env).GetIntArrayRegion(env, javaArray, 0, length, nativeArray);
    for (int i = 0; i < length / 2; ++i) {
        jint temp;
        temp = nativeArray[length - 1 - i];
        nativeArray[length - 1 - i] = nativeArray[i];
        nativeArray[i] = temp;
    }
    (*env).SetIntArrayRegion(env, returnArray, 0, length, nativeArray);
    return returnArray;
}