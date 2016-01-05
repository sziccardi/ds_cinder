#include "image_with_thumbnail.h"

#include "ds/ui/sprite/sprite_engine.h"

namespace ds {
namespace ui {

const float ImageWithThumbnail::DEFAULT_FADE_DURATION = 0.35f;

ImageWithThumbnail::ImageWithThumbnail(SpriteEngine& engine, const int flags, float fadeDuration)
	: inherited(engine, flags)
	, mThumbnail(nullptr)
	, mFadeDuration(fadeDuration)
{}

ImageWithThumbnail::ImageWithThumbnail(SpriteEngine& engine, const std::string& filename, const int flags, float fadeDuration)
	: inherited(engine, filename, flags)
	, mThumbnail(nullptr)
	, mFadeDuration(fadeDuration)
{}

ImageWithThumbnail::ImageWithThumbnail(SpriteEngine& engine, const ds::Resource::Id& resourceId, const int flags, float fadeDuration)
	: inherited(engine, resourceId, flags)
	, mThumbnail(nullptr)
	, mFadeDuration(fadeDuration)
{}

ImageWithThumbnail::ImageWithThumbnail(SpriteEngine& engine, const ds::Resource& resource, const int flags, float fadeDuration)
	: inherited(engine, resource, flags)
	, mThumbnail(nullptr)
	, mFadeDuration(fadeDuration)
{}

void ImageWithThumbnail::setImageResource(const ds::Resource& resource, const int flags){
	inherited::setImageResource(resource, flags);

	// dump an existing thumbnail, if any
	if(mThumbnail){
		mThumbnail->release();
		mThumbnail = nullptr;
	}

	if(resource.getThumbnailId() > 0 || !resource.getThumbnailFilePath().empty()){
		mThumbnail = new ds::ui::Image(mEngine);
		addChildPtr(mThumbnail);
		if(resource.getThumbnailId() > 0){
			mThumbnail->setImageResource(resource.getThumbnailId());
		} else {
			mThumbnail->setImageFile(resource.getThumbnailFilePath());
		}
		mThumbnail->setSize(getWidth(), getHeight());
	}
}

void ImageWithThumbnail::setSizeAll( float width, float height, float depth ){
	inherited::setSizeAll(width, height, depth);
	if(mThumbnail){
		mThumbnail->setSizeAll(width, height, depth);
	}
}

bool ImageWithThumbnail::isLoaded() const{
	return isLoadedThumbnail(true);
}

bool ImageWithThumbnail::isLoadedThumbnail(bool thumbnail) const{
	bool output = true;
	if(mThumbnail && thumbnail){
		output = mThumbnail->isLoaded();
	} else {
		output = inherited::isLoaded();
	}
	return output;
}

bool ImageWithThumbnail::isLoadedPrimary() const{
	return isLoadedThumbnail(false);
}

void ImageWithThumbnail::onImageLoaded(){
	inherited::onImageLoaded();
	if(mThumbnail){
		// fade the thumbnail out and eliminate it
		mThumbnail->tweenOpacity(0.0f, mFadeDuration, 0.0f, ci::easeNone, [this](){
			mThumbnail->release();
			mThumbnail = nullptr;
		});
	}
}

} // namespace ui
} // namespace ds
