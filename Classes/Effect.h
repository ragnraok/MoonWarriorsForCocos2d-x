/*
 * Effect.h
 *
 *  Created on: 2013-1-24
 *      Author: ragnarok
 */

#ifndef EFFECT_H_
#define EFFECT_H_

#include "cocos2d.h"

using namespace cocos2d;

class Effect : public CCSprite
{
public:
	virtual bool init();

	CREATE_FUNC(Effect);

	void flareEffect(CCNode *parent, CCCallFunc *callback);

};



#endif /* EFFECT_H_ */
