#include "HelloWorldScene.h"
#include "imgui/CCIMGUI.h"

#include "spine/spine.h"
USING_NS_CC;
using namespace spine;

static bool show_test_window = true;
static bool show_another_window = false;
static ImVec4 clear_color = ImColor(114, 144, 154);

HelloWorld::~HelloWorld()
{
    if (_skeletonData) spSkeletonData_dispose(_skeletonData);
    if (_stateData) spAnimationStateData_dispose(_stateData);
    if (_attachmentLoader) spAttachmentLoader_dispose(_attachmentLoader);
    if (_atlas) spAtlas_dispose(_atlas);
}

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto director = Director::getInstance();
    auto size = director->getWinSize();
    
    auto rootNode = Sprite::create("HelloWorld.png");
    rootNode->setPosition(size.width/2, size.height/2);
    addChild(rootNode);
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = [](Touch* touch, Event*) -> bool {
        CCLOG("touch bg node");
        return true;
    };
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, rootNode);
    
    CCIMGUI::getInstance()->addImGUI([=](){
        // 1. Show a simple window
        // Tip: if we don't call ImGui::Begin()/ImGui::End() the widgets appears in a window automatically called "Debug"
        {
            static float f = 0.0f;
            ImGui::Text("Hello, world!");
            ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
            ImGui::ColorEdit3("clear color", (float*)&clear_color);
            if (ImGui::Button("Test Window")) show_test_window ^= 1;
            if (ImGui::Button("Another Window")) show_another_window ^= 1;
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        }
        
        // 2. Show another simple window, this time using an explicit Begin/End pair
        if (show_another_window)
        {
            ImGui::SetNextWindowSize(ImVec2(200,100), ImGuiCond_FirstUseEver);
            ImGui::Begin("Another Window", &show_another_window);
            
            ImGui::Text("Hello");
            ImGui::End();
        }
        
        // 3. Show the ImGui test window. Most of the sample code is in ImGui::ShowTestWindow()
        if (show_test_window)
        {
            ImGui::SetNextWindowPos(ImVec2(650, 20), ImGuiCond_FirstUseEver);
            ImGui::ShowDemoWindow();
        }
    }, "demoid");
    
    createSpineTest();
    return true;
}

void HelloWorld::createSpineTest()
{
    // Load the texture atlas.
    _atlas = spAtlas_createFromFile("spine/spineboy.atlas", 0);
    CCASSERT(_atlas, "Error reading atlas file.");
    
    // This attachment loader configures attachments with data needed for cocos2d-x rendering.
    // Do not dispose the attachment loader until the skeleton data is disposed!
    _attachmentLoader = (spAttachmentLoader*)Cocos2dAttachmentLoader_create(_atlas);
    
    // Load the skeleton data.
    spSkeletonJson* json = spSkeletonJson_createWithLoader(_attachmentLoader);
    json->scale = 0.6f; // Resizes skeleton data to 60% of the size it was in Spine.
    _skeletonData = spSkeletonJson_readSkeletonDataFile(json, "spine/spineboy-ess.json");
    CCASSERT(_skeletonData, json->error ? json->error : "Error reading skeleton data file.");
    spSkeletonJson_dispose(json);
    
    // Setup mix times.
    _stateData = spAnimationStateData_create(_skeletonData);
    spAnimationStateData_setMixByName(_stateData, "walk", "jump", 0.2f);
    spAnimationStateData_setMixByName(_stateData, "jump", "run", 0.2f);
    
    int xMin = _contentSize.width * 0.10f, xMax = _contentSize.width * 0.90f;
    int yMin = 0, yMax = _contentSize.height * 0.7f;
    for (int i = 0; i < 50; i++) {
        // Each skeleton node shares the same atlas, skeleton data, and mix times.
        SkeletonAnimation* skeletonNode = SkeletonAnimation::createWithData(_skeletonData, false);
        skeletonNode->setAnimationStateData(_stateData);
        
        skeletonNode->setAnimation(0, "walk", true);
        skeletonNode->addAnimation(0, "jump", false, 3);
        skeletonNode->addAnimation(0, "run", true);
        
        skeletonNode->setPosition(Vec2(
                                       RandomHelper::random_int(xMin, xMax),
                                       RandomHelper::random_int(yMin, yMax)
                                       ));
        skeletonNode->setScale(0.8);
        addChild(skeletonNode);
    }
}
