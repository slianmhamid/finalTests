#pragma once

#include <string>
#include <memory>

#include "CharacterRole.h"
#include "CharacterType.h"

using std::string;

/**
 * Represents a player in the game, combining a role (e.g., Warrior)
 * and a type (e.g., Responsible). Maintains stats such as level,
 * force, health, and coins, and handles combat and game state logic.
 */
class Player {
public:

      /**
       * Constructor
       *
       * @param name - the player's name
       * @param role - shared_ptr to the character role (e.g., Warrior)
       * @param type - shared_ptr to the character type (e.g., Responsible)
       */
      Player(const string& name,
            std::shared_ptr<CharacterRole> role,
            std::shared_ptr<CharacterType> type);

      /**
       * Virtual destructor to ensure proper cleanup in case of inheritance.
       */
      virtual ~Player() = default;

      /**
       * Copy constructor.
       * Creates a new Player object as a copy of an existing one.
       */
      Player(const Player&) = default;

      /**
       * Copy assignment operator.
       * Copies the data from one Player object to another.
       *
       * @param source - the Player object to copy from
       * @return reference to the updated Player object
       */
      Player& operator=(const Player& source) = default;

      /**
       * @return the player's name
       */
      string getName() const;

      /**
       * @return the player's current level
       */
      int getLevel() const;

      /**
       * @return the player's combat force
       */
      int getForce() const;

      /**
       * @return the player's current health points (HP)
       */
      int getHealthPoints() const;

      /**
       * @return the player's maximum HP
       */
      int getMaxHP() const;

      /**
       * @return the number of coins the player currently has
       */
      int getCoins() const;

      /**
       * @return a string summary of the player's type and role
       */
      string getDescription() const;


      /**
       * @return the name of the player's role (e.g., "Warrior")
       */
      string getRoleName() const;

      /**
       * @return the name of the player's type (e.g., "Responsible")
       */
      string getTypeName() const;

      /**
       * @return the shared_ptr to the player's CharacterRole
       */
      std::shared_ptr<CharacterRole> getCharacterRole() const;

      /**
       * @return the shared_ptr to the player's CharacterType
       */
      std::shared_ptr<CharacterType> getCharacterType() const;


      /**
       * Calculates and returns the player's effective combat power,
       * possibly influenced by role-based modifiers (e.g., Solar Eclipse).
       */
      int getCombatPower() const;

      /**
       * Increases the player's level by one (up to max level)
       */
      void levelUp();

      /**
       * Heals the player by a given amount (without exceeding max HP)
       */
      void heal(int health);

      /**
       * Damages the player by a given amount (can reach zero)
       */
      void damage(int damage);

      /**
       * Adds loot (coins) to the player's total
       */
      void addLoot(int loot);

      /**
       * Sets the player's force to a new value
       */
      void setForce(int force);

      /**
       * Sets the player's coins to a new value
       */
      void setCoins(int coins);


      /**
       * Marks the player as dead (sets aliveOrDead = false)
       */
      void setLifeStatus();

      /**
       * Checks if the player is alive and can take a turn
       *
       * @return true if the player is alive
       */
      bool canPlayerPlay() const;

      /**
       * Checks if the player has reached the maximum allowed level
       *
       * @return true if max level reached
       */
      bool hasPlayerReachedMaxLevel() const;


      /**
       * Compares two players based on their levels, force, and name
       * Used in leaderboard sorting.
       *
       * @return true if this player ranks higher than the other
       */
      bool operator>(const Player& source) const;

      /**
       * Applies an encounter effect (e.g., from a monster or merchant)
       *
       * @param combatPower - encounter's required combat power
       * @param loot - coins to gain if successful
       * @param damage - HP to lose if failed
       * @return int representing the encounter outcome
       */
      int handleEncounterEffect(int combatPower, int loot, int damage);

private:

      // ----- Player state -----

      string playerName;   ///< The name of the player
      int playerLevel;     ///< Current player level (starts at 1)
      int playerForce;     ///< Base combat power
      int playerCurrentHP; ///< Current health points
      int playerMaxHP;     ///< Maximum health points
      int playerCoins;     ///< Number of coins the player has
      bool aliveOrDead;    ///< Whether the player is alive (true) or dead (false)

      // ----- Player type and role -----

      std::shared_ptr<CharacterRole> playerRole; ///< Player's role (affects combat)
      std::shared_ptr<CharacterType> playerType; ///< Player's type (affects healing/coins)

};
