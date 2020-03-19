#include "config.hpp"
ADIEncoder leftencoder (1, 2, true);
ADIEncoder rightencoder (5, 6, false);
ADIEncoder backencoder (3, 4, true);
ADIAnalogIn topLs(7);
ADIAnalogIn bottomLs(8);
Vision vision(5);
Motor intakeR(7,false), intakeL(16,false);
Motor fBar(12, true);
Motor front_L(2, false), front_R(10, true), back_L(9, false), back_R(5, true);
Controller master(E_CONTROLLER_MASTER);
