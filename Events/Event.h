
#pragma once

#include "../Players/Player.h"

class Event {
protected:
    std:: string eventName;
public:
    /**
     * Gets the description of the event
     *
     * @return - the description of the event
    */
    Event(const string &name):eventName(name){}
    virtual string getDescription() const = 0;
    virtual ~Event() = default;
    virtual int applyEffect(Player &player) = 0;
    virtual string getEventEffect(Player &player,int effect) const = 0;
    string getEventName() const{
        return eventName;
    }
};