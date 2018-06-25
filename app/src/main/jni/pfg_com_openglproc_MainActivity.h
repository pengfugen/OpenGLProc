/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class pfg_com_openglproc_MainActivity */

#ifndef _Included_pfg_com_openglproc_MainActivity
#define _Included_pfg_com_openglproc_MainActivity
#ifdef __cplusplus
extern "C" {
#endif
#undef pfg_com_openglproc_MainActivity_COLOR_RED
#define pfg_com_openglproc_MainActivity_COLOR_RED 0L
#undef pfg_com_openglproc_MainActivity_COLOR_GREEN
#define pfg_com_openglproc_MainActivity_COLOR_GREEN 1L
#undef pfg_com_openglproc_MainActivity_COLOR_BLUE
#define pfg_com_openglproc_MainActivity_COLOR_BLUE 2L
/*
 * Class:     pfg_com_openglproc_MainActivity
 * Method:    nativeSetColor
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_pfg_com_openglproc_MainActivity_nativeSetColor
  (JNIEnv *, jobject, jint);

/*
 * Class:     pfg_com_openglproc_MainActivity
 * Method:    nativeSurfaceInit
 * Signature: (Ljava/lang/Object;Ljava/lang/Object;)I
 */
JNIEXPORT jint JNICALL Java_pfg_com_openglproc_MainActivity_nativeSurfaceInit
  (JNIEnv *, jobject, jobject, jobject);

/*
 * Class:     pfg_com_openglproc_MainActivity
 * Method:    nativeSurfaceFinalize
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_pfg_com_openglproc_MainActivity_nativeSurfaceFinalize
  (JNIEnv *, jobject);

/*
 * Class:     pfg_com_openglproc_MainActivity
 * Method:    nativeShowBitmap
 * Signature: (Ljava/lang/Object;)I
 */
JNIEXPORT jint JNICALL Java_pfg_com_openglproc_MainActivity_nativeShowBitmap
  (JNIEnv *, jobject, jobject);

#ifdef __cplusplus
}
#endif
#endif