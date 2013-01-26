
/*
 * GameScene.cpp
 *
 *  Created on: 2013-1-24
 *      Author: ragnarok
 */

#include "GameScene.h"
#include "StartMenu.h"
#include "Loger.h"
#include "Global.h"
#include "Enemy.h"
#include "Bullet.h"

bool GameLayer::init()
{
	if (!CCLayer::init()) {
		return false;
	}

	//GV::enemies->removeAllObjects();
	//GV::enemy_bullets->removeAllObjects();
	//GV::player_bullets->removeAllObjects();
	GV::getInstance()->enemies->removeAllObjects();
	GV::getInstance()->enemy_bullets->removeAllObjects();
	GV::getInstance()->player_bullets->removeAllObjects();
	SCORE = 0;
	LIFE = 0;

	this->winSize = CCDirector::sharedDirector()->getWinSize();

	// back menu
	CCLabelTTF *backLabel = CCLabelTTF::create("Back", "Artial", 45);
	CCMenuItemLabel *backMenuItemLabel = CCMenuItemLabel::create(backLabel, this, menu_selector(GameLayer::backcallback));
	CCMenu *menu = CCMenu::create(backMenuItemLabel, NULL);
	menu->setPosition(ccp(winSize.width - 80, 40));
	this->addChild(menu, 1);

	this->initBackground();
	this->screenRect = CCRectMake(0, 0, winSize.width, winSize.height);

	this->scoreLabel = CCLabelTTF::create("Score: 0", "Arial", 35);
	//this->scoreLabel->setColor(ccRED);
	this->scoreLabel->setAnchorPoint(ccp(1, 0));
	this->addChild(this->scoreLabel, 1000);
	this->scoreLabel->setPosition(ccp(winSize.width - 50, winSize.height - 80));

	CCTexture2D *shipTexture = CCTextureCache::sharedTextureCache()->addImage("ship01.png");
	this->shipLifeSprite = CCSprite::createWithTexture(shipTexture, CCRectMake(0, 0, 60, 38));
	this->shipLifeSprite->setScale(0.6 * SCALE_FACTOR);
	this->shipLifeSprite->setPosition(ccp(30 * SCALE_FACTOR, winSize.height - 60));
	this->addChild(shipLifeSprite, 1, 5);

	this->shipLifeLabel = CCLabelTTF::create("0", "Arial", 35);
	this->shipLifeLabel->setPosition(ccp(60 * SCALE_FACTOR, winSize.height - 60));
	this->shipLifeLabel->setColor(ccRED);
	this->addChild(shipLifeLabel, 1000);

	this->ship = Ship::create();
	this->addChild(ship, Ship::zOrder, PLAYER_TAG);

	// enable touch
	this->setTouchEnabled(true);

	//LOGD(LOG_TAG, "added ship");

	//this->scheduleUpdate();
	this->schedule(schedule_selector(GameLayer::update), 0.01);
	this->schedule(schedule_selector(GameLayer::scoreCounter), 1);

	return true;
}

void GameLayer::backcallback(CCNode* pSender) {
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(1, StartMenu::scene()));
}


void GameLayer::initBackground() {
	backSky = CCSprite::create("bg.jpg");
	backSky->setAnchorPoint(ccp(0, 0));
	this->backSkyHeight = backSky->getContentSize().height;
	this->addChild(backSky, -10);
	this->backSky->runAction(CCMoveBy::create(1, ccp(0, -48)));
	this->schedule(schedule_selector(GameLayer::movingBackground), 1);

	this->backTileMap = CCTMXTiledMap::create("level01.tmx");
	this->backTileMap->setScale(1.4);
	this->addChild(backTileMap, -9);
	this->backTileMapHeight = backTileMap->getMapSize().height * backTileMap->getTileSize().height;
	backTileMapHeight -= 200;
	backTileMap->runAction(CCMoveBy::create(1, ccp(0, -200)));

	this->schedule(schedule_selector(GameLayer::movingBackground), 1);
}


void GameLayer::movingBackground() {
	this->backSky->runAction(CCMoveBy::create(1, ccp(0, -48)));
	this->backSkyHeight -= 48;


	if (backSkyHeight <= this->winSize.height) {
		if (this->backSkyIsReload == false) {
			this->backSkyReSprite = CCSprite::create("bg.jpg");
			this->backSkyReSprite->setAnchorPoint(ccp(0, 0));
			this->addChild(backSkyReSprite, -10);
			this->backSkyReSprite->setPosition(ccp(0, this->winSize.height));
			this->backSkyIsReload = true;
		}
		this->backSkyReSprite->runAction(CCMoveBy::create(1, ccp(0, -48)));
	}
	if (this->backSkyHeight <= 0) {
		this->backSkyHeight = this->backSky->getContentSize().height;
		this->removeChild(backSky, true);
		this->backSky = this->backSkyReSprite;
		this->backSkyReSprite = NULL;
		this->backSkyIsReload = false;
	}

	this->backTileMap->runAction(CCMoveBy::create(1, ccp(0, -200)));
	this->backTileMapHeight -= 200;
	if (backTileMapHeight <= this->winSize.height) {
		if (this->backTileMapIsReload == false) {
			this->backReTileMap = CCTMXTiledMap::create("level01.tmx");
			this->backReTileMap->setScale(1.4);
			this->addChild(backReTileMap, -9);
			this->backReTileMap->setPosition(ccp(0, this->winSize.height));
			this->backTileMapIsReload = true;
		}
		this->backReTileMap->runAction(CCMoveBy::create(1, ccp(0, -200)));
	}

	if (this->backTileMapHeight <= 0) {
		this->backTileMapHeight = backTileMap->getMapSize().height * backTileMap->getTileSize().height;
		this->removeChild(backTileMap, false);
		this->backTileMap = this->backReTileMap;
		this->backReTileMap = NULL;
		this->backTileMapIsReload = false;
	}
}


void GameLayer::onGameOver() {
}

void GameLayer::scoreCounter() {
	if (this->_state == STATE_PLAY) {
		this->_time++;
		this->loadEnemy();
		//this->addEnemy();
	}
}

void GameLayer::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent) {
	//LOGD(LOG_TAG, "on Touch begin");
	this->_isTouch = true;

}

void GameLayer::ccTouchesMoved(CCSet* touches,CCEvent* event) {
	//LOGD(LOG_TAG, "on Touch Move");
	if (this->_isTouch) {
		this->processEvent((CCTouch*)(touches->anyObject()), event);
	}
}

void GameLayer::ccTouchesEnded(CCSet* touches,CCEvent* event) {
	//LOGD(LOG_TAG, "on touch end");
	this->_isTouch = false;
}

void GameLayer::processEvent(CCTouch *pTouch, CCEvent *pEvent) {
	if (this->_state == STATE_PLAY) {
		CCPoint delta = pTouch->getDelta();
		CCPoint curPos = this->ship->getPosition();
		curPos = ccpAdd(curPos, delta);
		curPos = ccpClamp(curPos, CCPointZero, ccp(winSize.width, winSize.height));
		this->ship->setPosition(curPos);
	}
}

void GameLayer::update() {
	if (this->_state == STATE_PLAY) {
		this->checkIsCollide();
		this->removeInactiveUnit();
		this->checkIsReborn();
		this->updateUI();
	}
}

void GameLayer::checkIsCollide() {
	Enemy *enemy;
	Bullet *bullet;
	CCObject *it;
	CCObject *jt;
	CCArray* toRemoveEnemy = new CCArray();
	CCArray* toRemoveEnemyBullet = new CCArray();
	CCArray* toRemovePlayerBullet = new CCArray();
	int exploveCount = 0;
	CCARRAY_FOREACH(GV::getInstance()->enemies, it) {
		enemy = dynamic_cast<Enemy *>(it);
		CCARRAY_FOREACH(GV::getInstance()->player_bullets, jt) {
			bullet = dynamic_cast<Bullet *>(jt);
			if (bullet->collideRect().intersectsRect(enemy->collideRect())) {
				CCSprite *explode = CCSprite::create("hit.jpg");
				toRemoveExplove->addObject(explode);

				ccBlendFunc cbl = {GL_SRC_ALPHA, GL_ONE};
				explode->setBlendFunc(cbl);
				explode->setPosition(enemy->getPosition());
				explode->setRotation(CCRANDOM_0_1() * 360);
				explode->setScale(0.75 * SCALE_FACTOR);
				this->addChild(explode, 9999);
				explode->runAction(CCScaleBy::create(2, 2, 2));
				explode->runAction(CCFadeOut::create(2));
				//explode->runAction(CCSequence::create(CCFadeOut::create(2),
				//		CCCallFunc::create(this, callfunc_selector(GameLayer::removeExplove))));

				this->removeChild(bullet, true);
				this->removeChild(enemy, true);

				toRemovePlayerBullet->addObject(bullet);
				toRemoveEnemy->addObject(enemy);

				exploveCount++;
			}
			if (bullet->getPosition().y >= winSize.height || bullet->getPosition().y <= 0) {
				this->removeChild(bullet, true);
				toRemovePlayerBullet->addObject(bullet);
			}
		}
		if (enemy->collideRect().intersectsRect(this->ship->collideRect())) {
			if (this->ship->isActive()) {
				//enemy->destroy();
				//this->ship->hurt();
				//this->ship->destroy();
				this->ship->hurt();
			}
		}
		if (!this->screenRect.intersectsRect(enemy->collideRect())) {
			//enemy->destroy();
			this->removeChild(enemy, true);
			toRemoveEnemy->addObject(enemy);
		}
	}
	it = NULL;
	jt = NULL;
	CCARRAY_FOREACH(GV::getInstance()->enemy_bullets, it) {
		bullet = dynamic_cast<Bullet *>(it);
		if (bullet->collideRect().intersectsRect(this->ship->collideRect())) {
			if (this->ship->isActive()) {
				//bullet->destroy();
				this->removeChild(bullet, true);
				//this->ship->destroy();
				toRemoveEnemyBullet->addObject(bullet);
			}
		}
		if (bullet->getPosition().y >= winSize.height || bullet->getPosition().y <= 0) {
			this->removeChild(bullet, true);
			toRemoveEnemyBullet->addObject(bullet);
		}
	}
	it = NULL;
	CCARRAY_FOREACH(toRemoveEnemy, it) {
		enemy = dynamic_cast<Enemy *>(it);
		GV::getInstance()->enemies->removeObject(enemy);
	}
	it = NULL;
	CCARRAY_FOREACH(toRemoveEnemyBullet, it) {
		bullet = dynamic_cast<Bullet *>(it);
		GV::getInstance()->enemy_bullets->removeObject(bullet);
	}
	it = NULL;
	CCARRAY_FOREACH(toRemovePlayerBullet, it) {
		bullet = dynamic_cast<Bullet *>(it);
		GV::getInstance()->player_bullets->removeObject(bullet);
	}
	toRemoveEnemy->release();
	toRemoveEnemy = NULL;
	toRemoveEnemyBullet->release();
	toRemoveEnemyBullet = NULL;
	toRemovePlayerBullet->release();
	toRemovePlayerBullet = NULL;

	if (toRemoveExplove->count() >= 50) {
		it = NULL;
		CCARRAY_FOREACH_REVERSE(toRemoveExplove, it) {
			LOGD(LOG_TAG, "start remove");
			CCSprite *explode = dynamic_cast<CCSprite *>(it);
			this->removeChild(explode, true);
		}
		toRemoveExplove->removeAllObjects();
	}
}

void GameLayer::removeInactiveUnit() {
}

void GameLayer::checkIsReborn() {
}

void GameLayer::updateUI() {
}

void GameLayer::collide() {
}

void GameLayer::loadEnemy() {
	for (int i = 0; i < GameLayer::enemiesNum; i++) {
		this->addEnemy();
	}
}

void GameLayer::addEnemy() {
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCPoint enemyPos = ccp(80 + (winSize.width - 160) * CCRANDOM_0_1(), winSize.height);

	Enemy *enemy = Enemy::create();
	enemy->setPosition(enemyPos);
	//LOGD(LOG_TAG, "movetype is %d", enemy->getMoveType());
	if (enemy->getMoveType() == MOVE_VERTICAL) {
		CCPoint offset = ccp(0, -winSize.height - enemy->getContentSize().height);
		CCMoveBy *tmpAction = CCMoveBy::create(3, offset);
		enemy->setScale(SCALE_FACTOR);
		this->addChild(enemy, Enemy::zOrder, ENEMY_TAG);
		GV::getInstance()->enemies->addObject(enemy);
		enemy->runAction(CCRepeatForever::create(tmpAction));
		return;
	}
	else if (enemy->getMoveType() == MOVE_OVERLAP) {
		enemy->setScale(SCALE_FACTOR);
		this->addChild(enemy, Enemy::zOrder, ENEMY_TAG);
		GV::getInstance()->enemies->addObject(enemy);
		//enemy->runAction(CCMoveTo::create(4, this->ship->getPosition()));
		//enemy->runAction(CCRepeatForever::create(CCMoveBy::create(3, ccp(0, -winSize.height - enemy->getContentSize().height))));
		enemy->runAction(CCRepeatForever::create(CCMoveBy::create(1, ccp(0, -winSize.height))));
		//enemy->runAction(CCSequence::create(
		//		CCMoveTo::create(4, this->ship->getPosition()),
		//		CCMoveBy::create(1, ccp(0, -winSize.height))
		//		));
		return;
	}
}

void GameLayer::onMoveHorizontalComplete(CCNode* pSender) {
	CCActionInterval *moveBy = CCMoveBy::create(1, ccp(100 + 100 * CCRANDOM_0_1(), 0));
	CCActionInterval *reverseMoveBy = moveBy->reverse();
	//pSender->runAction(CCRepeatForever::create(CCSequence::create(moveBy, CCDelayTime::create(1), reverseMoveBy)));
	CCFiniteTimeAction *sequence = CCSequence::create(moveBy, CCDelayTime::create(1), reverseMoveBy);
	//while (true) {
	//	pSender->runAction(sequence);
	//}
}

GameLayer::~GameLayer() {
}


GameScene::~GameScene() {
	if (this->layer) {
		this->layer->release();
		this->layer = NULL;
	}
}

bool GameScene::init() {
	if (!CCScene::init()) {
		return false;
	}

	this->layer = GameLayer::create();
	this->layer->retain();
	this->addChild(layer);

	return true;
}



