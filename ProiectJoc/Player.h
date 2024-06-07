#pragma once
#include "VirtualEntitati.h"
#include "Energy_Shield.h"
class Player : public Entitate
{
private:
	int hp;
	int speed;
	point Colt;
	int cooldown = 0;
public:
	Player(int hp = 150, int speed = 20, point p = { 0,0 }) :hp(hp), speed(speed), Colt(p) {};
	float GetDamageFormula() const override {
		return 1000; //Nava playerului va distruge mereu orice entitate cu care va face coliziune
	 }
	std::vector<point> GetCoordinates() const override 
	{
//		  C*
//		******
//		******
//		  **
		
		std::vector<point>Coordonate;
		
		point p = Colt;
		//p += point{ 1, 0 };
		Coordonate.push_back(p);
		for (int i = 1; i <= 2; i++)
		{

			p += {0, 1};
			Coordonate.push_back(p);
			p += {1, 0};
			Coordonate.push_back(p);
			p += {1, 0};
			Coordonate.push_back(p);
			p += {-3, 0};
			Coordonate.push_back(p);
			p += {-1, 0};
			Coordonate.push_back(p);
			p += {-1, 0};
			Coordonate.push_back(p);
			p += {3, 0};
		}
		p += {0, 1};
		Coordonate.push_back(p);
		p += {-1, 0};
		Coordonate.push_back(p);
		Coordonate.push_back(Colt);
		return Coordonate;
		
		//return Colt;
	}
	int GetMovementFormula() const override 
	{
		return speed;
	}
	int GetHealth()const override
	{
		return hp;
	}
	virtual void Special(std::shared_ptr<Entitate>) {
	
	
	
	};
	 point MoveEntity(const point& trajectory) override 
	 {
		point aux = trajectory;
		//point Colt;
		point mnb = Colt;
		aux = aux * (speed / 10 + 3);
		mnb += aux;
		if (mnb.x < 0 || mnb.y < 0 || mnb.x>1640 || mnb.y>1010)
		{
			std::string mn = "Nu poti iesi din mapa!";
			throw(mn);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
			 for (int i = 0; i <= speed / 30 + 1; i++)
			 {
				 Colt += trajectory;
				// aux += trajectory;
			 }
		 else
			 for (int i = 0; i <= speed / 10 + 2; i++)
			 {
				 Colt += trajectory;
				// aux += trajectory;
			 }
		 return Colt;
		 //return trajectory*speed;
	 }
	 point GetVelocity() override
	 {
		 //point aux = trajectory;
		 return { 0,0 };
	 };

	 void DamageEntity(int damage) override 
	 {
		 this->hp -= damage;

	 }
	 void DamageEntities(std::shared_ptr<Entitate>p) override
	 {
		 this->DamageEntity(p->GetDamageFormula());
		 p->DamageEntity(this->GetDamageFormula());

	 }
	 friend std::ostream& operator<<(std::ostream& os, const Player& Player)
	 {
		 os << "Te afli la coordonatele " << Player.Colt << " mai ai hp " << Player.hp << " ramas"<<'\n';
		 return os;
	 }
	 void print(std::ostream& os) const
	 {
		 os<< *this;
	 }
	 virtual int GetType() override
	 {
		 return 5;
	 };
	 
	 void draw(sf::RenderWindow& window) const override
	 {
		 sf::RectangleShape sp1(sf::Vector2f(20.f,40.f));
		// sf::RectangleShape sp2(sf::Vector2f(20.f, 20.f));
		 sf::RectangleShape sp3(sf::Vector2f(5.f, 5.f));
		 sp1.setPosition(Colt.x, Colt.y);
		// sp2.setPosition(Colt.x, Colt.y - 20);
		 sp3.setPosition(Colt.x, Colt.y);

		 // sp3.setPosition(Colt.x, Colt.y)
		 if (!sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) 
		 {
			 window.draw(sp1);
			// window.draw(sp2);
		 }
		 else
			 window.draw(sp3);

	 };
};