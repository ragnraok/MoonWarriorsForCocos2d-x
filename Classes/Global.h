/*
 * Global.h
 *
 *  Created on: 2013-1-25
 *      Author: ragnarok
 */

#ifndef GLOBAL_H_
#define GLOBAL_H_

#include "cocos2d.h"
using namespace cocos2d;

class GV : public CCObject {
public:
	CCArray *enemies;
	CCArray *enemy_bullets;
	CCArray *player_bullets;

	static GV* getInstance() {
		if (obj == NULL) {
			obj = new GV();
		}
        return obj;
	}

protected:
	GV() {
		enemies = new CCArray();
		enemy_bullets = new CCArray();
		player_bullets = new CCArray();
	};
	static GV* obj;
};

static int LIFE = 4;
static int SCORE = 0;

static int SCALE_FACTOR = 2;

const static char* LOG_TAG = "Ragnarok";

const static int PLAYER_BULLET_TAG = 900;
const static int ENEMY_BULLET_TAG = 901;
const static int ENEMY_TAG = 1000;
const static int PLAYER_TAG = 1000;

const static int STATE_HOME = 0;
const static int STATE_PLAY = 1;
const static int STATE_OVER = 2;

// enemy move type
const static int MOVE_VERTICAL = 0;
const static int MOVE_OVERLAP = 1;

#endif /* GLOBAL_H_ */
