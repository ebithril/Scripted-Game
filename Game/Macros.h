#pragma once

#include <random>

#define RANDOM_FLOAT(aMax, aMin) ((float(rand()) / float(RAND_MAX)) * ((aMax) - (aMin))) + (aMin)
