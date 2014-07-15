#include "cocos2d.h"
#include "GameControl.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "../../../../cocos2dx/platform/android/jni/JniHelper.h"
#include <jni.h>
//#include "jniLoad.h"
using namespace cocos2d;

#define  LOG_TAG    "JniNative"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)

extern "C" {
	//rank:排名  score:最高分
	JNIEXPORT jint JNICALL Java_com_eebbk_turbosnail_TurboSnail_setRank(JNIEnv *env, jobject obj,int rank,int score)
    {
    	LOGD(" rank ==================== %d",rank);
    	LOGD(" score ==================== %d",score);

		g_Control.m_nRank = rank;
		g_Control.m_nTotalScore = score;

    	return 0;
    }
}

#endif
