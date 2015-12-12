/*
 * AdmobHelper.cpp
 *
 *  Created on: Dec 8, 2015
 *      Author: banh
 */

#include "AdmobHelper.h"
#include "cocos2d.h"


bool AdmobHelper::isBannerAdShowing = true;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

#include "platform/android/jni/JniHelper.h"
#include <jni.h>
//#include <android/log.h>


const char* AppActivityClassName = "org/cocos2dx/cpp/AppActivity";

void AdmobHelper::hideAd()
{
    cocos2d::JniMethodInfo t;
    if (cocos2d::JniHelper::getStaticMethodInfo(t, AppActivityClassName, "hideAd", "()V"))
    {

        t.env->CallStaticVoidMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
        isBannerAdShowing = false;
    }
}



void AdmobHelper::showAd()
{

    cocos2d::JniMethodInfo t;
    if (cocos2d::JniHelper::getStaticMethodInfo(t, AppActivityClassName, "showAd", "()V"))
    {

        t.env->CallStaticVoidMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
        isBannerAdShowing = true;
    }

}

void AdmobHelper::showInterstitial()
{
//	CCLOG(" Android : showInterstitial() called");
	cocos2d::JniMethodInfo t;
	if (cocos2d::JniHelper::getStaticMethodInfo(t, AppActivityClassName, "showInterstitial", "()V"))
	{
		t.env->CallStaticVoidMethod(t.classID, t.methodID);
		t.env->DeleteLocalRef(t.classID);
	}
}

#else


void AdmobHelper::hideAd()
{
    CCLOG("hideAd() called");
    isBannerAdShowing = false;
    return; //nothing
}


void AdmobHelper::showAd()
{
    CCLOG("showAd() called");
    isBannerAdShowing = true;
    return; //nothing;

}

void AdmobHelper::showInterstitial()
{
	CCLOG("showInterAd() called");

	return; //nothing;
}

#endif

