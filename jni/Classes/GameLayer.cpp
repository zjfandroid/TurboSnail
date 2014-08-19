#include "GameControl.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "../../../../cocos2dx/platform/android/jni/JniHelper.h"
#include <jni.h>
#endif

GameLayer::GameLayer():
gameLevel(1),
timeMax(60),
timeRemain(60),
isShowAnswerAfterWrong(false)
{
}

GameLayer::~GameLayer()
{
}

bool GameLayer::init()
{
	bool isInit = false;
	do 
	{
		CC_BREAK_IF(!CCLayer::init());
		g_Control.playBGMusic(s_musicBgGame);

		initTitle();
		this->initHero();
		this->setTouchEnabled(true);

		countDown(0);
		dataControl = g_Control.dataControl;

		monsters = CCArray::createWithCapacity(4);
		monsters->retain();
		isInit = true;

		g_Control.playEffect(s_effectCountDown);
		g_Control.gameState = GRS_UNKNOWN;
	} while (0);

	return isInit; 
}

void GameLayer::initHero()
{
	_hero = Hero::create();
	this->addChild(_hero, ORDER_HERO);
	_hero->idle();
}

void GameLayer::initMonster()
{
	set<int> types;
	monsters->removeAllObjects();

	unsigned int size = dataControl->options.size();
	while (types.size() < size)
	{
		int r = random_range(0, 7);
		types.insert(r);
	}

	int i = 0;
	for (set<int>::iterator it = types.begin(); it != types.end(); it++)
	{
		Monster *_monster = Monster::create();
		_monster->setText(dataControl->options[i]);
		if (i == dataControl->getRightOption())
		{
			_monster->setRightAns(true);
			_monster->setTag(TAG_RIGHT_ANS);
		}
		else
		{
			_monster->setRightAns(false);
			_monster->setTag(TAG_WRONG_ANS);
		}

		_monster->setMonsterType(*it);
		_monster->setPosition(ccp(1380 + i * 178, 300));
		monsters->addObject(_monster);
		_monster->idle();
		this->addChild(_monster, ORDER_MONSTER);
		i++;
	}
}

bool GameLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	if (g_Control.gameState != GRS_PLAY)
	{
		return false;
	}
	return true;
}

void GameLayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	if (g_Control.gameState != GRS_PLAY)
	{
		return;
	}

	isAnsRight = false;
	CCObject *pObj;
	CCARRAY_FOREACH(monsters, pObj)
	{
		Monster *_monster = (Monster *)pObj;
		if (_monster->isVisible())
		{
			//点了字
			CCPoint labelTouchPoint = _monster->convertTouchToNodeSpace(pTouch);
			CCRect sPointLabel = getRect(_monster->getOption());
			//点了怪物
			CCPoint touchPoint = convertTouchToNodeSpace(pTouch);
			CCRect sPoint = getRect(_monster);
	
			if (sPointLabel.containsPoint(labelTouchPoint) || sPoint.containsPoint(touchPoint))
			{
				g_Control.gameState = GRS_TOUCH_OVER;
				g_Control.playEffect(s_effectAnswer);
				setSpeedGain(_hero->getSpeedLevel());
				
				if (_monster->getRightAns())
				{
					isAnsRight = true;
					timeRemain = clampf(timeRemain + 8, 0, timeMax);
				}

				CCARRAY_FOREACH(monsters, pObj)
				{
					Monster *_mon = (Monster *)pObj;
					_mon->hideOption();
					if (isAnsRight)
					{
						_mon->changeToTomato();
					}
					else
					{
						showRightAnsCard();

						_mon->defy();
					}
				}

				break;
			}
		}
	}
}

cocos2d::CCRect GameLayer::getRect(CCNode* pNode)
{
	CCRect rc;
	rc.origin = pNode->getPosition();
	rc.size = pNode->getContentSize();
	rc.origin.x -= rc.size.width * 0.5;
	rc.origin.y	-= rc.size.height * 0.5;
	return rc;
}

void GameLayer::registerWithTouchDispatcher()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority, true);
}

void GameLayer::initProgress()
{
	//进度背景
	CCSprite *sprite = CCSprite::create(s_pPathProgressEmpy);
	sprite->setPosition(s_pPointProgress);
	addChild(sprite);

	speedProgress = CCProgressTimer::create(CCSprite::create(s_pPathProgressFull));
	speedProgress->setType(kCCProgressTimerTypeBar);
	//    Setup for a bar starting from the left since the midpoint is 0 for the x
	speedProgress->setMidpoint(ccp(0, 0));
	//    Setup for a horizontal bar since the bar change rate is 0 for y meaning no vertical change
	speedProgress->setBarChangeRate(ccp(1, 0));
	addChild(speedProgress);
	speedProgress->setPosition(s_pPointProgress);
	setSpeedProgress(_hero->getSpeedLevel());
}

void GameLayer::setSpeedProgress(int speedLevel)
{
	CCProgressTo *to = CCProgressTo::create(0.6f, speedLevel * 20 - 0.01f);
	speedProgress->runAction(to);
}

void GameLayer::ansRight()
{
	g_Control.m_nRight++;
	if (_hero->changeSpeed(true))
	{
		g_Control.playEffect(s_effectUseItem);
		setSpeedProgress(_hero->getSpeedLevel());
	}

	_hero->idle();

	addScore();

	if (false == isLevelUp())
	{
		nextQuestion();
	}
}

void GameLayer::ansWrong()
{
	g_Control.m_nWrong++;
	int speedLevel = _hero->getSpeedLevel();
	if (_hero->changeSpeed(false))
	{
		g_Control.playEffect(s_effectAnswer);
		speedLevel = _hero->getSpeedLevel();
		setSpeedProgress(speedLevel);
	}

	if (0 == speedLevel)
	{
		gameOver(false);
	}
	else
	{
		nextQuestion();
	}
}

void GameLayer::initQuestion()
{
	//题目背景
	CCSprite *sprite = CCSprite::create(s_pBgQuestion.m_strPath);
	sprite->setPosition(s_pBgQuestion.m_Position);
	addChild(sprite);
	CCLabelTTF *pLabel = CCLabelTTF::create("", "Arial", SIZE_QUESTION_TXT);

	if (NULL != pLabel)
	{
		pLabel->setColor(COLOR_QUESTION);
		pLabel->setPosition(s_pBgQuestion.m_Position);
		pLabel->setTag(TAG_QUESTION_TITLE);
		this->addChild(pLabel);

		changeQuestion();
	}
}

void GameLayer::changeQuestion()
{
	isAnsRight = false;
	g_Control.m_fSpeedGain = 1;
	dataControl->initQuestion(gameLevel);

	CCLabelTTF *pLabel = (CCLabelTTF *)getChildByTag(TAG_QUESTION_TITLE);

	if (NULL != pLabel)
	{
		string gbkStr(dataControl->getQuestion());
		CCLog("CSV_______%s", dataControl->getQuestion().c_str());
		//StringUtils::GBKToUTF8(gbkStr);
		pLabel->setString(gbkStr.c_str());
	}
}

void GameLayer::initTitle()
{
	CCSprite *sprite = CCSprite::create(s_pBgTitle.m_strPath);
	sprite->setPosition(s_pBgTitle.m_Position);
	addChild(sprite);

	timeProgress = CCProgressTimer::create(CCSprite::create(s_pTimeProgressFull));
	timeProgress->setType(kCCProgressTimerTypeBar);
	//    Setup for a bar starting from the left since the midpoint is 0 for the x
	timeProgress->setMidpoint(ccp(0, 0));
	//    Setup for a horizontal bar since the bar change rate is 0 for y meaning no vertical change
	timeProgress->setBarChangeRate(ccp(0, 1));
	addChild(timeProgress);
	timeProgress->setPosition(s_pPointTimeProgress);
	CCProgressTo *to = CCProgressTo::create(1, timeRemain * 100.0f/timeMax);
	timeProgress->runAction(to);

	g_Control.creatLabelAtlas(0, s_pNumTitleScore, this, LabelAtlas_SCORE);

	g_Control.creatLabelAtlas(timeRemain, s_pNumTitleTime, this, LabelAtlas_TIME);

	g_Control.creatLabelAtlas(g_Control.m_nCoin, s_pNumTitleCoin, this, LabelAtlas_COIN);
	//CCLabelAtlas *pTextLabel = g_Control.creatLabelAtlas("999", s_pNumTitleCoin, this);
	//pTextLabel->setPosition(ccp(s_pNumTitleCoin.m_Position.x + 135, s_pNumTitleCoin.m_Position.y));

	CCMenuItemImage *pMenuItem = CCMenuItemImage::create(s_pMenuItemPause.charMapFile, s_pMenuItemPause.charMapFilePress, this, menu_selector(GameLayer::onPauseClick));
	if (NULL != pMenuItem)
	{
		pMenuItem->setPosition(s_pMenuItemPause.m_Position);
	}
	CCMenu *pMenu = CCMenu::create(pMenuItem, NULL);
	if (NULL != pMenu)
	{
		pMenu->setPosition(CCPointZero);
		addChild(pMenu, ORDER_MENU);
	}
}

void GameLayer::onPauseClick(CCObject *pSender)
{
	if (g_Control.gameState == GRS_UNKNOWN)
	{
		return;
	}

	g_Control.gameState = GRS_PAUSE;
	g_Control.playEffect(s_effectButton);

	PopupLayer *popupLayer = PopupLayer::create(g_pExitTips[0]);
	popupLayer->setCallbackFunc(this, callfuncN_selector(GameLayer::buttonCallback));
	popupLayer->addButton(g_pExitTips[3], g_pExitTips[4], "", BTN_CANCLE);
	popupLayer->addButton(g_pExitTips[1], g_pExitTips[2], "", BTN_SURE);

	CCLayerColor *layer = CCLayerColor::create(ccc4(25, 25, 25, 125));
	layer->setTag(TAG_DARK_BG);
	this->addChild(layer, ORDER_POP);

	this->addChild(popupLayer, ORDER_POP);
}

void GameLayer::buttonCallback(CCNode *pNode)
{
	g_Control.playEffect(s_effectButton);
	switch (pNode->getTag())
	{
	case BTN_SURE:
		exitGame();	
		break;
	case BTN_CANCLE:
		g_Control.gameState = GRS_PLAY;
		this->removeChildByTag(TAG_DARK_BG);
		break;
	default:
		break;
	}
}

/*开始倒计时动画*/
void GameLayer::countDown(int index)
{
	char szFileName[32] = { 0 };
	sprintf(szFileName, s_pCountDown, index);

	CCSprite *pcdSprite = CCSprite::create(szFileName);
	if (NULL == pcdSprite)
	{
		return;
	}
	pcdSprite->setPosition(CENTER);
	pcdSprite->setOpacity(128);
	this->addChild(pcdSprite, ORDER_COUNT_DOWN, TAG_COUNTDOWN);

	pcdSprite->runAction(CCSequence::create(CCSpawn::create(CCScaleTo::create(0.2f, 1), CCFadeTo::create(0.2f, 255), NULL),
		CCDelayTime::create(0.6f),
		CCSpawn::create(CCScaleTo::create(0.2f, 0), CCFadeTo::create(0.2f, 0), NULL),
		CCCallFunc::create(this, callfunc_selector(GameLayer::countDownDone)), NULL));
}

void GameLayer::countDownDone()
{
	static int nCount = 0;
	this->removeChildByTag(TAG_COUNTDOWN);
	nCount++;
	if (nCount < 4)
	{
		countDown(nCount);
	}
	else
	{
		//g_OralCalculating.playBGMusic(OralCalculating::MIDBG_MUSIC_B1);
		nCount = 0;
		gameLevel = 1;

		initQuestion();
		this->initMonster();
		this->initProgress();
		initCards();
		g_Control.gameState = GRS_PLAY;

		g_Control.reset();
		//开启定时器，延时2s执行，执行3+1次，执行间隔1s  
		//this->schedule(schedule_selector(GameLayer::timeScheduler), 1, 3, 2);
	}
}

void GameLayer::nextQuestion()
{
	CCLog("________nextQuestion__________");

	CCObject *obj;
	CCARRAY_FOREACH(monsters, obj)
	{
		CCNode *node = (CCNode *)obj;
		removeChild(node);
	}

	changeQuestion();
	initMonster();

	g_Control.gameState = GRS_PLAY;
}

void GameLayer::initCards()
{
	CCMenu *pMenu = CCMenu::create();
	pMenu->setPosition(CCPointZero);
	pMenu->setTag(TAG_MENU);
	addChild(pMenu);

	char szFileName[32] = { 0 };
	char szFileName2[32] = { 0 };
	char szFileName3[32] = { 0 };
	for (int i = 0; i < CARD_COUNT; i++)
	{
		sprintf(szFileName, s_pathCard.charMapFile, i);
		sprintf(szFileName2, s_pathCard.charMapFilePress, i);
		sprintf(szFileName3, s_pathCardDisable, i);

		CCMenuItemImage *pMenuItem = CCMenuItemImage::create(szFileName, szFileName2, szFileName3, this, menu_selector(GameLayer::onCardClick));
		pMenuItem->setPosition(ccp(105 * i + 56, 68));
		pMenuItem->setTag(BTN_CARD + i);
		pMenu->addChild(pMenuItem);

		if (g_Control.cards[i] == 0)
		{
			pMenuItem->setEnabled(false);
		}
	}
}

void GameLayer::onCardClick(CCObject *pSender)
{
	g_Control.playEffect(s_effectButton);

	playSpeedUpAnim();
	CCMenuItemImage *card = (CCMenuItemImage *)pSender;
	int tag = card->getTag();
	card->setEnabled(false);

	int idx = tag - BTN_CARD;
	char key[8] = { 0 };
	sprintf(key, s_keyCard, idx);
	g_Control.cards[idx] = 0;
	CCUserDefault::sharedUserDefault()->setIntegerForKey(key, 0);

	switch (tag)
	{
	case BTN_CARD://换题卡
		nextQuestion();
		break;
	case BTN_CARD + 1://排除卡
		excludeAnswer();	
		break;
	case BTN_CARD + 2://免答卡
		noAnswerCard();
		break;
	case BTN_CARD + 3://加速卡
		speedUpCard();
		break;
	case BTN_CARD + 4://答案卡
		isShowAnswerAfterWrong = true;
		break;
	case BTN_CARD + 5://翻倍卡
		dobuleScoreCard();
		break;
	default:
		break;
	}
}

void GameLayer::playSpeedUpAnim()
{
	g_Control.playEffect(s_effectUseItem);

	CCLayerColor *layer = CCLayerColor::create(ccc4(25, 25, 25, 125));
	layer->setTag(TAG_DARK_BG);
	this->addChild(layer, ORDER_POP);

	char ch[32] = { 0 };
	sprintf(ch, hero_speed_up.m_strPath.c_str(), 0);

	CCAnimation *animation = AnimationUtils::createAnimationWithSpriteFrames(hero_speed_up);
	CCFiniteTimeAction *actionOne = CCSequence::create(
		CCAnimate::create(animation),
		CCCallFunc::create(this, callfunc_selector(GameLayer::animFinish)),
		NULL
		);

	PopupLayer *pop = PopupLayer::playAnimation(ch, hero_speed_up.m_Position, actionOne);
	layer->addChild(pop);
}

void GameLayer::animFinish()
{
	this->removeChildByTag(TAG_DARK_BG);
}

/*排除一个错误答案*/
void GameLayer::excludeAnswer()
{
	CCNode *child = getChildByTag(TAG_WRONG_ANS);
	monsters->removeObject(child);
	removeChild(child);
}

void GameLayer::noAnswerCard()
{
	//runAction(CCSequence::create(CCDelayTime::create(2.0f), CCCallFunc::create(this, callfunc_selector(GameLayer::ansRight)), NULL));
	CCObject *pObj;

	g_Control.gameState = GRS_TOUCH_OVER;
	setSpeedGain(_hero->getSpeedLevel());

	isAnsRight = true;
	timeRemain = clampf(timeRemain + 8, 0, timeMax);

	CCARRAY_FOREACH(monsters, pObj)
	{
		Monster *_mon = (Monster *)pObj;
		_mon->hideOption();
		_mon->changeToTomato();
	}
}

/*提升两级速度*/
void GameLayer::speedUpCard()
{
	if (_hero->changeSpeed(true))
	{
		_hero->changeSpeed(true);
		setSpeedProgress(_hero->getSpeedLevel());
	}
}

void GameLayer::showRightAnsCard()
{
	if (isShowAnswerAfterWrong)
	{
		CCLabelTTF *pLabel = (CCLabelTTF *)getChildByTag(TAG_QUESTION_TITLE);

		if (NULL != pLabel)
		{
			string gbkStr(dataControl->getQuestion());
			//StringUtils::GBKToUTF8(gbkStr);
			pLabel->setString(dataControl->getIdiom().c_str());
		}
	}
}

void GameLayer::dobuleScoreCard()
{
	doubleScoreCount = 20; 
}

void GameLayer::update(float dt)
{
	bool isUpdate = g_Control.gameState == GRS_PLAY || g_Control.gameState == GRS_FINISH_ANSWER || g_Control.gameState == GRS_TOUCH_OVER;
	int size = monsters->count();
	if (size == 0 || !isUpdate)
	{
		return;
	}

	int count = 0;
	CCObject *pObj;
	CCARRAY_FOREACH(monsters, pObj)
	{
		Monster *_mon = (Monster *)pObj;
		
		if (_mon->getActionState() == kActionStateHide)
		{
			count++;
		}
		else if (_mon->getPositionX() <= 320)
		{
			if (isAnsRight)
			{
				g_Control.playEffect(s_effectEat); 
				_mon->actionTomatoEat(g_Control.getRoadVelocity() * dt);
			}
			else
			{
				g_Control.playEffect(s_effectHit);
				_hero->hit();
				_mon->actionHitToFar();
				setSpeedGain(_hero->getSpeedLevel());
			}
			showRightAnsCard();
		}
		else if (kActionStateTomatoEat != _mon->getActionState())
		{
			 _mon->setPositionX(_mon->getPositionX() + g_Control.getRoadVelocity() * dt * g_Control.m_fSpeedGain);
		}
	}

	if (count == size && g_Control.gameState != GRS_FINISH_ANSWER)
	{
		g_Control.gameState = GRS_FINISH_ANSWER;
		if (isAnsRight)
		{
			ansRight();
			//runAction(CCSequence::create(CCDelayTime::create(2.0f), CCCallFunc::create(this, callfunc_selector(GameLayer::ansRight)), NULL));
		}
		else
		{
			ansWrong();
			//runAction(CCSequence::create(CCDelayTime::create(1.0f), CCCallFunc::create(this, callfunc_selector(GameLayer::ansWrong)), NULL));
		}
	}

	timeRemain -= dt;
	handleTimeOver();
	updateTitle();
}

void GameLayer::updateTitle()
{
	timeProgress->setPercentage(timeRemain * 100.0f / timeMax);

	CCLabelAtlas * labelAtlas = (CCLabelAtlas *)getChildByTag(LabelAtlas_SCORE);
	char num[32] = { 0 };
	sprintf(num, "%d", g_Control.m_nScore);
	labelAtlas->setString(num);

	labelAtlas = (CCLabelAtlas *)getChildByTag(LabelAtlas_COIN);
	sprintf(num, "%d", g_Control.m_nCoin);
	labelAtlas->setString(num); 

	labelAtlas = (CCLabelAtlas *)getChildByTag(LabelAtlas_TIME);
	sprintf(num, "%02d", (int)timeRemain);
	labelAtlas->setString(num); 

	static bool isTimeLess;
	if (!isTimeLess && timeRemain<10 && timeRemain>0)
	{
		isTimeLess = true;
		g_Control.playEffect(s_effectTimeLess);
	}
	else if(timeRemain >= 10)
	{
		isTimeLess = false;
	}
}

bool GameLayer::isLevelUp()
{
	bool isLevelUp = false;

	int count = LEVEL_ONE;
	switch (gameLevel)
	{
	case 1:
		count = LEVEL_ONE;
		break;
	case 2:
		count = LEVEL_TWO;
		break;
	case 3:
		count = LEVEL_THREE;
		break;
	case 4:
		count = LEVEL_FOUR;
		break;
	default:
		count = LEVEL_FOUR;
		break;
	}

	if (g_Control.m_nRight >= count)
	{
		gameLevel++;
		if (gameLevel >= 5)
		{
			gameOver(true);
		}
		else
		{
			g_Control.playEffect(s_effectLevelUp);
			timeRemain = timeMax;
			CCSprite *pcdSprite = CCSprite::create(s_pLevelUp);

			pcdSprite->setPosition(CENTER);
			pcdSprite->setOpacity(128);
			this->addChild(pcdSprite, ORDER_COUNT_DOWN, TAG_COUNTDOWN);

			pcdSprite->runAction(CCSequence::create(CCSpawn::create(CCScaleTo::create(0.2f, 1), CCFadeTo::create(0.2f, 255), NULL),
				CCDelayTime::create(0.6f),
				CCSpawn::create(CCScaleTo::create(0.2f, 0), CCFadeTo::create(0.2f, 0), NULL),
				CCCallFunc::create(this, callfunc_selector(GameLayer::levelUpDone)), NULL));
		}
		
		isLevelUp = true;
	}

	return isLevelUp;
}

void GameLayer::levelUpDone()
{
	removeChildByTag(TAG_COUNTDOWN);
	nextQuestion();
}

void GameLayer::gameOver(bool isPassAll)
{
	g_Control.gameState = GRS_OVER;
	removeChild(_hero);

	CCSprite *pcdSprite = CCSprite::create(s_pBgGameOver);
	pcdSprite->setPosition(CENTER);
	addChild(pcdSprite, ORDER_POP);

	if (isPassAll)
	{
		g_Control.playEffect(s_effectGamePass);
		CCAnimation *animation = AnimationUtils::createAnimationWithSpriteFrames(s_pGamePass);
		CCFiniteTimeAction *actionOne = CCSequence::create(
			CCAnimate::create(animation),
			CCCallFunc::create(this, callfunc_selector(GameLayer::exitGame)),
			NULL
			);

		PopupLayer *pop = PopupLayer::playAnimation("pass/game_pass_00.png", CENTER, actionOne);
		pcdSprite->addChild(pop);
	}
	else
	{
		g_Control.playEffect(s_effectGameOver);
		pcdSprite = CCSprite::create(s_pGameOver);

		pcdSprite->setPosition(ccp(640, 1000));
		pcdSprite->setOpacity(128);
		this->addChild(pcdSprite, ORDER_POP);

		pcdSprite->runAction(CCSequence::create(CCSpawn::create(CCMoveTo::create(0.6f, CENTER), CCScaleTo::create(0.2f, 1), CCFadeTo::create(0.2f, 255), NULL),
			CCDelayTime::create(1.5f),
			CCSpawn::create(CCScaleTo::create(0.2f, 0), CCFadeTo::create(0.2f, 0), NULL),
			CCCallFunc::create(this, callfunc_selector(GameLayer::exitGame)), NULL));
	}

}

void GameLayer::exitGame()
{
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		JniMethodInfo t;
		if (JniHelper::getStaticMethodInfo(t, "com/eebbk/turbosnail/TurboSnail", "submitGameScore", "(I)V")) {
			t.env->CallStaticVoidMethod(t.classID, t.methodID, g_Control.m_nScore);
			t.env->DeleteLocalRef(t.classID);
		}
	#endif
	CCDirector::sharedDirector()->replaceScene(ScoreScene::create());
}

void GameLayer::addScore()
{
	float scoreRate = 1;
	if (doubleScoreCount > 0)
	{
		scoreRate = 2;
		doubleScoreCount--;
	}

	float speedReward = 5;
	if (_hero->getSpeedLevel()<5)
	{
		speedReward = 4;
	}

	float levelReward = 1;
	if (gameLevel == 2)
	{
		levelReward = 1.5f;
	}
	else if (gameLevel == 3)
	{
		levelReward = 2;
	}
	else if (gameLevel == 4)
	{
		levelReward = 2.5;
	}

	g_Control.m_nScore += 2 * speedReward * levelReward * scoreRate;
	CCLog("g_Control.m_nScore = %d speedReward = %f  levelReward = %f  scoreRate = %f ", g_Control.m_nScore , speedReward , levelReward, scoreRate);
}

void GameLayer::handleTimeOver()
{
	if (timeRemain < 1)
	{
		gameOver(false);
	}
}

void GameLayer::setSpeedGain(int level)
{
	g_Control.m_fSpeedGain = 5 * 5 / level;
}
