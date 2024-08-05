# To integrate mogua-cocos into your project, modify the parent CMakeLists.txt file by
# adding the following lines after the add_executable(for Android) or add_library(for iOS) directives.
# This ensures that the mogua-cocos module is properly included and linked to your application target.
#
# add_subdirectory(Classes/mogua-cocos/)
# target_link_libraries(${APP_NAME} mogua-cocos)

set(MOGUA_HEADER)
set(MOGUA_SOURCE)

if(ANDROID)
    list(APPEND MOGUA_HEADER
            MoguaHelper.h
            Android/MoguaAndroidBridge.h
    )
    list(APPEND MOGUA_SOURCE
            MoguaHelper.cpp
            Android/MoguaAndroidBridge.cpp
    )
elseif(IOS)
    list(APPEND MOGUA_HEADER
            MoguaHelper.h
            iOS/MoguaCocos.h
            iOS/MoguaIosBridge.h
    )
    list(APPEND MOGUA_SOURCE
            MoguaHelper.cpp
            iOS/MoguaCocos.mm
            iOS/MoguaIosBridge.cpp
    )
endif()

if(ANDROID)
    add_library(mogua-cocos SHARED ${MOGUA_HEADER} ${MOGUA_SOURCE})
    target_link_libraries(mogua-cocos cocos2d)
elseif(IOS)
    add_library(mogua-cocos ${MOGUA_HEADER} ${MOGUA_SOURCE})
    target_link_libraries(mogua-cocos cocos2d)
    target_link_libraries(mogua-cocos "${CMAKE_CURRENT_SOURCE_DIR}/iOS/SDK/libMoguaSDK.a")
endif()