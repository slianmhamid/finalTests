#pragma once

#include "Event.h"

#include <vector>
#include <memory>
using namespace std;

class Encounter : public Event{
public:
    Encounter(const string& encounter,int combatPower,int loot,int damage);
    int getEncounterCombatPower()const;
    int getEncounterLoot()const;
    int getEncounterDamage()const;
    string getDescription() const override;
    virtual int applyEffect(Player& player) override;
    string getEventEffect(Player& player,int effect)const override;

protected:
    int encounterCombatPower;
    int encounterLoot;
    int encounterDamage;

};

class Snail : public Encounter{
public:
    Snail();
};

class Slime : public Encounter{
public:
    Slime();
};

class Balrog : public Encounter{
public:
    Balrog();
    int applyEffect(Player& player) override;

};
class Pack : public Encounter{
public:
    Pack(vector<shared_ptr<Encounter>> encounters);
    string getDescription() const override;
    int applyEffect(Player &player) override;
    const vector<std::shared_ptr<Encounter>>& getEncounters() const;

private:
    int packSize;
    int balrogsCounter;
    std::vector<std::shared_ptr<Encounter>> pack;
};