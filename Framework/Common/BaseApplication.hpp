#pragma once

#include "../Interface/IApplication.hpp"

/*! \class BaseApplication
 *  \brief Brief class description
 *
 *  Detailed description
 */
namespace My {
class BaseApplication : implements IApplication {
public:
  virtual int Initialize();
  virtual void Finalize();
  virtual void Tick();
  virtual bool IsQuit();

protected:
  bool m_IsQuit; /*!< Member description */
};
} // namespace My
