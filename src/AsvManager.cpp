#include "AsvManager.h"
#include "AsvException.h"

AsvManager::AsvManager(std::unique_ptr<AsvLoader> loader) : loader(std::move(loader)) {}

void AsvManager::PushState(std::string uri)
{
    try{
        this->chain.Add(AsvState::Create(uri, this->loader.get()));
        this->message = "";
    }catch(const AsvException& exc){
        this->message = std::string(exc.what());
    }
}

const std::shared_ptr<AsvState> AsvManager::Current()
{
    return this->chain.Current();
}

const std::string& AsvManager::Message() const
{
    return this->message;
}

void AsvManager::Enter()
{
    try{
        this->chain.Add(this->chain.Current()->Load1(this->Index));
        this->message = "";
    } catch(AsvException& exc){
        this->message = std::string(exc.what());
    }
}

void AsvManager::Prev()
{
    try{
        this->chain.Prev();
        this->message = "";
    } catch(AsvException& exc){
        this->message = std::string(exc.what());
    }
}

void AsvManager::Next()
{
    try{
        this->chain.Next();
        this->message = "";
    } catch(AsvException& exc){
        this->message = std::string(exc.what());
    }
}
