//
// Created by Mogua.
// Copyright © 2024 Mogua. All rights reserved.
//

#include "MoguaCocosCallback.h"
#include "MoguaIosBridge.h"

@implementation MoguaCocosInstallCallback

unordered_map<string, string> objcMap2cppMap(NSDictionary<NSString *, id> * _Nonnull map) {
    unordered_map<string, string> umap;
    for (NSString *key in map.allKeys) {
        NSString *value = [[map objectForKey: key] description];
        string keyStr = string([key UTF8String]);
        string valueStr = string([value UTF8String]);
        umap[keyStr] = valueStr;
    }
    return umap;
}

- (instancetype)init
{
    self = [super initWithOnData:^(NSDictionary<NSString *,id> * _Nonnull data) {
        unordered_map<string, string> umap = objcMap2cppMap(data);
        MoguaIosBridge::oniInstallOnData(umap);
    } onError:^(NSError * _Nonnull error) {
        string errStr = string([error.description UTF8String]);
        MoguaIosBridge::oniInstallOnError(errStr);
    }];
    return self;
}

@end

@implementation MoguaCocosOpenCallback

- (instancetype)init
{
    self = [super initWithOnData:^(NSDictionary<NSString *,id> * _Nonnull data) {
        unordered_map<string, string> umap = objcMap2cppMap(data);
        MoguaIosBridge::oniOpenOnData(umap);
    } onError:^(NSError * _Nonnull error) {
        string errStr = string([error.description UTF8String]);
        MoguaIosBridge::oniOpenOnError(errStr);
    }];
    return self;
}

@end
