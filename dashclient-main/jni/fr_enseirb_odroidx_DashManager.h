#include <jni.h>
/* Header for class fr_enseirb_odroidx_DashManager */

#ifndef _Included_fr_enseirb_odroidx_DashManager
#define _Included_fr_enseirb_odroidx_DashManager
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     fr_enseirb_odroidx_DashManager
 * Method:    openStream
 * Signature: (Landroid/net/Uri;)I
 */
JNIEXPORT jint JNICALL Java_fr_enseirb_odroidx_DashManager_openStream(JNIEnv *, jobject, jstring);

/*
 * Class:     fr_enseirb_odroidx_DashManager
 * Method:    read
 * Signature: ([BI)I
 */
JNIEXPORT jint JNICALL Java_fr_enseirb_odroidx_DashManager_read(JNIEnv *, jobject, jbyteArray, jint);

#ifdef __cplusplus
}
#endif
#endif
