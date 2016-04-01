## cocos2d-x-3.8.1 with imgui

1. [https://github.com/cocos2d/cocos2d-x](https://github.com/cocos2d/cocos2d-x)
2. [https://github.com/ocornut/imgui](https://github.com/ocornut/imgui)


![screen](imguix.png)

## how to integrate imguix

- all you need are `Classes/imgui` folder

- create GLView:


  ```
  // include headers
  #if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
  #include "CCIMGUIGLViewImpl.h"
  #include "CCImGuiLayer.h"
  #endif
  ```

  ```
  // create glview
  director->setOpenGLView(IMGUIGLViewImpl::createWithRect("imguix", Rect(0, 0, width,   height)));
  ```

  ```
  // add imgui layer on the top
  #if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
      // ImGui is always on the top
      Director::getInstance()->getScheduler()->schedule([](float)
      {
         if (!Director::getInstance()->getRunningScene()->getChildByName("ImGUILayer"))
         {
             Director::getInstance()->getRunningScene()->addChild(ImGuiLayer::create(), INT_MAX,   "ImGUILayer");
         }
      }, this, 0, false, "checkImGUI");
  #endif
  ```

## how to use

   ```
   // add ui
   CCIMGUI::getInstance()->addImGUI([=](){
       {
           ImGui::Text("Hello, world!");
       }
   }, "demoid");

   // remove ui
   CCIMGUI::getInstance()->removeImGUI("demoid");
   ```
