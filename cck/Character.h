#ifndef CHARACTER_H
#define CHARACTER_H
#include "Sprite.h"
#include "Direction.h"
#include "CharacterStats.h"
#include "PotionEffects.h"
#include <vector>

class Event;
class Character;

class Character : public Sprite
{
private:
	virtual bool isEqual(const Sprite& other) const;
protected:
	CharacterStats stats;
	bool moved = false;
	int health = 0;
	int gold = 0;
	bool neutral = false;

	Position getPosFromDir(Direction dir);
public:
	Character(CharacterStats stats, Position start);
	virtual ~Character();
	virtual std::shared_ptr<Event> Attack(std::shared_ptr<Character> enemy);

	int GetHealth() const;
	int GetStartingHealth() const;
	virtual int GetAttack() const; // need to add potion benefits
	virtual int GetDefense() const; // need to add potion benefits
	int GetDodgeAccuracy() const;
	std::vector<std::string> GetAllergicTo() const;

	void DecrementHealth(int amount);

	virtual std::string GetName() const;
	std::string GetRace() const;
	int GetGold() const;
	void AddGold(int val);
	int PickupGold(int amount);

	bool BeenMoved() const;
	void SetMoved(bool value);
	bool AccessToPath();

	bool GetNeutral() const;
	void SetNeutral(bool val);

	bool GetMoves() const;

	bool Alive();

	int GetGoldValue() const;

	int GetNumAttack(std::string race);

	virtual std::string Die();
};

#endif
