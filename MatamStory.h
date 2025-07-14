#pragma once

#include <iostream>

#include <vector>
#include <set>
#include <list>
#include <deque>
#include <memory>


#include "Utilities.h"
#include "Players/Player.h"
#include "Events/Event.h"
#include "Events/Encounter.h"

using std::shared_ptr;
using std::vector;
using std::list;


/**
 * Functor to compare two players using  (>) operator
 */
struct CompareTwoPlayers {
      bool operator()(const shared_ptr<Player>& player1, const shared_ptr<Player>& player2) const {
            return *player1 > *player2;
      }
};

/**
 * The MatamStory class handles the game logic, including
 * player management, event processing, and turn/round control.
 */
class MatamStory {

public:

      /**
       * Constructor of MatamStory class
       *
       * @param eventsStream - events input stream (file)
       * @param playersStream - players input stream (file)
       *
       * @return - MatamStory object with the given events and players
       *
      */
      MatamStory(std::istream& eventsStream, std::istream& playersStream);


      /**
       * Initializes players from the given input stream and populates the players list.
       *
       * @param playersStream - input stream with player information
       */
      void getPlayersReady(std::istream& playersStream);

      /**
       * Returns a shared pointer to a CharacterRole object matching the given role name.
       *
       * @param role - string representing the role name (e.g., "Warrior")
       * @return shared_ptr to the corresponding CharacterRole
       */
      shared_ptr<CharacterRole> getCharacterRoleReady(const std::string& role);

      /**
       * Returns a shared pointer to a CharacterType object matching the given type name.
       *
       * @param type - string representing the character type (e.g., "Responsible")
       * @return shared_ptr to the corresponding CharacterType
       */
      shared_ptr<CharacterType> getCharacterTypeReady(const std::string& type);

      /**
       * Checks if a word contains only English alphabet letters.
       *
       * @param word - the word to validate
       * @return true if valid, false otherwise
       */
      bool areLettersApartOfTheAlphabet(const std::string& word);


      /**
       * Parses a list of event strings and fills the event queue accordingly.
       *
       * @param strings - deque of strings representing event data
       */
      void getEventsReady(std::deque<string> &strings);

      /**
       * Creates a specific Encounter object from a string description.
       *
       * @param event - string representing the event type
       * @return shared_ptr to the constructed Encounter
       */
      std::shared_ptr<Encounter> getEncounterReady(const std::string& event);

      /**
       * Populates a deque of strings by reading lines from an input stream.
       *
       * @param stream - input stream to read from
       * @param strings - deque to be populated with the lines from the stream
       */
      void createDequeFromStream(std::istream &stream, std::deque<std::string> &strings);

      /**
       * Returns a non-pack event (like a single monster) from a string.
       *
       * @param event - string description of the event
       * @return shared_ptr to the Event
       */
      shared_ptr<Event> getNonPackReady(const std::string& event);

      /**
       * Builds a Pack event from the deque of event descriptions starting at a given index.
       *
       * @param deque - deque of event strings
       * @param index - reference to the current index in the deque
       * @return shared_ptr to the Pack
       */
      shared_ptr<Pack> getPackReady(const std::deque<std::string> &deque,int &index);

      /**
       * Checks if all players are dead.
       *
       * @return true if all players have 0 health, false otherwise
       */
      bool areAllPlayersDead() const;

      /**
       * Plays the entire game
       *
       * @return - void
      */
      void play();

private:
      /**
       * Vector containing all game events, in order.
       */
      vector<shared_ptr<Event>> events;

      /**
       * Vector of all players participating in the game.
       */
      vector<shared_ptr<Player>> players;

      /**
       * A pointer to the winning player, if one exists.
       */
      shared_ptr<Player> gameWinner;

      /**
       * Current turn index (incremented every turn).
       */
      unsigned int m_turnIndex;


      /**
       * Playes a single turn for a player
       *
       * @param player - the player to play the turn for
       *
       * @return - void
      */
      void playTurn(Player& player);

      /**
       * Plays a single round of the game
       *
       * @return - void
      */
      void playRound();

      /**
       * Checks if the game is over
       *
       * @return - true if the game is over, false otherwise
      */
      bool isGameOver() const;
};
