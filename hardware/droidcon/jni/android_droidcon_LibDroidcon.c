#include <libdroidcon.h>

#include <jni.h>

static void ThrowDroidconException(JNIEnv *env, const char *message) {
  jclass class = (*env)->FindClass(env, "fr/droidcon/DroidconException");
  if (class != NULL) {
    (*env)->ThrowNew(env, class, message);
  }
  (*env)->DeleteLocalRef(env, class);
}

JNIEXPORT void JNICALL Java_android_droidcon_LibDroidcon_clear(JNIEnv *env, jclass cls)
{
    droidcon_clear();
}


JNIEXPORT jstring JNICALL Java_android_droidcon_LibDroidcon_getData(JNIEnv *env, jclass cls)
{
    char buff[1024];
    int ret = droidcon_getdata(buff, 1024);
    if (ret < 0) {
        ThrowDroidconException(env, "fail to get data");
    }
    return (*env)->NewStringUTF(env, buff);

}

JNIEXPORT void JNICALL Java_android_droidcon_LibDroidcon_putData(JNIEnv *env, jclass cls, jstring string)
{
    int ret;
    const char *buff = (*env)->GetStringUTFChars(env, string, NULL);
    int length = (*env)->GetStringLength(env, string);
    ret = droidcon_putdata(buff, length);
    if (ret < 0) {
        ThrowDroidconException(env, "fail to put data");
    }
    (*env)->ReleaseStringUTFChars(env, string, buff);
}
