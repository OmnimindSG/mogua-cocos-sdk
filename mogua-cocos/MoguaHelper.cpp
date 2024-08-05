//
// Created by Mogua.
// Copyright © 2024 Mogua. All rights reserved.
//

#include "MoguaHelper.h"
#include "cocos2d.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "Android/MoguaAndroidBridge.h"
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "iOS/MoguaIosBridge.h"
#endif

using namespace mogua;

void MoguaHelper::getInstallData(DataCallback onData, ErrorCallback onError) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    MoguaAndroidBridge::getInstallData(onData, onError);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    MoguaIosBridge::getInstallData(onData, onError);
#endif
}

void MoguaHelper::getOpenData(DataCallback onData, ErrorCallback onError) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    MoguaAndroidBridge::getOpenData(onData, onError);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    MoguaIosBridge::getOpenData(onData, onError);
#endif
}