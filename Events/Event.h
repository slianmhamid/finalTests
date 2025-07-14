#pragma once

#include "../Players/Player.h"

/**
 * Abstract base class representing a game event.
 * Specific events (e.g., monster encounters, merchants, special effects)
 * should inherit from this class and implement its pure virtual methods.
 */
class Event {
protected:
      /**
       * The name of the event (used for identification and display).
       */
      std::string eventName;
public:
      /**
       * Constructor
       *
       * @param name - the name/identifier of the event
       */
      Event(const string &name):eventName(name){}

      /**
       * Virtual destructor to allow safe polymorphic deletion.
       */
      virtual ~Event() = default;

      /**
       * Returns the internal name of the event.
       *
       * @return a string representing the event's name
       */
      string getEventName() const{
            return eventName;
      }

      /**
       * Gets the description of the event
       *
       * @return - the description of the event
      */
      virtual string getDescription() const = 0;

      /**
       * Applies the event's effect to a given player.
       * The result depends on the event type and the player's state.
       *
       * @param player - the player affected by the event
       * @return an integer code representing the effect's outcome
       */
      virtual int applyEffect(Player &player) = 0;

      /**
       * Generates a message based on the event outcome and the player state.
       *
       * @param player - the player who experienced the event
       * @param effect - the result code returned by applyEffect
       * @return a string describing what happened to the player
       */
      virtual string getEventEffect(Player &player,int effect) const = 0;

};
