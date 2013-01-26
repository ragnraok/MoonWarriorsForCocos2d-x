/*
 * Ship.h
 *
 *  Created on: 2013-1-25
 *      Author: ragnarok
 */

#ifndef SHIP_H_
#define SHIP_H_

#include "cocos2d.h"
#include "Global.h"

using namespace cocos2d;

class Ship : public CCSprite
{
public:
	Ship();

	virtual bool init();
	CREATE_FUNC(Ship);

	void update(float dt);
	void shoot(float dt);
	void destroy();
	void hurt();
	CCRect collideRect();
	void setCanBeAttack();

	inline const bool isActive() const { return this->active; };

	const static int zOrder = 3000;
private:
	float speed;
	float bulletSpeed;
	float HP;
	float bulletTypeValue;
	float bulletPowerValue;
	float throwBombing;
	float canBeAttack;
	float isThrowingBomb;
	float maxBulletPowerValue;
	CCPoint appearPosition;
	float hurtColorLife;
	bool active;
	float timetick;

	CCSprite *ghostSprite;
};



#endif /* SHIP_H_ */
