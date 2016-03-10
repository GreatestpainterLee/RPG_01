#ifndef _UTILS_H_
#define _UTILS_H_

#include "cocos2d.h"
#include <string>
#include <sstream>
#include "editor-support\cocostudio\CCSGUIReader.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
using namespace std;
using namespace cocostudio;
//所有包的枚举类
enum PackageName
{
	BASICCARD, BASICGENERAL, BASICEQUIPMENT
};
enum Role
{
	FANZEI, ZHUGONG, ZHONGCHEN, NEIJIAN
};

enum JudgingState
{
	LEBUSISHU, LIGHTING, BINGLIANGCUNDUAN
};

enum Phase
{
	RoundStart, Start, Judge, Draw, Play, Discard, Finish, NotActive, PhaseNone
};

enum SEAT
{
	INVALID_SEAT = -1,ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT
};
class Utils
{
private:
	Utils(){ 
		reloadUI();
	};
	static Utils*instance;
public:
	static Utils*getInstance();

	void	reloadUI();

	string int2string(int);

	string int2string2(int);

	cocos2d::ui::Widget* getUI();
	
	cocos2d::ui::Widget* getStartUI();

	cocos2d::ui::Widget* getConnectToServerUI();

	cocos2d::ui::Widget* getChooseGeneralUI();

	cocos2d::ui::Widget* getCreateOrJoinRoomUI();

	cocos2d::ui::Widget* UI;
	
	cocos2d::ui::Widget* startUI;

	cocos2d::ui::Widget* connectToServerUI;

	cocos2d::ui::Widget* chooseGeneralUI;

	cocos2d::ui::Widget* createOrJoinRoomUI;
};
#endif