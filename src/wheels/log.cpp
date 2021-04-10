/*============================================================================*/

#include <fstream>
#include <stdexcept>

#include <chrono>
#include <ctime>

#include "log.hpp"

/*============================================================================*/
namespace wheels {
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

namespace chrono = std::chrono;

struct LogContext {
  std::ofstream stream_;
  std::chrono::system_clock::time_point start_time_;
};

////////////////////////////////
static LogContext LOG_CTX;
////////////////////////////////

std::ofstream& Log() {
  if (!LOG_CTX.stream_.is_open()) {
    throw std::runtime_error("log stream is not initialized");
  }

  auto now = chrono::system_clock::now();

  LOG_CTX.stream_ << "\n[" << (now - LOG_CTX.start_time_).count() << "] ";
  return LOG_CTX.stream_;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
namespace log {
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void Init(std::string_view path) {
  if (LOG_CTX.stream_.is_open()) {
    throw std::runtime_error("log stream is already initialized");
  }

  LOG_CTX.stream_.open(path.data());
  if (!LOG_CTX.stream_) {
    throw std::runtime_error("cannot open log");
  }

  LOG_CTX.start_time_ = chrono::system_clock::now();

  auto now_time = chrono::system_clock::to_time_t(LOG_CTX.start_time_);
  LOG_CTX.stream_ << "@ Wheels Log " << std::ctime(&now_time);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void Close() {
  LOG_CTX.stream_.close();
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
}  // namespace log
}  // namespace wheels
/*============================================================================*/

