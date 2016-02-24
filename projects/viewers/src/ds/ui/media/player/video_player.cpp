#include "video_player.h"


#include <ds/app/environment.h>
#include <ds/ui/sprite/sprite_engine.h>
#include <ds/debug/logger.h>
#include <ds/util/string_util.h>

#include <ds/ui/sprite/video.h>
#include <ds/ui/button/image_button.h>

#include "ds/ui/media/interface/video_interface.h"
#include "ds/ui/media/media_interface_builder.h"

namespace ds {
namespace ui {

VideoPlayer::VideoPlayer(ds::ui::SpriteEngine& eng, const bool embedInterface)
	: ds::ui::Sprite(eng)
	, mVideo(nullptr)
	, mVideoInterface(nullptr)
	, mEmbedInterface(embedInterface)
	, mShowInterfaceAtStart(true)
{
}

void VideoPlayer::setMedia(const std::string mediaPath){
	clear();

	mVideo = new ds::ui::GstVideo(mEngine);
	mVideo->generateAudioBuffer(true);
	mVideo->setLooping(true);

	mVideo->setMute(true);
	mVideo->setAutoStart(false);
	mVideo->loadVideo(mediaPath);
	mVideo->playAFrame(-1.0, [this](){
		mVideo->setMute(false);
	});
	addChildPtr(mVideo);

	if(mVideoInterface){
		mVideoInterface->release();
		mVideoInterface = nullptr;
	}

	if(mEmbedInterface){
		mVideoInterface = dynamic_cast<VideoInterface*>(MediaInterfaceBuilder::buildMediaInterface(mEngine, this, this));
		if(mVideoInterface){
			mVideoInterface->sendToFront();
		}
	}

	if(mVideoInterface){
		if(mShowInterfaceAtStart){
			mVideoInterface->show();
		} else {
			mVideoInterface->setOpacity(0.0f);
			mVideoInterface->hide();
		}
	}

	setSize(mVideo->getWidth(), mVideo->getHeight());
}

void VideoPlayer::clear(){
	if(mVideo){
		mVideo->release();
		mVideo = nullptr;
		if(mVideoInterface){
			mVideoInterface->linkVideo(nullptr);
		}
	}
}

void VideoPlayer::onSizeChanged(){
	layout();
}

void VideoPlayer::layout(){
	if(mVideo){
		mVideo->setScale(getWidth() / mVideo->getWidth());
	}

	if(mVideoInterface && mEmbedInterface){
		mVideoInterface->setSize(getWidth() / 2.0f, mVideoInterface->getHeight());
		mVideoInterface->setPosition(getWidth() / 2.0f - mVideoInterface->getWidth() / 2.0f, getHeight() - mVideoInterface->getHeight() - 50.0f);
	}
}

void VideoPlayer::showInterface(){
	if(mVideoInterface){
		mVideoInterface->animateOn();
	}
}

void VideoPlayer::setShowInterfaceAtStart(bool showInterfaceAtStart){
	mShowInterfaceAtStart = showInterfaceAtStart;
}

void VideoPlayer::play(){
	if(mVideo){
		if(mVideo->isPlayingAFrame()){
			mVideo->enablePlayingAFrame(false);
			mVideo->setMute(false);
		}
		mVideo->play();
	}
}

void VideoPlayer::pause(){
	if(mVideo){
		mVideo->pause();
	}
}

void VideoPlayer::stop(){
	if(mVideo){
		mVideo->stop();
	}
}

ds::ui::GstVideo* VideoPlayer::getVideo(){
	return mVideo;
}

void VideoPlayer::togglePlayPause(){
	if(mVideo){
		if(mVideo->getIsPlaying()){
			mVideo->pause();
		} else {
			mVideo->play();
		}
	}
}

} // namespace ui
} // namespace ds
