#include <iostream>
#include <vector>
#include <functional>
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "StructuraPointer.h"
#include "VirtualEntitati.h"
#include "Meteorite.h"
#include "Bullet.h"
#include "SpecialBullet.h"
#include "HeatBullet.h"
#include "Player.h"
#include "Energy_Shield.h"
#include "Game.h"
#include <ctime>
#include <cstdlib>
point generateRandomPoint() {

	// Generate random x and y values between 1 and 500
	int randomX = std::rand() % 500 + 1;
	int randomY = std::rand() % 500 + 1;

	// Create a point struct with the random values
	point randomPoint;
	randomPoint.x = randomX;
	randomPoint.y = randomY;

	return randomPoint;
}
void CreateMeteorites(std::vector<std::shared_ptr<Entitate>>& Entitati)
{
	for (int i = 1; i <= 10; i++)
	{
		point p = generateRandomPoint();
		point c = generateRandomPoint();
		int x = c.x;
		x = x % 3;
		if (x == 0)
			c.x = 0;
		else
			if (x == 1)
				c.x = 1;
			else
				c.x = -1;
		int y = c.y;
		y = y % 3;
		if (y == 0)
			c.y = 0;
		else
			if (y == 1)
				c.y = 1;
			else
				c.y = -1;
		if (c == point{ 0, 0 })
			c = { 1,0 };
		//Bullet B((10 * i) % 40, 10, 10, p, c);
		Entitati.push_back(std::make_shared<Meteorite>(20,10,p,c));
	};


};
void CreateBullets(std::vector<std::shared_ptr<Entitate>>& Entitati)
{
for (int i = 1; i <= 10; i++)
{
	point p = generateRandomPoint();
	point c = generateRandomPoint();
	int x = c.x;
	x = x % 3;
	if (x == 0)
		c.x = 0;
	else
		if (x == 1)
			c.x = 1;
		else
			c.x = -1;
	int y = c.y;
	y = y % 3;
	if (y == 0)
	c.y = 0;
	else
		if (y == 1)
	c.y = 1;
		else
	c.y = -1;
	if (c == point {0, 0})
		c = { 1,0 };
	Bullet B((10 * i) % 40, 10, 10, p, c);
	Entitati.push_back(std::make_shared<HeatBullet>(B));
};
}
void EliminateDeadEntities(std::vector<std::shared_ptr<Entitate>>& Entitati, std::shared_ptr<Entitate>&p,sf::RenderWindow& fereastra)
{
	for (auto i = Entitati.begin(); i != Entitati.end(); i++)
	{
		point pc = *((*i)->GetCoordinates().begin());
		if ((*i)->GetHealth() <= 0 || pc.x > 1680 || pc.x < 0 || pc.y>1050 || pc.y < 0)
		{
			i = Entitati.erase(i);
			if (i == Entitati.end())
				break;
		}
	else
	{
	if((*i)->GetType()!=5)
	{ 
	(*i)->draw(fereastra);
	(*i)->MoveEntity({ 1,1 });
	(*i)->Special(p);
	}
	}
	}
}
float SmartCollision(const AABB& Obiect1, const AABB& Obiect2, float vx1, float vy1, float vx2, float vy2)
{
	//Doamne ajuta-ma ca am scris algoritmul asta la miezu noptii 
	//Dupa ce am gasit ideea sa explicata pe web
	//Returneaza timpul in care s a facut o coliziune. 1->Nu e coliziune. (0,1) este. 0.5 < 0.6. A fost facuta intai coliziunea 0.5 
	//std::cout << Obiect1.x << 'x' << Obiect1.y << ' ' << Obiect2.x << 'x' << Obiect2.y << '\n';
float vx=(vx1 - vx2);
float vy=(vy1 - vy2);
float Xintrare, Yintrare;
float Xiesire, Yiesire;
if (vx > 0.0f)
{
	Xintrare = Obiect2.x - (Obiect1.x + Obiect1.width);
	Xiesire = (Obiect2.x + Obiect2.width) - Obiect1.x;
}
else
{
	Xintrare= (Obiect2.x + Obiect2.width) - Obiect1.x;
	Xiesire= Obiect2.x - (Obiect1.x + Obiect1.width);
}
if (vy > 0.0f)
{
	Yintrare = Obiect2.y - (Obiect1.y + Obiect1.height);
	Yiesire = (Obiect2.y + Obiect2.height) - Obiect1.y;
}
else
{
	Yiesire = Obiect2.y - (Obiect1.y + Obiect1.height);
	Yintrare = (Obiect2.y + Obiect2.height) - Obiect1.y;
}
float XTintrare,YTintrare , XTiesire, YTiesire;
if (vx == 0.0f)
{
	XTintrare = -std::numeric_limits<float>::infinity();
	XTiesire= std::numeric_limits<float>::infinity();
}
else
{
	XTintrare = Xintrare / vx;
	XTiesire = Xiesire / vx;
}
if (vy == 0.0f)
{
YTintrare= std::numeric_limits<float>::infinity();
YTiesire= -std::numeric_limits<float>::infinity();

}
else
{
	YTintrare = Yintrare / vy;
	YTiesire = Yiesire / vy;
}
//XTintrare < 0.0f && YTintrare < 0.0f
float TimpIntrare = std::max(XTintrare, YTintrare);
float TimpIesire = std::min(YTiesire, XTiesire);
if (TimpIntrare > TimpIesire || XTintrare < 0.0f && YTintrare < 0.0f || XTintrare>1.0f || YTintrare>1.0f)
return 1;
else
return TimpIntrare;
};

int main()
{
	//static std::vector <std::shared_ptr<Entitate>> Entitati; The form of the variable. The static variable is sored inside the Entitate interface. Meteorite is a derivate class of the interface
	/*std::unordered_map<point, std::vector<std::weak_ptr<Entitate>>>ump;
	Entitate::Entitati.push_back(std::make_shared<Meteorite>(5,10));
	Entitate::Entitati.push_back(std::make_shared<Meteorite>());
	Entitate::Entitati.push_back(std::make_shared<Meteorite>());
	Entitate::Entitati.push_back(std::make_shared<Meteorite>());
	Entitate::Entitati.push_back(std::make_shared<Meteorite>());
	for (auto i = Entitate::Entitati.begin(); i != Entitate::Entitati.end(); i++)
	{
		std::cout << **i;
		(*i)->MoveEntity({ 1,1 });
		point p = (*i)->GetCoordinates();
		ump[p].push_back(*i);//All i's will end up at the coordinates 6,5 since they initialize with the same coordinates
		std::cout << (*i)->GetCoordinates() << '\n';
		//std::cout << ump[p].size();
		p += {1, 0};
		//std::cout << p.x << p.y<<' ';
		ump[p].push_back(*i);
		//std::cout << ump[{7, 5}].size();
		p += {0, 1};
		ump[p].push_back(*i);
		//std::cout << ump[{7, 5}].size();
		p += {-1, 0};
		ump[p].push_back(*i);
		//std::cout << ump[{7, 5}].size();
		//std::cout << ump[{6, 5}].size() << "si" << ump[{7, 5}].size();
	}
	auto i = Entitate::Entitati.begin();
	std::cout << i->unique();
	i->reset();
	for (auto i = ump[{6, 5}].begin(); i != ump[{6, 5}].end(); i++)
	{
		auto sp = i->lock();
		std::cout << sp<<'\n';
	}
		/*for (auto i = ump[{6, 5}].begin(); i != ump[{6, 5}].end(); i++)
	{
		auto sp = i->lock(); 
		{
			sp->DamageEntity(5);
			for (auto j = ump[{7, 5}].begin(); j != ump[{7, 5}].end(); j++)
			{
				//std::cout << "!@#";
				auto mn = j->lock();
				std::cout << mn.get() << " cu " << sp.get() << '\n';
				//std::cout << *mn;
				//std::cout << mn.get();
				if (mn.get() == sp.get())
				{
					std::cout << "AM GASIT ELEMENTUL IN COLT DREAPTA SUS SI L AM STERS" << '\n';
					ump[{7, 5}].erase(j);
					mn->DamageEntity(4);
					break;
				}
			}
			for (auto j = ump[{7, 6}].begin(); j != ump[{7, 6}].end(); j++)
			{
				auto mn = j->lock();
				if (&*mn == &*sp)
				{
					std::cout << "AM GASIT ELEMENTUL IN COLT DREAPTA JOS" << '\n';
					ump[{7, 6}].erase(j);
					break;
				}
			}
			for (auto j = ump[{6, 6}].begin(); j != ump[{6, 6}].end(); j++)
			{
				auto mn = j->lock();
				if (&*mn == &*sp)
				{
					std::cout << "AM GASIT ELEMENTUL IN COLT STANGA JOS" << '\n';
					ump[{6, 6}].erase(j);
					break;
				}
			}
			std::cout << "AM FINALIZAT DE STERS URMATORUL ELEMENT:";
				std::cout << *sp;
				sp->DamageEntity(5);
				ump[{6, 5}].erase(i);
				break;
		};
		//std::cout << "Aici";
	}
	for (auto i = Entitate::Entitati.begin(); i != Entitate::Entitati.end(); i++)
	{
		if(*i!=nullptr)
		std::cout << **i;

	}
	std::cout << Entitate::TotalNumber;
*/
	/**
	std::shared_ptr<Entitate> i;
	//i = std::make_shared<Bullet>(5, 5, 5, point{ 1,1 }, point{ 1,2 });
	Bullet p(20);
	std::cout << p;
	i = std::make_shared<SplittingBullet>(p);
	std::cout << *i;
	//std::cout << i->GetDamageFormula();
	p.DamageEntities(i);
	//std::cout << i;
	//std::cout << "ASD";
	try {
		i->MoveEntity({ 1,1 });

		std::cout << *i;
	}
	catch (const std::runtime_error& e)
	{
		std::cout << e.what();
	}*/
std::vector<std::shared_ptr<Entitate>>& Entitati=Entitate::ReturneazaVector1();
std::vector<std::shared_ptr<Entitate>>& Entitati2 = Entitate::ReturneazaVector2();
srand(static_cast<unsigned>(time(nullptr)));
std::shared_ptr<Entitate>p;
p = std::make_shared<Player>(1200000, 100, point{ 125,125 });
EnergyShield* v = EnergyShield::Get();
std::cout<<v->GetHealth();
v->Special(p);
std::vector<std::shared_ptr<Entitate>>Entitati3;
Entitati3.push_back(p);
sf::RenderWindow fereastra(sf::VideoMode(1680, 1050), "Exercitiu", sf::Style::Default);
fereastra.setFramerateLimit(30);
while (fereastra.isOpen())
{
	sf::Event event;
	while (fereastra.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			fereastra.close();
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Z)
			{
				point R = *(p->GetCoordinates().begin());
				R += {-15, -15};
				Entitati.push_back(std::make_shared<SplittingBullet>(30, 30, 30, R, point{ 0,-1 }));
			}
			else if (event.key.code == sf::Keyboard::X)
			{
				CreateBullets(Entitati);
			}
			else if (event.key.code == sf::Keyboard::V)
			{
				//std::cout << "AICI";
				try {
					EnergyShield::Switch();
					}
				catch (std::string p)
				{
					std::cout << p;
				}
				}
			else if (event.key.code == sf::Keyboard::M)
			{
				CreateMeteorites(Entitati3);
			};
		}
		
	}
	bool W = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
	bool A = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
	bool S = sf::Keyboard::isKeyPressed(sf::Keyboard::S);
	bool D = sf::Keyboard::isKeyPressed(sf::Keyboard::D);
	bool Z = sf::Keyboard::isKeyPressed(sf::Keyboard::Z);
	if (W && A)
	{
		try {
			p->MoveEntity({ -1,-1 });
		}
		catch (std::string m)
		{
			std::cout << m;
		}
	}
	else if (W && D)
	{
		try {
			p->MoveEntity({ 1,-1 });
		}
		catch (std::string m)
		{
			std::cout << m;
		}
	}
	else if (S && A)
	{
		try {
			p->MoveEntity({ -1,1 });
		}
		catch (std::string m)
		{
			std::cout << m;
		}

	}
	else if (S && D)
		{
		try {
			p->MoveEntity({ 1,1 });
		}
		catch (std::string m)
		{
			std::cout << m;
		}
		}
	else if (W)
	{
		try {
			p->MoveEntity({ 0,-1 });
		}
		catch (std::string m)
		{
			std::cout << m;
		}
	}
	else if (A)
	{
		try {
			p->MoveEntity({ -1,0 });
		}
		catch (std::string m)
		{
			std::cout << m;
		}
	}
	else if (D)
	{
		try {
			p->MoveEntity({ 1,0 });
		}
		catch (std::string m)
		{
			std::cout << m;
		}
	}
	else if (S)
	{
		try {
			p->MoveEntity({ 0,1 });
		}
		catch (std::string m)
		{
			std::cout << m;
		}
	}
	fereastra.clear();
	if(1>0)
	{ 
	
		EliminateDeadEntities(Entitati, p, fereastra);
		EliminateDeadEntities(Entitati3, p, fereastra);
		/**for (auto i = Entitati.begin(); i != Entitati.end(); i++)
	{
		point pc = *(*i)->GetCoordinates().begin();
		if (pc.x > 1680 || pc.x < 0 || pc.y>1050 || pc.y < 0 || (*i)->GetHealth()<=0)
		{
			i = Entitati.erase(i);
			if (i == Entitati.end())
				break;
		}
		else
		{
			(*i)->draw(fereastra);
			//auto z=dynamic_cast<HeatBullet&>(**i);
			
			(*i)->MoveEntity({ 1,1 });
			(*i)->Special(p);
		}
		//	std::cout << "!@#";
	}*/
	if (EnergyShield::Check() == 1 && EnergyShield::CheckCooldown() == 1)
	{
		//std::cout << "DA";
		v->Special(p);
		v->draw(fereastra);
	}
	else
		EnergyShield::RemoveCooldown();
	}
	for (auto i = Entitati.begin(); i != Entitati.end(); i++)
	{
		AABB b3({ 0,0 }, 1, 1);
		point i1 = *(*i)->GetCoordinates().begin();
		if ((*i)->GetType() == 1)
		{
			AABB b1(i1, 5, 5);
			b3 = b1;
		}
		else
		{
			AABB b1(i1, 20, 20);
			b3 = b1;
		}
		if (EnergyShield::Check() == 1)
		{
		//AABB b5({ 0,0 }, 1, 1);
			point j2 = *(v->GetCoordinates().begin());
			AABB b5(j2, 40, 10);
			point aux2 = (*i)->GetVelocity();
			if (SmartCollision(b3, b5, aux2.x, aux2.y, 0, 0) != 1 || b3.Coliziune(b5) == 1)
				v->DamageEntities(*i);
		}

		for (auto j = Entitati3.begin(); j != Entitati3.end(); j++)
		{
			if ((*j)->GetType() != (*i)->GetType() && (*i)->GetHealth() > 0 && (*j)->GetHealth() > 0)
			{
				//std::cout << "HERE";
				point j1;
				AABB b4({ 0,0 }, 1, 1);
				j1 = *(*j)->GetCoordinates().begin();
					AABB b2(j1, 20, 40);
					b4 = b2;
				

				point aux1 = (*i)->GetVelocity();
				if (SmartCollision(b3, b4, aux1.x, aux1.y, 0, 0) != 1 || b4.Coliziune(b3) == 1)
					(*i)->DamageEntities(*j);


			};
		}
		}
	if(Entitati2.size()!=0)
		for (auto i = Entitati2.begin(); i != Entitati2.end(); i++)
		{
			Entitati.push_back(std::move(*i));
		}
	Entitati2.clear();
	//std::cout << "A";
	p->draw(fereastra);
	fereastra.display();
}
std::cout <<"AI HP-UL URMATOR"<< p->GetHealth();

	return 0;
}
