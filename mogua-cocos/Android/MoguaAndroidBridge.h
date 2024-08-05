//
// Created by Mogua.
// Copyright © 2024 Mogua. All rights reserved.
//

#ifndef MOGUA_ANDROID_BRIDGE_H
#define MOGUA_ANDROID_BRIDGE_H

#import "../MoguaHelper.h"

class MoguaAndroidBridge {

public:

    static void getInstallData(mogua::DataCallback onData, mogua::ErrorCallback onError);

    static void getOpenData(mogua::DataCallback onData, mogua::ErrorCallback onError);

};

#endif //MOGUA_ANDROID_BRIDGE_H
