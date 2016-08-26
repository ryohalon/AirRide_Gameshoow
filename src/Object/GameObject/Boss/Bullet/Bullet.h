#pragma once
#include "../../GameObject.h"
 

class Boss;
class CharaBase;

class Bullet : public ar::GameObject
{
public:
	Bullet(ci::Vec3f);

	void update() override;

	void draw()override;

	bool isErase();

private:
	int count;
	ci::TriMesh* mesh;
};



class Bullets : public ar::GameObject
{
public:
	void setup() override;
	void update()override;
	void draw()override;

	void setBoss(std::shared_ptr<Boss>);
	void setPlayer(std::shared_ptr<CharaBase>);

private:
	std::list<Bullet> bullets;
	Boss* boss;
	CharaBase* player;

};
