/*
 * AboutLayer.h
 *
 *  Created on: 2013-1-24
 *      Author: ragnarok
 */

#ifndef ABOUTLAYER_H_
#define ABOUTLAYER_H_

#include "cocos2d.h"

using namespace cocos2d;



class AboutLayer : public CCLayer
{
public:
	AboutLayer():label(NULL){};
	virtual ~AboutLayer();

	virtual bool init();
	CREATE_FUNC(AboutLayer);

	void backcallback(CCNode *pSender);
private:
	CCLabelTTF *label;
};

class AboutScene : public CCScene
{
public:
	AboutScene():layer(NULL){};
	virtual ~AboutScene();
	virtual bool init();
	CREATE_FUNC(AboutScene);
private:
	AboutLayer *layer;
};


#endif /* ABOUTLAYER_H_ */
