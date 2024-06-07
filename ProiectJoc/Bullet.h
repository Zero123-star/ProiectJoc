#ifndef BULLET_H
#define BULLET_H
#include "VirtualEntitati.h"
#include "StructuraPointer.h"
#include "Meteorite.h"
#include <exception>
class Bullet : public Entitate
{
protected:
	int health;
	float dmg;
	int speed;
	point Colt;
	point trajectory;
public:
	Bullet(int speed = 10, int dmg = 10, int health = 30, point p = { 1,1 }, point trajectory = { 0,1 }) :health(health), dmg(dmg), speed(speed), Colt(p),trajectory(trajectory) { TotalNumber++; 
	std::cout << "(BULLET)";
	std::cout << "Constructor de build apelat pentru adresa " << this << '\n';
	};
	Bullet(const Bullet& b) : health(b.health), dmg(b.dmg), speed(b.speed), Colt(b.Colt), trajectory(b.trajectory) { TotalNumber++;
	std::cout << "(BULLET)";
	std::cout << "Constructor de copiere apelat pentru adresa " << this << '\n';
	};
	virtual int GetType() override
	{
		return 1;
	};

	Bullet(const Bullet&&b)noexcept: health(b.health), dmg(b.dmg), speed(b.speed), Colt(b.Colt), trajectory(b.trajectory) { TotalNumber++; 
	std::cout << "(BULLET)";
	std::cout << "Constructor de mutare apelat pentru adresa " << this << '\n';
	};
	std::vector<point> GetCoordinates() const override { 
		//Glontul va ocupa un simplu spatiu 
		std::vector<point>Coordonate;
		Coordonate.push_back(Colt);
		return Coordonate;
	};
	void DamageEntity(int damage)override
	{
		health -= damage;
	}
	float GetDamageFormula()const override
	{
		//this->dmg = 5;
		return (float)dmg * speed/10;
	}
	int GetMovementFormula()const override
	{
		//Returneaza viteza entitatii
		return std::max(speed/3,1) * std::max((int)health / 10, 1);

	};
	virtual int GetHealth() const
	{
		return health;
	}

	virtual void Special(std::shared_ptr<Entitate>) {};
	virtual point MoveEntity(const point& trajectory)  
	{
		//Yea traiectoria e useless:)
		point aux = this->trajectory;
		aux = aux * GetMovementFormula();
		Colt += aux;
		return aux;
	};
	virtual point GetVelocity() override
	{
		point aux = this->trajectory;
		aux = aux * GetMovementFormula();
		return aux;

	};
	friend std::ostream& operator<<(std::ostream& os, const Bullet& b)
	{
		
		if (b.Colt.x < 0 || b.Colt.x > 500 || b.Colt.y < 0 || b.Colt.y > 500)
			throw std::runtime_error("Eroare glont, a iesit din mapa, nu se poate face afisarea");
		os << "Glontul cu adresa "<< &b<<" ce se gaseste la coordonatele " << b.Colt << " merge in directia " << b.trajectory << " la o viteza de " << b.speed << " cu dmg posibil : " << b.dmg<<" are hp " << b.health << '\n';
		
	};
	void print(std::ostream& os)const override
	{
		os << *this;
	};
	void DamageEntities(std::shared_ptr<Entitate>Entitate2) override
	{
		//std::cout << "Voi da dmg la bulletul meu care are " << health << " atata din entitatea straina: " << Entitate2->GetDamageFormula()<<"!";
		this->DamageEntity(Entitate2->GetDamageFormula());
		Entitate2->DamageEntity(this->GetDamageFormula());
		//std::cout <<* this;
		//std::cout << * Entitate2;
	};
	virtual void draw(sf::RenderWindow& window) const override
	{
		//This is a bullet entity.
		//std::cout << "Draw for the address" << this << '\n';
		sf::RectangleShape Glont(sf::Vector2f(5.f,5.f));
		sf::Color col(139,0,0);
		Glont.setFillColor(col);
		Glont.setOutlineThickness(0);
		Glont.setPosition(Colt.x, Colt.y);
		window.draw(Glont);
		//Glont.setOutlineColor()
	};
	
	~Bullet()// override
	{
		std::cout << "(BULLET)A fost distrus la adresa " << this << '\n';
		TotalNumber--;
	}
	friend class SplittingBullet;
};

#endif // BULLET_H
