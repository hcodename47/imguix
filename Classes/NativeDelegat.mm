//
//  NativeDelegat.cpp
//  imguix
//
//  Created by z on 11/14/15.
//
//

#include <cocos2d.h>

USING_NS_CC;

void setWindowResizable()
{
    id window = Director::getInstance()->getOpenGLView()->getCocoaWindow();
    [window setStyleMask:[window styleMask] | NSResizableWindowMask];
}
