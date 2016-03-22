#include <stdexcept>

class AsvException : public std::runtime_error
{
public:
    AsvException(const std::string& message);
};
