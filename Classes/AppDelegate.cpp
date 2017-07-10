#include "AppDelegate.h"
#include "Menu.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

void AppDelegate::initGLContextAttrs()
{
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching() {
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLViewImpl::create("Nope 50");
		glview->setFrameSize(1280, 720);
        director->setOpenGLView(glview);
    }
    director->setDisplayStats(false);

	glview->setDesignResolutionSize(1280, 720, ResolutionPolicy::FIXED_WIDTH);

    director->setAnimationInterval(1.0 / 60);

    auto scene = MenuScene::createScene();

    director->runWithScene(scene);

    return true;
}

void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

}
