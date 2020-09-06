#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include <spine/spine-cocos2dx.h>

class HelloWorld : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    ~HelloWorld();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
    
    void createSpineTest();
    
    void testSVG();
protected:
    spAtlas* _atlas = nullptr;
    spAttachmentLoader* _attachmentLoader = nullptr;
    spSkeletonData* _skeletonData = nullptr;
    spAnimationStateData* _stateData = nullptr;
};

#endif // __HELLOWORLD_SCENE_H__
