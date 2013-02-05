#pragma once
#ifndef DS_APP_AUTOUPDATE_H_
#define DS_APP_AUTOUPDATE_H_

#include <vector>
#include <Poco/Timestamp.h>

namespace ds {
class AutoUpdateList;
namespace ui {
class SpriteEngine;
}

/**
 * \class ds::AutoUpdate
 * Automatically run an update operation. Handle managing myself
 * in my containing list.
 */
class AutoUpdate {
  public:
    AutoUpdate(ds::ui::SpriteEngine&);
    ~AutoUpdate();

  protected:
	  virtual void					update(const Poco::Timestamp::TimeVal&) = 0;

  private:
    friend class AutoUpdateList;
    AutoUpdate();

    AutoUpdateList&       mOwner;
};

} // namespace ds

#endif // DS_APP_AUTOUPDATE_H_