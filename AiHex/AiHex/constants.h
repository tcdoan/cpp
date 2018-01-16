#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;

const size_t BoardSize = 11;

const unsigned int windowWidth = 1024;
const unsigned int windowHeight = 768;
const std::string windowTitle = "Hex game";

static const Color Gray{ 128,128,128 };
static const float HexRadius = 50;

enum class Player { BLUE, RED, GRAY };
enum class State { Red, Blue, RedWon, BlueWon };