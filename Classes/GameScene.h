/*
 * GameScene.cpp
 *
 *  Created on: 2013-1-24
 *      Author: ragnarok
 */

#ifndef GAMESCENE_H_
#define GAMESCENE_H_

#include "cocos2d.h"
#include "Ship.h"
#include "Enemy.h"
#include "Global.h"

using namespace cocos2d;

class GameLayer : public CCLayer
{
public:
	GameLayer():
	backSkyIsReload(false),
	backTileMapIsReload(false),
	backReTileMap(NULL),
	backSky(NULL),
	backSkyReSprite(NULL),
	backTileMap(NULL),
	ship(NULL),
	shipLifeSprite(NULL),
	shipLifeLabel(NULL),
	_beginPos(ccp(0, 0)),
	_state(STATE_PLAY),
	_isTouch(false),
	explosionAnim(new CCArray),
	_time(0),
	toRemoveExplove(new CCArray)
	{};

	virtual bool init();

	void backcallback(CCNode *pSender);

	void scoreCounter();
	void initBackground();
	void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
	void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
	void ccTouchesEnded(CCSet* touches,CCEvent* event);
	void processEvent(CCTouch *pTouch, CCEvent *pEvent);
	void update();
	void checkIsCollide();
	void removeInactiveUnit();
	void checkIsReborn();
	void updateUI();
	void collide();
	void movingBackground();
	void onGameOver();

	void loadEnemy();
	void addEnemy();

	void onMoveHorizontalComplete(CCNode* pSender);

	virtual ~GameLayer();

	CREATE_FUNC(GameLayer);

	inline Ship* getShip() const { return ship; };
	void removeExplove() {
		CCSprite *sprite = dynamic_cast<CCSprite *>(this->toRemoveExplove->objectAtIndex(0));
		this->removeChild(sprite, true);
		this->toRemoveExplove->removeObjectAtIndex(0);
	};

	const static int enemiesNum = 5;
private:
	CCSize winSize;

	// for background
	CCSprite *backSky;
	float backSkyHeight;
	bool backSkyIsReload;
	CCSprite *backSkyReSprite;

	// for back tile map
	CCTMXTiledMap *backTileMap;
	float backTileMapHeight;
	bool backTileMapIsReload;
	CCTMXTiledMap *backReTileMap;

	// ship
	Ship *ship;

	// score
	CCLabelTTF *scoreLabel;

	// ship life
	CCSprite *shipLifeSprite;
	CCLabelTTF *shipLifeLabel;

	// some other utility variable
	float _time;
	int _tmpScore;
	CCRect screenRect;
	CCArray *explosionAnim;
	CCPoint _beginPos;
	int _state;
	bool _isTouch;

	CCArray* toRemoveExplove;
};

class GameScene : public CCScene
{
public:
	GameScene():layer(NULL) {};
	virtual ~GameScene();

	virtual bool init();

	CREATE_FUNC(GameScene);
private:
	GameLayer *layer;

};



#endif /* GAMESCENE_CPP_ */
