
#include "Encounter.h"
#include "Utilities.h"

Encounter::Encounter(const string &encounter,int combatPower,int loot,int damage)
    : Event(encounter), encounterCombatPower(combatPower),encounterLoot(loot),encounterDamage(damage){}

int Encounter::getEncounterCombatPower()const{
    return encounterCombatPower;
}
int Encounter::getEncounterLoot()const{
    return encounterLoot;
}
int Encounter::getEncounterDamage() const{
    return encounterDamage;
}

string Encounter::getDescription() const {
  return eventName + " (power " + std::to_string(encounterCombatPower) +", loot "+
         std::to_string(encounterLoot) +", damage "+std::to_string(encounterDamage)+")";
}

Snail::Snail(): Encounter("Snail",5,2,10){}

Slime::Slime(): Encounter("Slime",12,5,25){}

Balrog::Balrog() :Encounter("Balrog",15,100,9001){}

int Balrog::applyEffect(Player &player){
    int effect = player.handleEncounterEffect(encounterCombatPower,encounterLoot,encounterDamage);
    encounterCombatPower+=2;
    return effect;
}

Pack::Pack(vector<shared_ptr<Encounter>> encounters):
    Encounter("Pack",0,0,0),packSize(0),balrogsCounter(0){
    pack = encounters;
    for(std::vector<std::shared_ptr<Encounter>>::const_iterator cit = encounters.cbegin();
         cit!= encounters.cend();cit++){
        encounterCombatPower += (*cit)->getEncounterCombatPower();
        encounterDamage += (*cit)->getEncounterDamage();
        encounterLoot += (*cit)->getEncounterLoot();
        packSize++;
        if((*cit)->getEventName() == "Balrog"){
          balrogsCounter++;
        }
    }
}

string Pack::getDescription() const {
    return "Pack of "+std::to_string(packSize) +" members (power " + std::to_string(encounterCombatPower) +
         ", loot "+std::to_string(encounterLoot) +", damage "+std::to_string(encounterDamage)+")";
}

int Encounter::applyEffect(Player &player) {
    return player.handleEncounterEffect(encounterCombatPower,encounterLoot,encounterDamage);
}

string Encounter::getEventEffect(Player &player,int effect) const {
    if(effect == 1){
        return getEncounterWonMessage(player,this->encounterLoot);
    }else if (effect == 0){
        return getEncounterLostMessage(player, this->encounterDamage);
    }
    return " ";
}

int Pack::applyEffect(Player &player) {
    int effect = player.handleEncounterEffect(encounterCombatPower,encounterLoot,encounterDamage);
    encounterCombatPower += (2*balrogsCounter);
    return effect;
}

const std::vector<std::shared_ptr<Encounter>>& Pack::getEncounters() const {
    return pack;
}