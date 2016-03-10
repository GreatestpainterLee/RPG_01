#include "ProgressView.h"

ProgressView::ProgressView()
{
	m_pProgressBackground = 0;
	m_pProgressForeground = 0;
	m_fTotalProgress = 1.0;
	m_fCurrentProgress = 0.0;
	m_fScale = 1.0;
}

void ProgressView::InitProgress(const char* background,const char* foreground,float currentProgress)
{
	m_strBackground = background;
	m_strForeground = foreground;
	
	m_fCurrentProgress = currentProgress;

	SetTotalProgress(1.0);
}

void ProgressView::SetTotalProgress(float v)
{
	m_pProgressBackground = Sprite::create(m_strBackground);

	m_pProgressForeground = Sprite::create(m_strForeground);
	m_pProgressForeground->setAnchorPoint(Point(0,0.5));
	m_pProgressForeground->setPosition(Point(-m_pProgressForeground->getContentSize().width * 0.5f, 0));

	m_fTotalProgress = v;

	m_fScale = m_pProgressForeground->getContentSize().width / (m_fTotalProgress*100);

	this->addChild(m_pProgressBackground);
	this->addChild(m_pProgressForeground);
}

float ProgressView::GetCurrentProgress()
{
	return m_fCurrentProgress;
}

float ProgressView::GetTotalProgress()
{
	return m_fTotalProgress;
}

void ProgressView::SetCurrentProgress(float fPersent)
{
	if (fPersent < 0.0)
	{
		fPersent = 0;
	}

	if (fPersent > 1.0)
	{
		fPersent = 1.0;
	}


	m_fCurrentProgress = fPersent;

	float width = (fPersent*100) * m_fScale;

	Point from = m_pProgressForeground->getTextureRect().origin;
	Rect rect = CCRectMake(from.x,from.y,width,m_pProgressForeground->getContentSize().height);
	m_pProgressForeground->setTextureRect(rect);
}

Size ProgressView::GetSize()
{
	return m_pProgressBackground->getContentSize();
}