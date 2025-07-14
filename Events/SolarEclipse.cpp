
#include "SolarEclipse.h"

SolarEclipse::SolarEclipse() : SpecialEvents("SolarEclipse"){}

int SolarEclipse::applyEffect(Player &player){
    return player.getCharacterRole()->applySolarEclipseEffect(player);
}

string SolarEclipse::getEventEffect(Player &player,int effect)const{
    return getSolarEclipseMessage(player,effect);
}