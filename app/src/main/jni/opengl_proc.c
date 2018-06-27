#include <string.h>
#include <stdint.h>
#include <jni.h>
#include <android/log.h>
#include <pthread.h>
#include <EGL/egl.h>
#include <GLES/gl.h>
#include <GLES/glext.h>
#include <EGL/eglext.h>
#include <android/native_window.h>
#include <android/native_window_jni.h>

#include <android/bitmap.h>
#include <atomic.h>


#define APP_NAME "OpenGlProc"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, APP_NAME, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, APP_NAME, __VA_ARGS__)

#define G_N_ELEMENTS(methods) (sizeof(methods)/sizeof(methods[0]))


ANativeWindow *new_native_window;
EGLSurface eglSurface;
EGLContext eglContext;
EGLDisplay eglDisplay;
EGLint mWidth;
EGLint mHeight;
GLuint mTextureId;
uint32_t mTransactionFlags = 0x00;


void native_set_color(JNIEnv *env, jobject obj, jint color)
{

}


int loadImage(uint8_t *pixels, int width, int height) {
    //glActiveTexture(GL_TEXTURE0);
    //glBindTexture(GL_TEXTURE_2D, mTextureId);
    //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0,
    //             GL_RGBA, GL_UNSIGNED_BYTE, pixels);
    //GLuint location = glGetUniformLocation(mGlProgram, "s_texture");
    //glUniform1i(location, 0);

    return 0;
}

int draw() {
    //glUseProgram(mGlProgram);

    //glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

    return 0;
}

int native_show_bitmap(JNIEnv *env, jobject obj, jobject bitmap)
{
    /*int ret = 0;
    AndroidBitmapInfo bitmapInfo;
    void *pixels = NULL;
    int imgWidth = 2;
    int imgHeight = 2;

    LOGI("native_show_bitmap enter");

    if ((ret = AndroidBitmap_getInfo(env, bitmap, &bitmapInfo)) < 0) {
        LOGE("AndroidBitmap_getInfo() failed ! error=%d", ret);
        return -1;
    }

    LOGI("native_show_bitmap width %d, height %d, format %d",
            bitmapInfo.width, bitmapInfo.height, bitmapInfo.format);
    imgWidth = bitmapInfo.width;
    imgHeight = bitmapInfo.height;

    if (bitmapInfo.format != ANDROID_BITMAP_FORMAT_RGBA_8888) {
        LOGE("native_show_bitmap invalid rgb format");
        return -1;
    }

    if ((ret = AndroidBitmap_lockPixels(env, bitmap, &pixels)) < 0) {
        LOGE("AndroidBitmap_lockPixels() failed ! error=%d", ret);
    }


        LOGI("EGLEngine::loadImage width %d, height %d", imgWidth, imgHeight);

        ret = setup(pixels, imgWidth, imgHeight);
        if (ret) {
            LOGE("EGLEngine::loadImage failed");
            return -1;
        }

        LOGI("EGLEngine::loadImage done");

    ret = draw();
    if (ret) {
        LOGE("EGLEngine::draw failed");
        return -1;
    }

    eglSwapBuffers(eglDisplay, eglSurface);

    LOGI("EGLEngine::draw done");
    AndroidBitmap_unlockPixels(env, bitmap);*/

    return 0;
}

uint32_t setTransactionFlags(uint32_t flags) {
    uint32_t old = android_atomic_or(flags, &mTransactionFlags);
    if ((old & flags)==0) { // wake the server up
       //LOGI("setTransactionFlags================flags:%02x, old:%02x, mTransactionFlags:%02x",flags, old, mTransactionFlags);
    }
    return old;
}

uint32_t peekTransactionFlags() {
    return android_atomic_release_load(&mTransactionFlags);
}

int native_surface_init(JNIEnv *env, jobject obj, jobject surface, jobject bitmap)
{
    /*EGLBoolean returnValue;
        EGLConfig myConfig = {0};

        EGLint context_attribs[] = { EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE };
        EGLint s_configAttribs[] = {
                EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
                EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
                EGL_RED_SIZE, 8,
                EGL_GREEN_SIZE, 8,
                EGL_BLUE_SIZE, 8,
                EGL_ALPHA_SIZE, 8,
                EGL_NONE };
        EGLint majorVersion;
        EGLint minorVersion;
        EGLContext context;
        EGLSurface eglsurface;
        EGLint w, h;

        EGLDisplay dpy;

        checkEglError("<init>");
        dpy = eglGetDisplay(EGL_DEFAULT_DISPLAY);
        checkEglError("eglGetDisplay");
        if (dpy == EGL_NO_DISPLAY) {
            printf("eglGetDisplay returned EGL_NO_DISPLAY.\n");
            return 0;
        }

        returnValue = eglInitialize(dpy, &majorVersion, &minorVersion);
        checkEglError("eglInitialize", returnValue);
        fprintf(stderr, "EGL version %d.%d\n", majorVersion, minorVersion);
        if (returnValue != EGL_TRUE) {
            printf("eglInitialize failed\n");
            return 0;
        }

        if (!printEGLConfigurations(dpy)) {
            printf("printEGLConfigurations failed\n");
            return 0;
        }

        checkEglError("printEGLConfigurations");

        WindowSurface windowSurface;
        EGLNativeWindowType window = windowSurface.getSurface();
        EGLint numConfigs = -1, n = 0;
        eglChooseConfig(dpy, s_configAttribs, 0, 0, &numConfigs);
        if (numConfigs) {
            EGLConfig* const configs = new EGLConfig[numConfigs];
            eglChooseConfig(dpy, s_configAttribs, configs, numConfigs, &n);
            myConfig = configs[0];
            delete[] configs;
        }

        checkEglError("EGLUtils::selectConfigForNativeWindow");

        printf("Chose this configuration:\n");
        printEGLConfiguration(dpy, myConfig);

        eglsurface = eglCreateWindowSurface(dpy, myConfig, window, NULL);
        checkEglError("eglCreateWindowSurface");
        if (eglsurface == EGL_NO_SURFACE) {
            printf("gelCreateWindowSurface failed.\n");
            return 0;
        }

        context = eglCreateContext(dpy, myConfig, EGL_NO_CONTEXT, context_attribs);
        checkEglError("eglCreateContext");
        if (context == EGL_NO_CONTEXT) {
            printf("eglCreateContext failed\n");
            return 0;
        }
        returnValue = eglMakeCurrent(dpy, eglsurface, eglsurface, context);
        checkEglError("eglMakeCurrent", returnValue);
        if (returnValue != EGL_TRUE) {
            return 0;
        }
        eglQuerySurface(dpy, eglsurface, EGL_WIDTH, &w);
        checkEglError("eglQuerySurface");
        eglQuerySurface(dpy, eglsurface, EGL_HEIGHT, &h);
        checkEglError("eglQuerySurface");
        GLint dim = w < h ? w : h;

        fprintf(stderr, "Window dimensions: %d x %d\n", w, h);

        printGLString("Version", GL_VERSION);
        printGLString("Vendor", GL_VENDOR);
        printGLString("Renderer", GL_RENDERER);
        printGLString("Extensions", GL_EXTENSIONS);

        if(!setupGraphics(w, h)) {
            fprintf(stderr, "Could not set up graphics.\n");
            return 0;
        }

        for (;;) {
            renderFrame(w, h);
            eglSwapBuffers(dpy, eglsurface);
            checkEglError("eglSwapBuffers");
        }*/

        AndroidBitmapInfo info;
        AndroidBitmap_getInfo(env, bitmap, & info);
        int dataLen = sizeof(int) *info.width * info.height;
        char *data = NULL;
        AndroidBitmap_lockPixels(env, bitmap, (void**)&data);

        LOGI("native_surface_init================Bitmap info width:%d, height:%d, stride:%d, dataLen:%d, format:%d",info.width,info.height,info.stride,dataLen, info.format);

        ANativeWindow * window = ANativeWindow_fromSurface(env, surface);


        //ANativeWindow_acquire(window);
        ANativeWindow_setBuffersGeometry(window, info.width, info.height, info.format);

        ANativeWindow_Buffer windowBuffer;
        ANativeWindow_lock(window, & windowBuffer, NULL);

        dataLen = sizeof(int)*windowBuffer.width * windowBuffer.height;
        LOGI("native_surface_init================Buffer info width:%d, height:%d, stride:%d, dataLen:%d, format:%d",windowBuffer.width,windowBuffer.height,windowBuffer.stride,dataLen, windowBuffer.format);

        if (windowBuffer.bits != NULL) {
            memcpy(windowBuffer.bits,data, sizeof(int) *info.width * info.height);
            /*if (windowBuffer.width == windowBuffer.stride) {
                memcpy(windowBuffer.bits, data, dataLen);
            } else {
                int offset = windowBuffer.stride - windowBuffer.width;
                int ii = 0;
                for (ii = 0; ii < windowBuffer.height * 2; ii++) {
                        char *srcPointer = data + windowBuffer.width * ii * 2;
                        char *dstPointer = ((char *)windowBuffer.bits)+windowBuffer.stride * ii * 2;

                        memcpy(dstPointer, srcPointer, windowBuffer.stride * 2);
                }
            }*/
        }
        AndroidBitmap_unlockPixels(env, bitmap);
        //ANativeWindow_release(window);

        ANativeWindow_unlockAndPost(window);
        uint32_t flags = 0x01;
        //setTransactionFlags(flags);
        //LOGI("native_surface_init================ flags:%02x",peekTransactionFlags());

        //setTransactionFlags(0x02);
        //setTransactionFlags(0x04);
        //LOGI("native_surface_init================ flags:%02x",peekTransactionFlags());
        return 0;
}


void native_surface_finalize(JNIEnv *env, jobject obj)
{

}

/* List of implemented native methods */
static JNINativeMethod native_methods[] = {
  { "nativeSetColor", "(I)V", (void *) native_set_color},
  { "nativeSurfaceInit", "(Ljava/lang/Object;Ljava/lang/Object;)I", (void *) native_surface_init},
  { "nativeSurfaceFinalize", "()V", (void *) native_surface_finalize},
  { "nativeShowBitmap", "(Ljava/lang/Object;)I", (void *) native_show_bitmap}
};

/* Library initializer */
jint JNI_OnLoad(JavaVM *vm, void *reserved) {
  JNIEnv *env = NULL;
  LOGI("JNI_Onload================");

  if ((*vm)->GetEnv(vm, (void**) &env, JNI_VERSION_1_4) != JNI_OK) {
    __android_log_print (ANDROID_LOG_ERROR, "tutorial-4", "Could not retrieve JNIEnv");
    return 0;
  }
  jclass klass = (*env)->FindClass (env, "pfg/com/openglproc/MainActivity");
  (*env)->RegisterNatives (env, klass, native_methods, G_N_ELEMENTS(native_methods));
  return JNI_VERSION_1_4;
}
