#include "Utils.h"

Utils*Utils::instance = NULL;
 Utils* Utils::getInstance()
 {
	 if (NULL == instance)
	 {
	 
		 instance = new Utils();
		 
	}
		return instance;
}
 cocos2d::ui::Widget* Utils::getUI()
 {
	
	 return UI;
	 

 }
string Utils::int2string(int num)
{
	stringstream ss;

	string result;

	ss << num;

	ss >> result;

	return result;
}

string Utils::int2string2(int num)
{
	char tmp[50] = { 0 };

	sprintf(tmp, "%d", num);

	string result = tmp;

	return result;
}

cocos2d::ui::Widget* Utils::getStartUI()
{
	return startUI;

}

cocos2d::ui::Widget* Utils::getChooseGeneralUI()
{
	return chooseGeneralUI;

}

cocos2d::ui::Widget* Utils::getConnectToServerUI()
{
	return connectToServerUI;
}

cocos2d::ui::Widget* Utils::getCreateOrJoinRoomUI()
{
	return createOrJoinRoomUI;
}


void Utils::reloadUI()
{
	UI = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("PlayScene/PlayScene.ExportJson"); 
	startUI = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("StartScene/StartScene_1.ExportJson");
	connectToServerUI = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("Connect2Server/Connect2Server.ExportJson");
	chooseGeneralUI = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("ChooseGeneral/ChooseGeneral.ExportJson");
	createOrJoinRoomUI = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("CreateOrJoinRoom/CreateOrJoinRoom.ExportJson");
}