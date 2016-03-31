## cocos2d-x-3.8.1 with imgui

1. [https://github.com/cocos2d/cocos2d-x](https://github.com/cocos2d/cocos2d-x)
2. [https://github.com/ocornut/imgui](https://github.com/ocornut/imgui)


![screen](imguix.png)

## how to integrate imguix

- all you need are `Classes/imgui` folder

- create GLView:

  ```
  director->setOpenGLView(IMGUIGLViewImpl::createWithRect("imguix", Rect(0, 0, width,   height)));
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
