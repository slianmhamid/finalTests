
#include "PotionsMerchant.h"

PotionsMerchant::PotionsMerchant() : SpecialEvents("PotionsMerchant") {}

int PotionsMerchant::applyEffect(Player &player){
    return player.getCharacterType()->applyPotionsMerchantEffect(player);
}

string PotionsMerchant::getEventEffect(Player &player,int effect)const{
    return getPotionsPurchaseMessage(player,effect);
}