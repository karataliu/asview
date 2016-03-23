#include "AsvManager.h"

AsvManager::AsvManager(std::unique_ptr<AsvLoader> loader) : loader(std::move(loader)) {}
