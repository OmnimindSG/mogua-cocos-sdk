//
// Created by Mogua.
// Copyright © 2024 Mogua. All rights reserved.
//

#include "MoguaIosBridge.h"

using namespace mogua;

static DataCallback installOnData = nullptr;
static ErrorCallback installOnError = nullptr;
static DataCallback openOnData = nullptr;
static ErrorCallback openOnError = nullptr;

static unordered_map<string, string> pendingInstallData = {};
static string pendingInstallError = "";
static unordered_map<string, string> pendingOpenData = {};
static string pendingOpenError = "";

void MoguaIosBridge::getInstallData(DataCallback onData, ErrorCallback onError) {
    installOnData = onData;
    installOnError = onError;
    if (!pendingInstallData.empty()) {
        installOnData(pendingInstallData);
        pendingInstallData.clear();
    }
    if (!pendingInstallError.empty()) {
        installOnError(pendingInstallError);
        pendingInstallError.clear();
    }
}

void MoguaIosBridge::getOpenData(DataCallback onData, ErrorCallback onError) {
    openOnData = onData;
    openOnError = onError;
    if (!pendingOpenData.empty()) {
        openOnData(pendingOpenData);
        pendingOpenData.clear();
    }
    if (!pendingOpenError.empty()) {
        openOnError(pendingOpenError);
        pendingOpenError.clear();
    }
}

void MoguaIosBridge::oniInstallOnData(unordered_map<string, string> data) {
    if (installOnData == nullptr) {
        pendingInstallData = data;
        return;
    }
    installOnData(data);
}

void MoguaIosBridge::oniInstallOnError(string error) {
    if (installOnError == nullptr) {
        pendingInstallError = error;
        return;
    }
    installOnError(error);
}

void MoguaIosBridge::oniOpenOnData(unordered_map<string, string> data) {
    if (openOnData == nullptr) {
        pendingOpenData = data;
        return;
    }
    openOnData(data);
}

void MoguaIosBridge::oniOpenOnError(string error) {
    if (openOnError == nullptr) {
        pendingOpenError = error;
        return;
    }
    openOnError(error);
}



