//
// Created by Mogua.
// Copyright © 2024 Mogua. All rights reserved.
//

#ifndef MOGUA_HELPER_H
#define MOGUA_HELPER_H

#include <unordered_map>
#include <string>

using namespace std;

namespace mogua {
    
    using DataCallback = void (*)(unordered_map<string, string> data);
    using ErrorCallback = void (*)(string error);

    class MoguaHelper {

    public:

        static void getInstallData(DataCallback onData, ErrorCallback onError);

        static void getOpenData(DataCallback onData, ErrorCallback onError);

    };

}

#endif //MOGUA_HELPER_H
