#include "fr_enseirb_odroidx_DashManager.h"
#include "include/IDASHManager.h"
#include "include/libdash.h"
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

using namespace dash;

JNIEXPORT jint JNICALL Java_fr_enseirb_odroidx_DashManager_openStream(JNIEnv * env, jobject obj, jstring uri) {
	const char* mediaUrl = env->GetStringUTFChars(uri, NULL);
	if (mediaUrl == NULL) {
		return EXIT_FAILURE;
	}
	IDASHManager* manager = CreateDashManager();
	manager->open(const_cast<char*> (mediaUrl));
	return EXIT_SUCCESS;
}

JNIEXPORT jint JNICALL Java_fr_enseirb_odroidx_DashManager_read(JNIEnv * env, jobject object, jbyteArray buffer, jint size) {
	return EXIT_SUCCESS;
}

#ifdef __cplusplus
}
#endif
