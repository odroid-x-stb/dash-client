#include "fr_enseirb_odroidx_DashManager.h"
#include "include/IDASHManager.h"
#include "include/libdash.h"
#include <stdlib.h>
#include <android/log.h>

#ifdef __cplusplus
extern "C" {
#endif

using namespace dash;

static void sleep_by_nanosleep(time_t sec, long nsec) {
    const timespec tm = {sec, nsec};
    nanosleep(&tm, NULL);
    return;
}

JNIEXPORT jint JNICALL Java_fr_enseirb_odroidx_DashManager_openStream(JNIEnv * env, jobject obj, jstring uri) {
	const char* mediaUrl = env->GetStringUTFChars(uri, NULL);
	if (mediaUrl == NULL) {
		return EXIT_FAILURE;
	}
	__android_log_print(ANDROID_LOG_ERROR, "DEBUG", "Media: %s", mediaUrl);
	IDASHManager* manager = CreateDashManager();
	manager->setBufferLength(30);
	bool is_opened = manager->open(const_cast<char*> (mediaUrl));
	__android_log_print(ANDROID_LOG_ERROR, "DEBUG", "Opened: %s", is_opened ? "true" : "false");
	if(!manager->start()) {
		__android_log_print(ANDROID_LOG_ERROR, "DEBUG", "Could not start DASHManager!");
		return EXIT_FAILURE;
	}

	uint8_t *p_data = new uint8_t[32768];
	//file.open("bunny.vh4", ios::out | ios::binary);
	int ret = manager->read(p_data, 32768);
	while(ret) {
		sleep_by_nanosleep(0, 500000);
		//file.write((char *)p_data, ret);
		ret = manager->read(p_data, 32768);
	}
	//file.close();
	__android_log_print(ANDROID_LOG_ERROR, "DEBUG", "End!");
	manager->destroy();
	return EXIT_SUCCESS;
}

JNIEXPORT jint JNICALL Java_fr_enseirb_odroidx_DashManager_read(JNIEnv * env, jobject object, jbyteArray buffer, jint size) {
	return EXIT_SUCCESS;
}

#ifdef __cplusplus
}
#endif
