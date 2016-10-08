#pragma once

#include <string>
#include <future>
#include <utility>

#include <boost/array.hpp>
#include <boost/assert.hpp>
#include <boost/thread.hpp>

namespace stac {
namespace core {

class Worker {
public:
  Worker() = default;
  Worker(Worker const&) = delete;

  template <typename Callable>
  auto work(Callable fn) {
    return std::async(std::launch::async, fn);
  }
}; // Worker
} // core
} // stac
