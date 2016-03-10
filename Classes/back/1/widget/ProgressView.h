#ifndef _PROGRESS_VIEW_H_
#define _PROGRESS_VIEW_H_

#include <string>
#include "cocos2d.h"
USING_NS_CC;


/************************************************************************
*   ������                                                                  
************************************************************************/
class ProgressView:public cocos2d::Node
{
public:
	ProgressView();

	CREATE_FUNC(ProgressView);

	void							InitProgress(const char* background,const char* foreground,float currentProgress);	// ��ʼ��������
	float							GetTotalProgress();																																	// ��ȡ�ܵĽ���
	float							GetCurrentProgress();																																// ��ȡ��ǰ����
	void							SetCurrentProgress(float fPersent);																											// ���õ�ǰ����
	Size							GetSize();																																					// ��ȡ�������ĳߴ�
	void							SetTotalProgress(float v);
private:
	Sprite*						m_pProgressBackground;																															// ����������
	Sprite*						m_pProgressForeground;																															// ������ǰ��
	float							m_fTotalProgress;
	float							m_fCurrentProgress;
	float							m_fScale;																																					// �Ŵ���

	std::string					m_strBackground;
	std::string					m_strForeground;
};
#endif