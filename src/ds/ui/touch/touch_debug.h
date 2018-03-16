#pragma once
#ifndef DS_TOUCH_TOUCH_DEBUG
#define DS_TOUCH_TOUCH_DEBUG

#include <unordered_map>
#include <cinder/app/MouseEvent.h>
#include <ds/ui/touch/touch_info.h>
#include <ds/app/engine/engine.h>

namespace ds {
namespace ui {

/**
* \class ds::ui::TouchDebug
* \brief Takes over mouse-to-touch conversion for your app to perform some common multi-touch thingies.
* Hold down shift while clicking with mouse to access 5-finger menu.
* Hold down control to drop a second touch point (to simulate scaling and shit)
*/
class TouchDebug {
public:
	TouchDebug(ds::Engine& enginey);

	void							mouseDown(const ci::app::MouseEvent&);
	void							mouseDrag(const ci::app::MouseEvent&);
	void							mouseUp(const ci::app::MouseEvent&);

	/** The distance between the touches for 5-finger touch simulation (shift-click) */
	void							setFiveTouchRadius(const float fiveTouchRadius) { mFiveTouchRadius = fiveTouchRadius; }

private:

	ds::Engine&						mEngine;
	void							replicate(const ci::app::MouseEvent&, ds::ui::TouchInfo::Phase);

	int								mTouchId;
	int								mNumberOfReplicants;
	bool							mReplicating;

	bool							mTwoTouching;
	ci::ivec2						mTwoTouchDown;

	bool							mDropTouched;
	float							mFiveTouchRadius;
};

} // namespace ui
} // namespace ds

#endif