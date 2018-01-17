#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;

const size_t TRIALS = 20000;
const size_t BoardSize = 11;

const unsigned int windowWidth = 1080;
const unsigned int windowHeight = 800;
const std::string windowTitle = "Hex game";

static const Color Gray{ 128,128,128 };
static const float HexRadius = 35;

enum class Player { BLUE, RED, GRAY };
enum class State { Red, Blue, PieRuleAccepted, RedWon, BlueWon };
enum class PieRule { Offered, Accepted, Rejected };