#include "EquipmentManager.h"
#include "scene/BaseScene.h"
#include "SceneManager.h"
#include "PathManager.h"
#include "Controller.h"
#include "Equipment.h"
#include "SkillManager.h"
#include "Config.h"
#include "PlayerManager.h"
#include "MonsterLogic.h"
#include "PlayerLogic.h"

RPG_01_BEGIN
EquipmentManager* EquipmentManager::m_pInstance = 0;

EquipmentManager* EquipmentManager::GetInstance()
{
	if (m_pInstance == 0)
	{
		m_pInstance = new EquipmentManager;
	}

	return m_pInstance;
}

/************************************************************************
*  装备管理器的处理主逻辑
************************************************************************/
void EquipmentManager::Process(float delt)
{
	static float fDelt = 0;
	fDelt += delt;
	if (fDelt >= Game()->GetConfig()->GetProcessInterval() )
	{
		// 掉下血瓶
		DropoutBloodVial();

		// 掉下魔法瓶
		DropoutMagicVial();

		fDelt = 0;
	}

	// 碰撞检测
	CheckCollision();
}

/************************************************************************
*  随机掉下血瓶
************************************************************************/
void	EquipmentManager::DropoutBloodVial()
{
	if (!Game()->IsRunning())
	{
		return;
	}

	if (m_nBloodVial >= Game()->GetConfig()->GetEquipmentBloodMaxCount())
	{
		for (int i = 0; i < m_EquipmentList.size(); ++i)
		{
			BloodEquipment* bloodEqp =  dynamic_cast<BloodEquipment*>(m_EquipmentList[i]);

			if (bloodEqp == 0)
			{
				continue;
			}

			if (bloodEqp->isVisible() == false)
			{
				bloodEqp->setPosition(Game()->GetPathManager()->GetRandomPoint());
				bloodEqp->setVisible(true);
				break;
			}
		}
		return;
	}


	//=================
	BloodEquipment* bloodEqp = BloodEquipment::create();

	Layer* pScene = Game()->GetSceneManager()->GetCurrentScene()->GetEntityLayer();

	Point point = Game()->GetPathManager()->GetRandomPoint();

	bloodEqp->setPosition(point);

	pScene->addChild(bloodEqp);

	++m_nBloodVial;

	m_EquipmentList.push_back(bloodEqp);
}

/************************************************************************
*  随机掉下魔瓶
************************************************************************/
void	EquipmentManager::DropoutMagicVial()
{
	if (!Game()->IsRunning())
	{
		return;
	}

	if (m_nMagicVial >= Game()->GetConfig()->GetEquipmentMagicMaxCount())
	{
		for (int i = 0; i < m_EquipmentList.size(); ++i)
		{
			MagicEquipment* magicEqp =  dynamic_cast<MagicEquipment*>(m_EquipmentList[i]);
			if (magicEqp == 0)
			{
				continue;
			}

			if (magicEqp->isVisible() == false)
			{
				magicEqp->setPosition(Game()->GetPathManager()->GetRandomPoint());
				magicEqp->setVisible(true);
				break;
			}
		}
		return;
	}

	//=================
	MagicEquipment* magicEqp = MagicEquipment::create();

	Layer* pScene = Game()->GetSceneManager()->GetCurrentScene()->GetEntityLayer();

	Point point = Game()->GetPathManager()->GetRandomPoint();

	magicEqp->setPosition(point);

	pScene->addChild(magicEqp);

	++m_nMagicVial;

	m_EquipmentList.push_back(magicEqp);
}

/************************************************************************
*  移除所有装备
************************************************************************/
void EquipmentManager::RemoveAllEquipment()
{
	m_nMagicVial = 0;
	m_nBloodVial = 0;
	m_EquipmentList.clear();
}

/************************************************************************
*  碰撞检测
************************************************************************/
void EquipmentManager::CheckCollision()
{
	if (!Game()->IsRunning())
	{
		return;
	}

	for (int i = 0; i < m_EquipmentList.size(); ++i)
	{
		Equipment* eqp = m_EquipmentList[i];
		if (eqp == 0 || eqp->isVisible() == false)
		{
			continue;
		}

		Rect scope = eqp->GetScope();

		vector<Player*> playerList = Game()->GetPlayerManager()->GetPlayerList();

		for (int i = 0; i < playerList.size(); ++i)
		{
			Player* player = playerList[i];

			Point point = player->getPosition();
			if (!Game()->GetPathManager()->IsInRect(scope,point) || eqp->isVisible() == false)
			{
				continue;
			}

			if (eqp->GetEquipmentType() == EQUIPMENT_BLOOD)
			{
				BloodEquipment* bloodEqp =  0;
				bloodEqp = dynamic_cast<BloodEquipment*>(eqp);
				if (bloodEqp == 0)
				{
					continue;
				}
				Game()->GetPlayerLogic()->HandlePlayerBloodChange(player,bloodEqp->GetReturnBlood());
				player->ShowBloodReturnAnimation();
				Game()->GetSkillManager()->ShowBloodDropAnimation(player,bloodEqp->GetReturnBlood());
			}
			else if (eqp->GetEquipmentType() == EQUIPMENT_MAGIC)
			{
				MagicEquipment* magicEqp =  0;
				magicEqp = dynamic_cast<MagicEquipment*>(eqp);
				if (magicEqp == 0)
				{
					continue;
				}
				Game()->GetPlayerLogic()->HandlePlayerMagicChange(player,magicEqp->GetReturnMagic());
			}
			else
			{
				continue;
			}

			eqp->setVisible(false);
		}
		
	}
}

void EquipmentManager::TestAnimation()
{
	Animation*								m_pStaticRightAnimation;
	Animation*								m_pStaticDownAnimation;
	Animation*								m_pStaticLeftAnimation;
	Animation*								m_pStaticUpAnimation;

	auto strings = FileUtils::getInstance()->getValueMapFromFile("config/weapon-action.xml"); 
	auto monster = strings["weapon2"].asValueMap();
	auto dict = monster["static"].asValueMap();

	string filename =  dict["filename"].asString();
	string strPicName = dict["picturename"].asString();
	int action = dict["action"].asInt();

	string file_plist = filename + ".plist";
	string file_png = filename + ".png";

	SpriteFrameCache* frameCache = SpriteFrameCache::getInstance();

	frameCache->addSpriteFramesWithFile(file_plist,file_png);

	SpriteFrame* frame = NULL;
	Vector<SpriteFrame*> frameList;

	int direction = 0;

	for (direction = 1;direction <= 4; ++direction)
	{
		frameList.clear();
		for (int i = 0; i < 10;++i)
		{
			string tmp = StringUtils::format("_%d_%d_0%d.png",action,direction,i);;
			string path = strPicName + tmp;
			frame = frameCache->getSpriteFrameByName((path));

			frameList.pushBack(frame);
		}

		for (int i = 10; i < 16;++i)
		{
			string tmp = StringUtils::format("_%d_%d_%d.png",action,direction,i);;
			string path = strPicName + tmp;
			frame = frameCache->getSpriteFrameByName((path));

			frameList.pushBack(frame);
		}

		Animation* pTempAnimation = 0;

		m_pStaticRightAnimation = Animation::createWithSpriteFrames(frameList);
		pTempAnimation = m_pStaticRightAnimation;
		/*if (m_DirectionMap[direction] == right_up_direction)
		{
		m_pWalkRightAnimation  = Animation::createWithSpriteFrames(frameList);
		pTempAnimation = m_pWalkRightAnimation;
		}

		if (m_DirectionMap[direction] == right_direction)
		{
		m_pWalkDownAnimation  = Animation::createWithSpriteFrames(frameList);
		pTempAnimation = m_pWalkDownAnimation;
		}

		if (m_DirectionMap[direction] == right_down_direction)
		{
		m_pWalkLeftAnimation  = Animation::createWithSpriteFrames(frameList);
		pTempAnimation = m_pWalkLeftAnimation;
		}

		if (m_DirectionMap[direction] == down_direction)
		{
		m_pWalkUpAnimation  = Animation::createWithSpriteFrames(frameList);
		pTempAnimation = m_pWalkUpAnimation;
		}*/
		pTempAnimation->setLoops(-1);
		pTempAnimation->setDelayPerUnit(0.1);

		auto seq = Sequence::create(Animate::create(pTempAnimation),NULL);
		auto sp = Sprite::create();
		sp->setPosition(Point(200,100));
		Game()->GetSceneManager()->GetCurrentScene()->GetEntityLayer()->addChild(sp);
		sp->runAction(seq);
	}
}
RPG_01_END

