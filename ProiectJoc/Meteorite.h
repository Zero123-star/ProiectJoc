#pragma once
#include "StructuraPointer.h"
#include "VirtualEntitati.h"
#include "Bullet.h"
#include <string>
#include <vector>
#include <iostream>
#include <memory>
class Meteorite : public Entitate
{
protected:
	int hp;
	int speed;
	point Coordonate;
	const int mb;
	point trajectory;
	int Cooldown = 15;
public:
	Meteorite(int hp = 15, int speed = 10, point punct = { 5, 4 }, point trajectory = { 0,-1 }) : hp(hp), speed(speed), Coordonate(punct), mb(hp^ speed), trajectory(trajectory)
	{
		//TotalNumber++;
		//AdaugaElement(std::shared_ptr<Entitate>(this));
	};
	Meteorite(const Meteorite& M) : hp(M.hp), speed(M.speed), Coordonate(M.Coordonate), mb(hp^ speed), trajectory(M.trajectory){
		//TotalNumber++;
	};
	float GetDamageFormula()const override
	{
		return (int)speed * hp;
	};
	std::vector<point> GetCoordinates()const override 
	{
		std::vector<point>Coord;
		Coord.push_back(Coordonate);
		return Coord;

	};
	int GetHealth() const override
	{
		return hp;
	}
	int GetMovementFormula()const override 
	{
		return speed / 10;
	};
	point GetVelocity() override
	{
		point p = this->trajectory;
		p = p * GetMovementFormula();
		return p;
	};
	point MoveEntity(const point& trajectory) override 
	{
		point p = this->trajectory;
		p = p * GetMovementFormula();
		std::cout << p;
		Coordonate +=p;
		std::cout << "Noile coordonate pentru " << this << " sunt:";
		std::cout << Coordonate<<'\n';
		return Coordonate;
	}
	void DamageEntity(int value)override
	{
		this->hp -= value;
	}
	void DamageEntities(std::shared_ptr<Entitate>Entitate2) override
	{
		this->DamageEntity(Entitate2->GetDamageFormula());
		Entitate2->DamageEntity(this->GetDamageFormula());
	};
	void print(std::ostream& os) const override
	{
		//bd();
		os << *this;
	};
	int GetType() override
	{
		return 3;
	};
	friend std::ostream& operator<<(std::ostream& os, const Meteorite& Mt)
	{
		std::cout << "Meteoritul care se gaseste la adresa " << &Mt << " are coordonatele " << Mt.Coordonate << " si are " << Mt.hp << " hp si " << Mt.speed << " viteza " <<Mt.mb<<" id"<< '\n';

		return os;
	}
	void draw(sf::RenderWindow& window) const override
	{
		sf::RectangleShape sp1(sf::Vector2f(30.f, 40.f));
		sp1.setPosition(Coordonate.x, Coordonate.y);
			window.draw(sp1);
	};
	virtual void Special(std::shared_ptr<Entitate> V) {
		if (Cooldown == 0)
		{
			point Coord1 = *((V->GetCoordinates()).begin());
			point Coord2 = this->Coordonate;
			Coord1 = Coord1 *( - 1);
			Coord2 += Coord1;
			//Coord2 += {0, -20};
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
			point pd = this->Coordonate;
			pd += {0, 40};
			Entitate::Entitati2.push_back(std::make_shared<Bullet>(10, 10, 30, pd, trajectory));
			for (int i = 5; i <= 25; i += 10)
			{
				pd += {5, 0};
				Entitate::Entitati2.push_back(std::make_shared<Bullet>(10, 10, 30, pd, trajectory));
			}
			Cooldown = 100;
		}
		else
			Cooldown--;
	};
	~Meteorite() //override
	{
		//std::cout << this;
	};

};

