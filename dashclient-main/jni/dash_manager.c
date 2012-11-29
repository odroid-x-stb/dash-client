#include "fr_enseirb_odroidx_DashManager.h"
#include <stdlib.h>

JNIEXPORT jint JNICALL Java_fr_enseirb_odroidx_DashManager_openStream(JNIEnv * env, jobject obj, jstring uri) {
	const char* mediaUrl = (*env)->GetStringUTFChars(env, uri, NULL);
	if (mediaUrl == NULL) {
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

JNIEXPORT jint JNICALL Java_fr_enseirb_odroidx_DashManager_read(JNIEnv * env, jobject object, jbyteArray buffer, jint size) {
	return EXIT_SUCCESS;
}
