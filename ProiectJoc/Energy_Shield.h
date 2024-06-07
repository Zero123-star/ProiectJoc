#pragma once
#include "VirtualEntitati.h"
class EnergyShield : public Entitate
{
private:
	int health = 500;
	static bool Activated;
	static int Cooldown;
	static EnergyShield* inst;
	point Colt = { 0,0 };
	EnergyShield()
	{};
public:
	EnergyShield(const EnergyShield&) = delete;
	EnergyShield& operator=(const EnergyShield&) = delete;
	static int Check()
	{
		if (Activated == 1)
			return 1;
		return 0;
	}
	static EnergyShield* Get()
	{
		if (inst == nullptr)
		{
			inst = new EnergyShield;
			return inst;
		}
	}
	static int CheckCooldown()
	{
		if (Cooldown == 0)
			return 1;
		return 0;

	}
	static void Switch()
	{
		if (Cooldown != 0)
		{
			std::string m = "Cooldown scut!";
			throw(m);
		}
		if (Activated == 0)
			Activated = 1;
		else
			Activated = 0;
	}
	static void RemoveCooldown()
	{
		if (Cooldown > 0)
			Cooldown--;

	}
	float GetDamageFormula() const
	{
		return 1000; //Un scut ar trebui sa distruga in medie orice bullet. Dar nici sa nu fie foarte OP sa distruga toate entitatile inamice? TODO Balance?
	};
	std::vector<point> GetCoordinates() const override
	{
		std::vector<point>Coordonate;
		Coordonate.push_back(Colt);
		return Coordonate;


	}
	 int GetMovementFormula() const override
	{
		return 0;
	}
	virtual int GetHealth() const override
	{
		return health;
	}
	virtual int GetType() override
	{
		return 3;
	};
	virtual point GetVelocity() override
	{
		return { 0,0 };
	}
	point MoveEntity(const point& trajectory) override
	{
		return Colt;

	};
	 void DamageEntity(int damage) override
	{
		 std::cout << "Ai fost aparat de scut!" <<damage <<'\n';
		 health -= damage;
		if (health <= 0)
		{
			health = 500;
			Activated = 0;
			Cooldown = 100;
		}
		};
	 void print(std::ostream& os) const override
	 {
		 os << "Scutul se afla la coordonatele " << Colt<<" si mai are "<<health<<"hp";
	 }
	  void DamageEntities(std::shared_ptr<Entitate>Entitate2) override
	 {
		  this->DamageEntity(Entitate2->GetDamageFormula());
		  Entitate2->DamageEntity(this->GetDamageFormula());

	 };
	  void Special(std::shared_ptr<Entitate> player) override
	 {
		 //Special: O sa urmeze mereu playerul
		  
		
		  Colt = *(player->GetCoordinates().begin());
		  Colt += {-10, -20};
	 };
	  void draw(sf::RenderWindow& window) const override
	  {
		  if (Activated == 1)
		  {
			  sf::RectangleShape sp1(sf::Vector2f(40.f, 10.f));
			  sf::Color col(0, 0, 255);
			  sp1.setFillColor(col);
			  // sf::RectangleShape sp2(sf::Vector2f(20.f, 20.f));
			  sp1.setPosition(Colt.x, Colt.y);
			  window.draw(sp1);
		  }
		 };
};
bool EnergyShield::Activated = 0;
int EnergyShield::Cooldown = 0;
EnergyShield* EnergyShield::inst = nullptr;