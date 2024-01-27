#pragma once

#include <iostream>
#include <ctime>
#include <thread>
#include <chrono>
#include <vector>
#include <unistd.h>

const char BOARD_HOR_SIDE = '-';
const char BOARD_VER_SIDE = '|';
const char BOARD_CORNER = '+';
const char BOARD_CHAR = ' ';

const char SNAKE_HEAD = 'O';
const char SNAKE_BODY = 'o';
const char SNAKE_TAIL = '*';

const char FOOD = '@';

using board = char**;

struct snake{
    size_t x=5,y=5;
    char state;
};