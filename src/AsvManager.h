#include "AsvChain.h"
#include <vector>

class AsvManager
{
public:
    AsvManager(std::unique_ptr<AsvLoader> loader);
    const AsvState* Current();
    void PushState(std::string uri);
    void Enter();
    void Prev();
    void Next();
    const std::string& Message() const;
    bool CheckUpdate();
    int Index;

private:
    std::string message {};
    AsvChain chain;
    std::unique_ptr<AsvLoader> loader;
    bool updated;
};
