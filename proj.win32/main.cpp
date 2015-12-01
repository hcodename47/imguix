#include "main.h"
#include "AppDelegate.h"
#include "cocos2d.h"
#include "IMGUIGLViewImpl.h"

USING_NS_CC;

#if _MSC_VER > 1800
#pragma comment(lib,"libcocos2d_2015.lib")
#pragma comment(lib,"libbox2d_2015.lib")
#pragma comment(lib,"libSpine_2015.lib")
#pragma comment(lib,"librecast_2015.lib")
#pragma comment(lib,"libbullet_2015.lib")
#else
#pragma comment(lib,"libcocos2d_2013.lib")
#pragma comment(lib,"libbox2d_2013.lib")
#pragma comment(lib,"libSpine_2013.lib")
#pragma comment(lib,"librecast_2013.lib")
#pragma comment(lib,"libbullet_2013.lib")
#endif

int APIENTRY _tWinMain(HINSTANCE hInstance,
                       HINSTANCE hPrevInstance,
                       LPTSTR    lpCmdLine,
                       int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    auto director = Director::getInstance();
    IMGUIGLViewImpl *glview = IMGUIGLViewImpl::createWithRect("imguix", Rect(0, 0, 960, 640));
    director->setOpenGLView(glview);

    // create the application instance
    AppDelegate app;
    return Application::getInstance()->run();
}
