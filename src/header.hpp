#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#define IMG_PATH "/home/nishan/Desktop/moreAdventure/images"
#include <vector>
#include "character.hpp"
using namespace std;
using namespace sf;
  enum Direction {
        Left,
        Right,
        Up,
        Down
    };

    enum Screen{
      Main_Menu,
      Game_Play,
      Lose,
      Win
    };

