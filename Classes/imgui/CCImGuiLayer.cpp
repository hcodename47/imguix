#include "CCImGuiLayer.h"
#include "imgui.h"
#include "imgui_impl_cocos2dx.h"
#include "CCIMGUI.h"

USING_NS_CC;

void ImGuiLayer::createAndKeepOnTop()
{
    // delay call, once.
    auto director = Director::getInstance();
    director->getScheduler()->schedule([=](float dt)
    {
        std::string layerName = "ImGUILayer";
        auto order = INT_MAX;
        auto layer = ImGuiLayer::create();
        auto runningScene = Director::getInstance()->getRunningScene();
        if (runningScene && !runningScene->getChildByName(layerName))
        {
           runningScene->addChild(layer, INT_MAX, layerName);
        }
        
        auto e = Director::getInstance()->getEventDispatcher();
        layer->detached = false;
        e->addCustomEventListener(Director::EVENT_BEFORE_SET_NEXT_SCENE, [&, layerName](EventCustom*){
            layer = dynamic_cast<ImGuiLayer*>(Director::getInstance()->getRunningScene()->getChildByName(layerName));
            if (layer) {
                layer->retain();
                layer->removeFromParent();
                layer->detached = true;
            }
        });
        e->addCustomEventListener(Director::EVENT_AFTER_SET_NEXT_SCENE, [&, layer, layerName](EventCustom*){
            if (layer && layer->detached) {
                Director::getInstance()->getRunningScene()->addChild(layer, order, layerName);
                layer->release();
                layer->detached = false;
            }
        });
    }, director, 0, 0, 0, false, "checkIMGUI");
}

// on "init" you need to initialize your instance
bool ImGuiLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
	
#if COCOS2D_VERSION < 0x00040000
    // init imgui
    setGLProgram(GLProgramCache::getInstance()->getGLProgram(GLProgram::SHADER_NAME_POSITION_COLOR));
#endif

	// events
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = [](Touch* touch, Event*) -> bool {
        bool inImGuiWidgets = ImGui::IsAnyWindowHovered();
        
        return inImGuiWidgets;
    };
    getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    return true;
}

void ImGuiLayer::visit(cocos2d::Renderer *renderer, const cocos2d::Mat4 &parentTransform, uint32_t parentFlags)
{
    Layer::visit(renderer, parentTransform, parentFlags);
    _command.init(_globalZOrder);
    _command.func = CC_CALLBACK_0(ImGuiLayer::onDraw, this);
    Director::getInstance()->getRenderer()->addCommand(&_command);
}

void ImGuiLayer::onDraw()
{
#if COCOS2D_VERSION < 0x00040000
    getGLProgram()->use();
#endif

    // create frame
    ImGui_ImplCocos2dx_NewFrame();
    
    // draw all gui
    CCIMGUI::getInstance()->updateImGUI();
    
#if COCOS2D_VERSION < 0x00040000
    // rendering
    glUseProgram(0);
#endif
    
    ImGui::Render();
    
    ImGui_ImplCocos2dx_RenderDrawData(ImGui::GetDrawData());
}
