#pragma once
#include "SpecialEvents.h"


class SolarEclipse : public SpecialEvents{
public:
    SolarEclipse() ;
    int applyEffect(Player &player)override;
    string getEventEffect(Player &player,int effect) const override;
};