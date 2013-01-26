LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := game_shared

LOCAL_MODULE_FILENAME := libgame

LOCAL_LDLIBS := -llog

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/StartMenu.cpp \
                   ../../Classes/Effect.cpp \
				   ../../Classes/AboutLayer.cpp \
				   ../../Classes/GameScene.cpp \
				   ../../Classes/Ship.cpp \
				   ../../Classes/Bullet.cpp \
				   ../../Classes/Explosion.cpp \
				   ../../Classes/Enemy.cpp \
				   ../../Classes/Global.cpp
                   
LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes                   

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static cocosdenshion_static cocos_extension_static
            
include $(BUILD_SHARED_LIBRARY)

$(call import-module,CocosDenshion/android) \
$(call import-module,cocos2dx) \
$(call import-module,extensions)
