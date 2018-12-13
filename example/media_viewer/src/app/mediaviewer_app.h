#ifndef _MEDIAVIEWER_APP_H_
#define _MEDIAVIEWER_APP_H_

#include <cinder/gl/gl.h>
#include <cinder/app/App.h>
#include <cinder/app/AppBase.h>
#include <cinder/app/RendererGl.h>
#include <ds/app/app.h>

#include "app/globals.h"
#include "query/query_handler.h"
#include "ds/ui/menu/touch_menu.h"

#include <ds/ui/sprite/gst_video.h>

#include "gstreamer/GstPlayerSprite.h"
namespace mv {
class AllData;

class MediaViewer : public ds::App {
public:
	MediaViewer();

	virtual void		onKeyDown(ci::app::KeyEvent event) override;
	void				setupServer();

	void startGstPlayerSprite();
	void				fileDrop(ci::app::FileDropEvent event) override;
private:
	typedef ds::App		inherited;

	// Data
	AllData				mAllData;

	// Data acquisition
	Globals				mGlobals;
	QueryHandler		mQueryHandler;

	ds::ui::TouchMenu*	mTouchMenu;

	ds::ui::Sprite*		mStreamerParent;
	ds::ui::GstVideo*	mStreamer;

	ds::ui::GstPlayerSprite*	mPlayerSprite;

	std::string			mLastFilePath;

	bool				mGlMode = true;
	bool				mNVDecode = true;

};

} // !namespace mv

#endif // !_MEDIAVIEWER_APP_H_

