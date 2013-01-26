/*
 * Enemy.h
 *
 *  Created on: 2013-1-25
 *      Author: ragnarok
 */

#ifndef ENEMY_H_
#define ENEMY_H_

#include "cocos2d.h"
#include "Global.h"

using namespace cocos2d;

class Enemy : public CCSprite
{
public:
	Enemy():
	active(false),
	speed(400),
	bulletSpeed(-900),
	HP(4),
	bulletPowerValue(1),
	scoreValue(200),
	delayTime(CCRANDOM_0_1() * 1.2 + 0.5),
	_hurtColorLife(0),
	_timetick(0),
	moveType(MOVE_VERTICAL)
	{};
	virtual bool init();
	CREATE_FUNC(Enemy);


	void update(float dt);
	void destroy();
	void shoot();
	void hurt();
	CCRect collideRect();

	const static int zOrder = 200;

	inline const int getMoveSpeed() const { return this->speed; };
	inline const int getMoveType() const { return this->moveType; };
private:
	bool active;
	float speed;
	float bulletSpeed;
	float HP;
	float bulletPowerValue;
	float scoreValue;
	float delayTime;
	float _hurtColorLife;
	float _timetick;
	int moveType;
};


#endif /* ENEMY_H_ */
