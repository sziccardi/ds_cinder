#pragma once
#ifndef DS_UI_MEDIA_STREAM_PLAYER_STREAM_PLAYER
#define DS_UI_MEDIA_STREAM_PLAYER_STREAM_PLAYER


#include <ds/ui/sprite/sprite.h>

namespace ds {

class Resource;

namespace ui {

class GstVideo;
class VideoInterface;
class MediaInterface;

/**
* \class ds::ui::VideoPlayer
*			Creates a video and puts an interface on top of it.
*/
class StreamPlayer : public ds::ui::Sprite  {
public:
	StreamPlayer(ds::ui::SpriteEngine& eng, const bool embedInterface = true);

	void								setResource(const ds::Resource& resource);

	void								layout();

	void								play();
	void								pause();
	void								stop();
	void								toggleMute();

	void								showInterface();
	void								hideInterface();
	VideoInterface*						getVideoInterface(){ return mVideoInterface; }
	void								setShowInterfaceAtStart(bool showInterfaceAtStart);
	void								setAutoRestartStream(bool autoRestart);

	ds::ui::GstVideo*					getVideo();

	void								setGoodStatusCallback(std::function<void()> func){ mGoodStatusCallback = func; }
	void								setErrorCallback(std::function<void(const std::string&)> func){ mErrorMsgCallback = func; }

protected:

	virtual void						onSizeChanged();
	VideoInterface*						mVideoInterface;
	ds::ui::GstVideo*					mVideo;
	bool								mEmbedInterface;
	bool								mShowInterfaceAtStart;
	std::function<void(void)>					mGoodStatusCallback;
	std::function<void(const std::string&)>		mErrorMsgCallback;

};

} // namespace ui
} // namespace ds

#endif
