#pragma once
#include "SpecialEvents.h"

class PotionsMerchant: public SpecialEvents{
public:
    PotionsMerchant();
    int applyEffect(Player &player)override;
    string getEventEffect(Player &player,int effect) const override;
};