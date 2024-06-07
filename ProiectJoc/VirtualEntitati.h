#ifndef VIRTUALENTITATI_H
#define VIRTUALENTITATI_H
#include "StructuraPointer.h"
#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>
class Entitate
{
public:


protected:
	static std::vector <std::shared_ptr<Entitate>> Entitati;
	//static std::vector <std::shared_ptr<Entitate>> Entitati
	static std::vector <std::shared_ptr<Entitate>> Entitati2;
	static std::vector <std::shared_ptr<Entitate>> Entitati3;
  static int TotalNumber;
	//static int m;
public:
	//IDEA INTERFATEI:
	//Daca un obiect se poate gasi pe harta, el reprezinta o entitate care poate avea o coliziune intre alte entitati
	//Asta inseamna ca cel mai probabil se poate misca, ar avea o metoda in care poate sa isi ia dmg sau nu, ar putea da dmg la alte entitati 
	//Ajuta mult interfata la DamageEntities, ca asa nu trebuie sa scriu la fiecare clasa un dmg entity in functie de cu cine da collide (ex meteorit cu bullet/player/splitting bullet/etc)
	//
	//


	//Getteri
	virtual float GetDamageFormula() const = 0; 
	virtual std::vector<point> GetCoordinates() const= 0; //In vectorul returnat PRIMUL element reprezinta coltul din stanga sus al entitatii(Variabila colt ce se gaseste la fiecare).   
	virtual int GetMovementFormula() const= 0;
	virtual int GetHealth() const = 0;
	//Getteri 

	virtual point MoveEntity(const point &trajectory)  = 0;
	virtual void DamageEntity(int damage) = 0;
	virtual void print(std::ostream& os) const = 0;
	virtual	void DamageEntities(std::shared_ptr<Entitate>)=0;
	virtual void Special(std::shared_ptr<Entitate>) = 0;
	virtual point GetVelocity() = 0;
	virtual int GetType() = 0;
	static void AdaugaElement(std::shared_ptr<Entitate> Entitatea)
	{
		Entitati.push_back(std::move(Entitatea));
	}
	static std::vector<std::shared_ptr<Entitate>>& ReturneazaVector1()
	{
		return Entitate::Entitati;

	};
	static std::vector<std::shared_ptr<Entitate>>& ReturneazaVector2()
	{
		return Entitate::Entitati2;

	};
	friend std::ostream& operator<<(std::ostream& os, const Entitate& ent) {
		ent.print(os);
		return os;
	}

	//Functii legate de sfml
	virtual void draw(sf::RenderWindow& window) const = 0;
	//Functii legate de sfml
//virtual ~Entitate() ;
};
int Entitate::TotalNumber = 0;
std::vector<std::shared_ptr<Entitate>> Entitate::Entitati;
std::vector<std::shared_ptr<Entitate>> Entitate::Entitati2;
std::vector <std::shared_ptr<Entitate>> Entitate::Entitati3;
#endif // !VIRTUALENTITATI_H
