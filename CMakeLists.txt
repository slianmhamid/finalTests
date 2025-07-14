cmake_minimum_required(VERSION 3.29)
project(finalTests)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(Events)
include_directories(Players)

add_executable(finalTests
    Events/Encounter.cpp
    Events/Encounter.h
    Events/Event.h
    Events/PotionsMerchant.h
    Events/SolarEclipse.h
    Events/SpecialEvents.cpp
    Events/SpecialEvents.h
        Players/Archer.cpp
        Players/Archer.h
        Players/CharacterRole.cpp
        Players/CharacterRole.h
        Players/CharacterType.h
        Players/Magician.cpp
        Players/Magician.h
        Players/Player.cpp
        Players/Player.h
        Players/Responsible.cpp
        Players/Responsible.h
        Players/RiskTaking.cpp
        Players/RiskTaking.h
        Players/Warrior.cpp
        Players/Warrior.h
    Utilities.cpp
    Utilities.h
        MatamStory.cpp
        MatamStory.h)
