//
// Created by Mogua.
// Copyright © 2024 Mogua. All rights reserved.
//

#ifndef MOGUA_IOS_BRIDGE_H
#define MOGUA_IOS_BRIDGE_H

#include "../MoguaHelper.h"

class MoguaIosBridge {

public:

    static void getInstallData(mogua::DataCallback _Nonnull onData, mogua::ErrorCallback _Nonnull onError);
    
    static void getOpenData(mogua::DataCallback _Nonnull onData, mogua::ErrorCallback _Nonnull onError);
    
    static void oniInstallOnData(unordered_map<string, string> data);
    
    static void oniInstallOnError(string error);

    static void oniOpenOnData(unordered_map<string, string> data);
    
    static void oniOpenOnError(string error);

};

#endif //MOGUA_IOS_BRIDGE_H
