#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
	return HelloWorld::create();
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Scene::init())
	{
		return false;
	}

	check = 0;
	srand(time(NULL));

	allowJump = true;
	end = false;
	a = true;

	movedObject = Node::create();
	movedObject->setPosition(Vec2(0, 0));
	addChild(movedObject);

	text = Label::createWithSystemFont("0", "ygotjalnanfont.ttf", 30);
	text->setColor(Color3B(0, 0, 0));
	text->setAnchorPoint(Vec2(1, 1));
	text->setPosition(Vec2(1060, 700));
	this->addChild(text);

	background = Sprite::create("background.png");
	background->setAnchorPoint(Vec2(0, 0));
	background->setPosition(Vec2(0, 0));
	movedObject->addChild(background);
	background2 = Sprite::create("background.png");
	background2->setAnchorPoint(Vec2(0, 0));
	background2->setPosition(Vec2(10800, 0));
	movedObject->addChild(background2);

	man = Sprite::create("man2.png");
	man->setAnchorPoint(Vec2(0, 0));
	man->setPosition(Vec2(5, 92));
	movedObject->addChild(man);

	auto animation = Animation::create();
	animation->setDelayPerUnit(0.3f);

	animation->addSpriteFrameWithFile("man1.png");
	animation->addSpriteFrameWithFile("man2.png");

	auto animate = Animate::create(animation);
	CCAction* rep = CCRepeatForever::create(animate);

	man->runAction(rep);

	orux = Sprite::create("orux.png");
	orux->setAnchorPoint(Vec2(1, 0));
	orux->setPosition(Vec2(70, 0));
	movedObject->addChild(orux);

	int j = 1500;
	for (int i = 0; i < 60; i++) {
		random = rand() % 5 + 1;

			coin[i] = Sprite::create("coin1.png");
			coin[i]->setAnchorPoint(Vec2(0, 0));
			coin[i]->setTag(1);

			if (random == 1)
			{
				coin[i]->setPosition(Vec2(j, 540));
			}
			else if(random == 2)
			{
				coin[i]->setPosition(Vec2(j, 440));
			}
			else if (random == 3)
			{
				coin[i]->setPosition(Vec2(j, 370));
			}
			else
			{
				coin[i]->setPosition(Vec2(j, 110));
			}

			movedObject->addChild(coin[i]);
			object.push_back(coin[i]);
			j += 200;
	}

	jump = ui::Button::create("no.png");
	jump->setAnchorPoint(Vec2(0, 0));
	jump->setPosition(Vec2(0, 0));
	jump->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
	{
		if (allowJump == false)
			return;

		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
		{
			allowJump = false;
			JumpBy* jumpAction = JumpBy::create(0.75f, Vec2(0, 0), 260, 1);
			CallFunc* callBack = CallFunc::create([&]()
			{
				allowJump = true;
			});

			Sequence* action = Sequence::create(jumpAction, callBack, nullptr);
			man->runAction(action);
		}
		}
	});
	addChild(jump, 1);

	schedule(schedule_selector(HelloWorld::Move, 1.0f / 60));
	schedule(schedule_selector(HelloWorld::Update, 1.0f / 60));

	return true;
}

void HelloWorld::Move(float dt)
{
	srand(time(NULL));

	Vec2 nowCharacterPosition = man->getPosition();
	nowCharacterPosition.x += 6;
	man->setPosition(nowCharacterPosition);

	Vec2 ddx = orux->getPosition();
	ddx.x += 6;
	orux->setPosition(ddx);

	nowPosition = movedObject->getPosition();
	nowPosition.x -= 6;
	movedObject->setPosition(nowPosition);

	if (nowPosition.x < -15000)
	{
		unschedule(schedule_selector(HelloWorld::Move));
		Sleep(2000);

		removeChild(text);
		Sprite* back = Sprite::create("back.png");
		back->setAnchorPoint(Vec2(0, 0));
		back->setPosition(Vec2(0, 0));
		back->setOpacity(188);
		this->addChild(back);

		if (end == true)
		{
			Sprite* m1 = Sprite::create("m1.png");
			m1->setPosition(Vec2(1080 / 2, 720 / 2+40));
			this->addChild(m1);
		}
		else
		{
			Sprite* m2 = Sprite::create("m2.png");
			m2->setPosition(Vec2(1080 / 2, 720 / 2 + 40));
			this->addChild(m2);
		}
	}

	if (nowPosition.x < -13500)
	{
		if (money > 5500)
		{
			if (a == true)
			{
				rm = rand() % 3 + 1;
				if (rm == 1)
				{
					eat = Sprite::create("eat1.png");
					eat->setAnchorPoint(Vec2(0, 0));
					eat->setPosition(Vec2(15100, 110));
					movedObject->addChild(eat);
					object.push_back(eat);
				}
				else if (rm == 2)
				{
					eat = Sprite::create("eat2.png");
					eat->setAnchorPoint(Vec2(0, 0));
					eat->setPosition(Vec2(15100, 110));
					movedObject->addChild(eat);
					object.push_back(eat);
				}
				else if (rm == 3)
				{
					eat = Sprite::create("eat2.png");
					eat->setAnchorPoint(Vec2(0, 0));
					eat->setPosition(Vec2(15100, 110));
					movedObject->addChild(eat);
					object.push_back(eat);
				}

				a = false;
			}
		}

		nowCharacterPosition.x += 5;
		man->setPosition(nowCharacterPosition);
	}
}

void HelloWorld::Update(float dt)
{
	for (int i = 0; i < object.size(); i++)
	{
		if (object[i] == nullptr)
			continue;

		if (man->getBoundingBox().intersectsRect(object[i]->getBoundingBox()))
		{

			if (nowPosition.x > -13500)
			{

				movedObject->removeChild(coin[check]);
				object.erase(object.begin());
				check++;

				money += 100;
				removeChild(getChildByTag(1));

				sprintf(moneyScore, "%d", money);
				text->setString(moneyScore);
			}
			else
			{
				movedObject->removeChild(eat);
				object.erase(object.begin());

				end = true;
			}
		}
		else if (orux->getBoundingBox().intersectsRect(object[i]->getBoundingBox()))
		{
			movedObject->removeChild(coin[check]);
			object.erase(object.begin());
			check++;
		}
		
	}
}