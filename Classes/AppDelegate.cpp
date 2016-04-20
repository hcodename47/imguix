#include "AppDelegate.h"
#include "HelloWorldScene.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
#include "CCIMGUIGLViewImpl.h"
#include "CCImGuiLayer.h"
#include "CCIMGUI.h"

    #ifdef IMGUI_LUA
    #include "imgui/imgui_lua.hpp"
    #endif // IMGUI_LUA

#endif

USING_NS_CC;

#if IMGUI_LUA > 0
static int imgui_lua_test()
{
    static lua_State *L = luaL_newstate();
    luaL_openlibs(L);
    luaopen_imgui(L);

    std::string fn = FileUtils::getInstance()->fullPathForFilename("res/main.lua");
    if (luaL_dofile(L, fn.c_str()))
    {
        CCLOG("%s", lua_tostring(L, -1));
    }

    return 0;
}
#endif // IMGUI_LUA

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate()
{
}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching() {
    int width = 960;
    int height = 640;
    
    // initialize director
    auto director = Director::getInstance();
    auto glview   = director->getOpenGLView();

    if (!glview)
    {
        director->setOpenGLView(IMGUIGLViewImpl::createWithRect("imguix", Rect(0, 0, width, height)));
    }
    
    director->getOpenGLView()->setDesignResolutionSize(width, height, ResolutionPolicy::NO_BORDER);

    // turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0f / 30);

    FileUtils::getInstance()->addSearchPath("res");

    // create a scene. it's an autorelease object
    auto scene = HelloWorld::createScene();
    
    // run
    director->runWithScene(scene);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
    // ImGui is always on the top
    Director::getInstance()->getScheduler()->schedule([](float)
    {
       if (!Director::getInstance()->getRunningScene()->getChildByName("ImGUILayer"))
       {
           Director::getInstance()->getRunningScene()->addChild(ImGuiLayer::create(), INT_MAX, "ImGUILayer");
       }
    }, this, 0, false, "checkImGUI");
#endif

#if IMGUI_LUA > 0
    imgui_lua_test();
#endif // IMGUI_LUA

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
