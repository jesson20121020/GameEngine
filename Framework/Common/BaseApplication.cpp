#include "BaseApplication.hpp"

using namespace My;

int BaseApplication::Initialize() {
  m_IsQuit = false;
  return 0;
}

void BaseApplication::Finalize() {}

void BaseApplication::Tick() {}

bool BaseApplication::IsQuit() { return m_IsQuit; }