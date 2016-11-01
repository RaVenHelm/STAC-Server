#pragma once

#include <random>

namespace stac { namespace core {

template <typename IntType = int>
auto make_random(IntType min, IntType max)
{
  std::random_device device{};
  std::mt19937 gen{device()};
  std::uniform_int_distribution<IntType> dist{min, max};
  return dist(gen);
} // make_random
} // core
} // stac