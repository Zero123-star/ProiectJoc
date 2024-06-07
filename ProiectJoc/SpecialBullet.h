#pragma once
#include "Bullet.h"
class SplittingBullet : virtual public Bullet
{
	//Glont special
	//Viteza redusa, dmg redus, extra hp
	//Dupa ce i se termina timerul, o sa se autodistruga si in locul sau o sa spawneze 3 gloante simple
private:
	int timer=50;
public:
	SplittingBullet& operator=(const Bullet& p)
	{
		std::cout << "(SPLITTING_BULLET)A fost creat prin operator de egalitate la adresa "<<this<<'\n';
		this->health = p.health*2;
		this->dmg = p.dmg/2;
		this->Colt = p.Colt;
		this->timer = 5;
		this->speed = std::max(10,p.speed / 2);
		this->trajectory = p.trajectory;
		return *this;
	};
	SplittingBullet(int health, int speed, int dmg, point p, point trajectory)
	{
		std::cout << "(SPLITTING_BULLET)A fost creat prin constructor la adresa"<<this<<'\n';
		TotalNumber++;
		this->health = health;
		this->dmg = dmg;
		this->Colt = p;
		//this->timer = timer;
		this->trajectory = trajectory;
	};
	SplittingBullet(const Bullet& p)
	{
		std::cout << "(SPLITTING_BULLET)A fost creat prin constructor de copiere la adresa " << this << '\n';
		TotalNumber++;
		this->health = p.health * 2;
		this->dmg = p.dmg / 2;
		this->Colt = p.Colt;
		this->timer = 5;
		this->speed = std::max(10, p.speed / 2);
		this->trajectory = p.trajectory;
	}


	virtual void Special(std::shared_ptr<Entitate>) override
	{
		if (timer == 0)
		{
			float y = this->trajectory.y;
			float x = this->trajectory.x;
			point p, p2, p3;
			if (y == 0 && x != 0) {
				 p = { x,1 };
				 p2 = { x,0 };
				 p3 = { x,-1 };
			}
			else
			{
				 p = { 1,y };
				 p2 = { 0,y };
				 p3 = { -1,y };
			}
			//std::cout << "E";
			//Entitate::Entitati.size();
			Entitate::Entitati2.push_back(std::make_shared<Bullet>(10, 10, 10, this->Colt, p));
			Entitate::Entitati2.push_back(std::make_shared<Bullet>(10, 10, 10, this->Colt, p2));
			Entitate::Entitati2.push_back(std::make_shared<Bullet>(10, 10, 10, this->Colt, p3));
			this->health = 0;
		}
	};
	void Split()
	{
		this->health = 0;
		this->dmg = 0;
		this->speed = 0;
	}
	void DecreaseTimer()
	{
		this->timer--;
	}
	point MoveEntity(const point& trajectory) override
	{
		DecreaseTimer();
		for(int i=0;i<=speed/10;i++)
		this->Colt += this->trajectory;
		return Colt;
	};
	void draw(sf::RenderWindow& window) const override
	{
		sf::RectangleShape sp1(sf::Vector2f(20.f, 20.f));
		sf::Color color(0, 255, 255);
		sp1.setFillColor(color);
		sp1.setPosition(Colt.x, Colt.y);
		window.draw(sp1);
	};
	int GetType() override
	{
		return 2;
	};
		 void Print()const
	{
		std::cout << this->health<<' '<<this->dmg<<' '<<this->Colt<<' '<<this->trajectory<<' '<<this->speed;

	}
	~SplittingBullet()
	{
		std::cout << "(SPLITTING_BULLET)A fost distrus la adresa "<<this<<'\n';
		TotalNumber--;
		/*		int y = this->trajectory.y;
point p = { 0,y };
point p2 = { 1,y };
point p3 = { -1,y };
std::cout << "E";
Entitate::Entitati.push_back(std::make_shared<Bullet>(10,10,10,this->Colt, p));
Entitate::Entitati.push_back(std::make_shared<Bullet>(10, 10, 10, this->Colt, p2));
Entitate::Entitati.push_back(std::make_shared<Bullet>(10, 10, 10, this->Colt, p3));
	*/
	};
};
