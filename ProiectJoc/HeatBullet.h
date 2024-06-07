#pragma once
#include "Bullet.h"
class HeatBullet : virtual public Bullet
{
private:
	int timer=60;
public:
	HeatBullet(const Bullet& Bullet): Bullet(Bullet) {
		std::cout << "(Copy)HeatBullet facut" << '\n';
	
	};
	
	HeatBullet(int speed, int health, int damage, point Colt, point Traiectorie)
	{
		this->speed = speed;
		this->health = health;
		this->dmg = damage;
		this->Colt = Colt;
		this->trajectory = Traiectorie;

	};
void SeekTarget(std::shared_ptr<Entitate> V)
	{
	//if (timer <= 0)
		//throw std::runtime_error("HeatBulletul nu mai poate da target!");
		//Codul updateaza traiectoria glontului ca sa loveasca targetul
		//Ca sa fie mereu optima
		//Evident acest lucru va fi valabil cat timp timerul este !=0.
		//Dupa ce moare timerul, obiectul devine in esenta un bullet normal
		point Coord1 = *((V->GetCoordinates()).begin());
		point Coord2 = this->Colt;
		Coord1 = Coord1 * (-1);
		Coord2 += Coord1;
		float x1;
		float y1;
		if (Coord2.x < 0)
			x1 = 1;
		else
			if (Coord2.x == 0)
			{
				x1 = 0;
			}
			else
			{
				x1 = -1;
			}

		if (Coord2.y < 0)
			y1 = 1;
		else
			if (Coord2.y == 0)
				y1 = 0;
			else
				y1 = -1;
		trajectory = point{ x1,y1 };
}
virtual void Special(std::shared_ptr<Entitate>P) {
	if(timer>0)
	SeekTarget(P);
};
virtual void draw(sf::RenderWindow& window) const override
{
	//This is a bullet entity.
	//std::cout << "Draw for the address" << this << '\n';
	sf::RectangleShape Glont(sf::Vector2f(5.f, 5.f));
	sf::Color col(139, 0, 0);
	if (timer >= 0)
	Glont.setFillColor(col);
	Glont.setPosition(Colt.x, Colt.y);
	window.draw(Glont);
	//Glont.setOutlineColor()
};
void DecreaseTimer()
{
	timer--;
	if (timer == 0)
		this->speed/=2;
}
virtual point MoveEntity(const point& trajectory)  override
{
	//Yea traiectoria e useless:)
	
	point aux = this->trajectory;
	aux = aux*GetMovementFormula();
	Colt += aux;
	//for(int i=0;i<=speed/10;i++)
	//Colt += this->trajectory;
	DecreaseTimer();
	return aux;
};
};