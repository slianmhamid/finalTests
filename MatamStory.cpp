#include <iostream>
#include <fstream>
#include <string>

#include "MatamStory.h"

#include "Events/Encounter.h"
#include "Events/SolarEclipse.h"
#include "Events/PotionsMerchant.h"

#include "Players/Archer.h"
#include "Players/Warrior.h"
#include "Players/Magician.h"
#include "Players/RiskTaking.h"
#include "Players/Responsible.h"

// Constants used for event count validation
static const int MIN_NUM_EVENT = 2;
// Constants used for player name and count validation
static const int MIN_LEN_NAME = 3;
static const int MAX_LEN_NAME = 15;
static const int MIN_NUM_PLAYERS = 2;
static const int MAX_NUM_PLAYERS = 6;


MatamStory::MatamStory(std::istream& eventsStream, std::istream& playersStream) {
      std::deque<std::string> temp;
      createDequeFromStream(eventsStream,temp);

      /*===== Open and read events file =====*/

      getEventsReady(temp);

      /*===== Open and Read players file =====*/

      getPlayersReady(playersStream);

      // Initialize the game state
      gameWinner = nullptr;
      this->m_turnIndex = 1;
}

void MatamStory::getPlayersReady(std::istream& playersStream) {
      shared_ptr<CharacterRole> role;
      shared_ptr<CharacterType> type;
      string playerName, playerRole, playerType;

      // Read player data line by line
      while (playersStream >> playerName) {
            // Validate player name length
            if (playerName.length() < MIN_LEN_NAME || playerName.length() > MAX_LEN_NAME) {
                  throw std::runtime_error("Invalid Players File");
            }
            // Ensure player name has only alphabet letters
            if (!areLettersApartOfTheAlphabet(playerName)) {
                  throw std::runtime_error("Invalid Players File");
            }
            // Read role and type; validate structure
            if (!(playersStream >> playerRole >> playerType)) {
                  throw std::runtime_error("Invalid Players File");
            }
            try {
                  // Create role and type objects
                  role = std::move(getCharacterRoleReady(playerRole));
                  type = std::move(getCharacterTypeReady(playerType));
                  // Create the player object and add to the list
                  players.push_back(std::make_shared<Player>(Player(playerName, role, type)));

            }catch (...) {
                  throw std::runtime_error("Invalid Players File");
            }
      }
      // Check that number of players is within allowed range
      if (players.size() < MIN_NUM_PLAYERS || players.size() > MAX_NUM_PLAYERS) {
            throw std::runtime_error("Invalid Players File");
      }
}

shared_ptr<CharacterRole> MatamStory::getCharacterRoleReady(const std::string& role) {
      // Return the appropriate role object according to the input string
      if (role == "Warrior") {
            return std::make_shared<Warrior>(Warrior(role));
      }else if (role == "Archer") {
            return std::make_shared<Archer>(Archer(role));
      }else if (role == "Magician") {
            return std::make_shared<Magician>(Magician(role));
      }else {
            throw std::runtime_error("Invalid Players File");
      }
}

shared_ptr<CharacterType> MatamStory::getCharacterTypeReady(const std::string& type) {
      // Return the appropriate type object according to the input string
      if (type == "Responsible") {
            return std::make_shared<Responsible>(Responsible(type));
      }else if (type == "RiskTaking") {
            return std::make_shared<RiskTaking>(RiskTaking(type));
      }else {
            throw std::runtime_error("Invalid Players File");
      }
}

void MatamStory::getEventsReady(std::deque<std::string>& strings) {
      // Parse the event list from deque and build the event vector
      for(int index = 0; index < static_cast<int>(strings.size()); index++){
            // Handle simple event
            if(strings[index] != "Pack"){
                  events.push_back(getNonPackReady(strings[index]));
            } else {
                  // Handle nested or base Pack event
                  events.push_back(getPackReady(strings,index));
                  index--;
            }
      }
      // Validate minimum number of events
      if (events.size() < MIN_NUM_EVENT) {
            throw std::runtime_error("Invalid Events File");
      }
}
std::shared_ptr<Encounter> MatamStory::getEncounterReady(const std::string& event) {
      // Return the appropriate encounter object according to the input string
      if (event == "Snail") {
            return std::make_shared<Snail>();
      } else if (event == "Slime") {
            return std::make_shared<Slime>();
      } else if (event == "Balrog") {
            return std::make_shared<Balrog>();
      } else {
            throw std::runtime_error("Invalid Events File");
      }
}

void MatamStory::createDequeFromStream(std::istream& stream, std::deque<string>& deque) {
      // Read all whitespace-separated words into deque
      string word;
      while (stream >> word) {
            deque.push_back(word);
      }
}

shared_ptr<Event> MatamStory::getNonPackReady(const string& event) {
      // Return the appropriate event object according to the input string
      if(event == "Snail"){
            return std::make_shared<Snail>(Snail());
      } else if(event == "Slime"){
            return std::make_shared<Slime>(Slime());
      } else if(event == "Balrog"){
            return std::make_shared<Balrog>(Balrog());
      } else if(event == "SolarEclipse"){
            return std::make_shared<SolarEclipse>(SolarEclipse());
      } else if(event == "PotionsMerchant"){
            return std::make_shared<PotionsMerchant>(PotionsMerchant());
      }else {
            throw std::runtime_error("Invalid Events File");
      }
}

shared_ptr<Pack> MatamStory::getPackReady(const std::deque<std::string>& deque,int& index) {

      const std::string &eventString = deque[index + 1];

      // Validate formatting of Pack declaration
      for (char letter : eventString) {
            if (letter == '.') {
                  throw std::runtime_error("Invalid Events File");
            }
      }

      // Get size of the pack
      unsigned int packSize = std::stoi(deque[++index]);
      if (packSize < MIN_NUM_EVENT) {
            throw std::runtime_error("Invalid Events File");
      }

      std::vector<std::shared_ptr<Encounter>> packEncounters;
      index++;

      // Process each sub-event inside the pack
      for (unsigned int i = 0; i < packSize; i++) {
            if (index >= static_cast<int>(deque.size())) {
                  throw std::runtime_error("Invalid Events File");
            }
            if (deque[index] == "Pack") {
                  // Recursively handle nested Pack
                  std::shared_ptr<Pack> nestedPack = getPackReady(deque, index);
                  const auto &nestedEncounters = nestedPack->getEncounters();
                  packEncounters.insert(packEncounters.end(), nestedEncounters.begin(), nestedEncounters.end());
            } else {
                  // Add individual Encounter
                  packEncounters.push_back(getEncounterReady(deque[index]));
                  index++;
            }
      }

      return std::make_shared<Pack>(Pack(packEncounters));
}

void MatamStory::playTurn(Player& player) {
      // Select current event based on turn index
      shared_ptr<Event> currentEvent = events[(m_turnIndex - 1) % events.size()];
      // Print details of the current turn
      printTurnDetails(m_turnIndex, player, *currentEvent);
      // Apply the event's effect and get the outcome
      int eventOutcome = currentEvent->applyEffect(player);
      // Print the result based on effect
      printTurnOutcome(currentEvent->getEventEffect(player, eventOutcome));

      // Increment turn index
      m_turnIndex++;
}

void MatamStory::playRound() {

      printRoundStart();

      /*===== Play a turn for each player =====*/
      // Let each active player play a turn
      for (const shared_ptr<Player>& currentPlayer : players) {
            if (currentPlayer->canPlayerPlay()) {
                  playTurn(*currentPlayer);
                  if (currentPlayer->getHealthPoints() <= 0) {
                        currentPlayer->setLifeStatus();
                  }
            }
      }

      printRoundEnd();

      printLeaderBoardMessage();

      /*===== Print leaderboard entry for each player using "printLeaderBoardEntry" =====*/
      // Sort players by leaderboard rules
      std::set<shared_ptr<Player>, CompareTwoPlayers> leaderBoard;
      for (const shared_ptr<Player>& currentPlayer : players) {
            leaderBoard.insert(currentPlayer);
      }

      // Print leaderboard
      unsigned int index = 1;
      for (const shared_ptr<Player>& currentPlayer : leaderBoard) {
            printLeaderBoardEntry(index, *currentPlayer);
            index++;
      }

      // Update current winner
      gameWinner = *leaderBoard.begin();

      printBarrier();
}

bool MatamStory::isGameOver() const {
      /*===== Implement the game over condition =====*/
      // Game over if a player reached max level
      if(gameWinner && gameWinner->hasPlayerReachedMaxLevel()) {
                  return true;
      }
      // Or all players are dead
      return areAllPlayersDead();
}

void MatamStory::play() {
      printStartMessage();

      /*===== Print start message entry for each player using "printStartPlayerEntry" =====*/
      unsigned int index = 1;
      for (const shared_ptr<Player> &player: players) {
            printStartPlayerEntry(index, *player);
            index++;
      }

      printBarrier();

      // Main game loop
      while (!isGameOver()) {
            playRound();
      }

      printGameOver();

      /*===== Print either a "winner" message or "no winner" message =====*/
      if (areAllPlayersDead() && !gameWinner->hasPlayerReachedMaxLevel()) {
            printNoWinners();
      } else {
            printWinner(*gameWinner);
      }
}


// Helper Functions

bool MatamStory::areLettersApartOfTheAlphabet(const std::string& word) {
      // Check each letter is in a-z or A-Z
      for (const auto& letter : word) {
            if (!((letter >= 'a' && letter <= 'z') || (letter >= 'A' && letter <= 'Z'))) {
                  return false;
            }
      }
      return true;
}

bool MatamStory::areAllPlayersDead() const {
      // Return true if all players have 0 HP
      for (const auto& player: players) {
            if (player->getHealthPoints() > 0) {
                  return false;
            }
      }
      return true;
}
