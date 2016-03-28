## cocos2d-x-3.8.1 with imgui

1. [https://github.com/cocos2d/cocos2d-x](https://github.com/cocos2d/cocos2d-x)
2. [https://github.com/ocornut/imgui](https://github.com/ocornut/imgui)


![screen](imguix.png)

## how to integrate imguix

Files:

- Classes/imgui
- Classes/CCIMGUI.h
- Classes/CCIMGUI.cpp
- Classes/IMGUIGLViewImpl.h
- Classes/IMGUIGLViewImpl.cpp
- Classes/ImGuiLayer.h
- Classes/ImGuiLayer.cpp

Create GLView:

```
director->setOpenGLView(IMGUIGLViewImpl::createWithRect("imguix", Rect(0, 0, width, height)));
```