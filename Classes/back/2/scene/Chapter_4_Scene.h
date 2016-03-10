#ifndef _CHAPTER_4_SCENE_H_
#define _CHAPTER_4_SCENE_H_

#include "cocos2d.h"
USING_NS_CC;
using namespace cocos2d::ui;

#define _USE_PC_

#include "Player.h"
#include "BaseScene.h"

class Controller;
class HRocker;

RPG_01_BEGIN

class Chapter_4_Scene:public BaseScene
{
public: 
	Chapter_4_Scene();

	virtual ~Chapter_4_Scene();

	CREATE_FUNC(Chapter_4_Scene);

	static cocos2d::Scene* createScene();

	virtual bool					init();

	void								LoadBackground();


private:

	void								update(float delta);


};
RPG_01_END



#endif //_CHAPTER_2_SCENE_H_