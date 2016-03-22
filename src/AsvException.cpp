#include "AsvException.h"

AsvException::AsvException(const std::string& message) : runtime_error(message) {}
