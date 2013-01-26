/*
 * Explosion.h
 *
 *  Created on: 2013-1-25
 *      Author: ragnarok
 */

#ifndef EXPLORSION_H_
#define EXPLORSION_H_

#include "cocos2d.h"

using namespace cocos2d;

class Explosion : public CCSprite
{
public:
	Explosion();
	virtual bool init();

	CREATE_FUNC(Explosion);

	void destroy();
	void startRun();
private:
	float tmpWidth;
	float tmpHeight;

	CCAnimate* destroyAnim;
};



#endif /* EXPLORSION_H_ */
