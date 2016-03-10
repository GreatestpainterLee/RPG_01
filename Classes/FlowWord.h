
#ifndef _FLOW_WORD_H_
#define _FLOW_WORD_H_

#include "cocos2d.h"
#include "cocos-ext.h"
//#include "cocos2d\external\Json\rapidjson.h"

using namespace cocos2d;
using namespace extension;


class FlowWord : public CCNode {
public:
	static FlowWord* create();
	bool init();

public:
	void showWord(const char* text, CCPoint pos);
private:
	CCLabelTTF* m_textLab;

	void flowEnd();
};





#endif // !_FLOW_WORD_H_
