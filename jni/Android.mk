LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   Classes/GameControl.cpp\
                   Classes/AppDelegate.cpp\
                   Classes/AnimationUtils.cpp\
                   Classes/ActionSprite.cpp\
                   Classes/CMImage.cpp\
                   Classes/GameLayer.cpp\
                   Classes/GameScene.cpp\
                   Classes/Hero.cpp\
                   Classes/HudLayer.cpp\
                   Classes/Monster.cpp\
                   Classes/StringUtils.cpp\
                   Classes/PopupLayer.cpp\
                   Classes/MarketScene.cpp\
                   Classes/StartScene.cpp\
                   Classes/ScoreScene.cpp\
                   Classes/CSVReader.cpp\
                   Classes/HelpScene.cpp\
                   Classes/JniNative.cpp\
                   Classes/DataControl.cpp
                   
LOCAL_C_INCLUDES := $(LOCAL_PATH)/Classes \
										$(LOCAL_PATH)/Classes/UtilityFunction \
										$(LOCAL_PATH)/Classes/data \
										$(LOCAL_PATH)/Classes/DefendWar \
									  	$(LOCAL_PATH)/external/sqlite3/include \
									    $(LOCAL_PATH)/cocos2dx/platform/android \
										$(LOCAL_PATH)/cocos2dx/platform/android/jni \
										$(LOCAL_PATH)/cocos2dx \
										$(LOCAL_PATH)/cocos2dx/actions \
										$(LOCAL_PATH)/cocos2dx/base_nodes \
										$(LOCAL_PATH)/cocos2dx/cocoa \
										$(LOCAL_PATH)/cocos2dx/draw_nodes \
										$(LOCAL_PATH)/cocos2dx/effects \
										$(LOCAL_PATH)/cocos2dx/include \
										$(LOCAL_PATH)/cocos2dx/kazmath/include \
										$(LOCAL_PATH)/cocos2dx/keypad_dispatcher \
										$(LOCAL_PATH)/cocos2dx/label_nodes \
										$(LOCAL_PATH)/cocos2dx/layers_scenes_transitions_nodes \
										$(LOCAL_PATH)/cocos2dx/menu_nodes \
										$(LOCAL_PATH)/cocos2dx/misc_nodes \
										$(LOCAL_PATH)/cocos2dx/particle_nodes \
										$(LOCAL_PATH)/cocos2dx/platform \
										$(LOCAL_PATH)/cocos2dx/platform/android \
										$(LOCAL_PATH)/cocos2dx/script_support \
										$(LOCAL_PATH)/cocos2dx/shaders \
										$(LOCAL_PATH)/cocos2dx/sprite_nodes \
										$(LOCAL_PATH)/cocos2dx/support \
										$(LOCAL_PATH)/cocos2dx/text_input_node \
										$(LOCAL_PATH)/cocos2dx/textures \
										$(LOCAL_PATH)/cocos2dx/tilemap_parallax_nodes \
										$(LOCAL_PATH)/cocos2dx/touch_dispatcher \
										$(LOCAL_PATH)/CocosDenshion \
										$(LOCAL_PATH)/CocosDenshion/android \
										$(LOCAL_PATH)/CocosDenshion/blackberry \
										$(LOCAL_PATH)/CocosDenshion/emscripten \
										$(LOCAL_PATH)/CocosDenshion/include \
										$(LOCAL_PATH)/CocosDenshion/marmalade \
										$(LOCAL_PATH)/CocosDenshion/third_party \
										$(LOCAL_PATH)/CocosDenshion/tizen \
										$(LOCAL_PATH)/extensions \
										$(LOCAL_PATH)/extensions/AssetsManager \
										$(LOCAL_PATH)/extensions/CCBReader \
										$(LOCAL_PATH)/extensions/CocoStudio \
										$(LOCAL_PATH)/extensions/GUI \
										$(LOCAL_PATH)/extensions/LocalStorage \
										$(LOCAL_PATH)/extensions/network \
										$(LOCAL_PATH)/extensions/physics_nodes \
										$(LOCAL_PATH)/extensions/spine \
										$(LOCAL_PATH)/CocosDenshion/ \
										$(LOCAL_PATH)/external \
										$(LOCAL_PATH)/external/Box2D \
										$(LOCAL_PATH)/external/Box2D/Collision \
										$(LOCAL_PATH)/external/Box2D/Collision/Shapes \
										$(LOCAL_PATH)/external/Box2D/Common \
										$(LOCAL_PATH)/external/Box2D/Dynamics \
										$(LOCAL_PATH)/external/Box2D/Rope \
										$(LOCAL_PATH)/external/chipmunk/include \
										$(LOCAL_PATH)/external/emscripten/system/include/GL \
										$(LOCAL_PATH)/external/emscripten/system/include/SDL \
										$(LOCAL_PATH)/external/emscripten/system/include/GLES2 \
										$(LOCAL_PATH)/external/emscripten/system/include/GLES \
										$(LOCAL_PATH)/external/libwebsockets \
										$(LOCAL_PATH)/external/sqlite3 \
										$(LOCAL_PATH)/scripting \
										$(LOCAL_PATH)/scripting/javascript \
										$(LOCAL_PATH)/scripting/lua \
										
LOCAL_LDLIBS:=-L$(SYSROOT)/usr/lib -llog -lGLESv2 $(LOCAL_PATH)/libbbkcocos2d.so
include $(BUILD_SHARED_LIBRARY)