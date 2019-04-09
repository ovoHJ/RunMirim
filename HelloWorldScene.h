#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "ui\CocosGUI.h"
#include <vector> 
#include <stdlib.h>
#include <time.h>

class HelloWorld : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();


    virtual bool init();

	void Move(float dt);
	void Update(float dt);

	bool allowJump;
	bool end;
	bool a;
		
	cocos2d::Node* movedObject;

	cocos2d::ui::Button* jump;

	cocos2d::Sprite* eat;
	cocos2d::Sprite* background;
	cocos2d::Sprite* background2;
	cocos2d::Sprite* man;
	cocos2d::Sprite* orux;
	cocos2d::Label* text;
	cocos2d::Sprite* coin[60];
	cocos2d::Vec2 nowPosition;
	cocos2d::Vec2 nowCharacterPosition;

	int money;
	int random;
	int rm;
	char moneyScore[100];

	int check;

	std::vector<cocos2d::Sprite*> object;
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

};

#endif // __HELLOWORLD_SCENE_H__
