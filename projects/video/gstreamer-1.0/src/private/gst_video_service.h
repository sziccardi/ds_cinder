#pragma once
#ifndef PRIVATE_VIDEO_SERVICE
#define PRIVATE_VIDEO_SERVICE

#include <ds/app/engine/engine_service.h>
#include <string>


namespace ds {
class Engine;

namespace gstreamer {

/**
* \class ds::gstreamer::GstVideoService
* \brief Setup gstreamer paths and other initialization
*/
class GstVideoService : public ds::EngineService {
public:
	GstVideoService(ds::Engine&);
	~GstVideoService();

	bool					getValidInstall();
	const std::string&		getErrorMessage();

	virtual void			start();

private:
	bool					mValidInstall;
	std::string				mErrorMessage;
	ds::Engine&				mEngine;


};

} // namespace gstreamer
} // namespace ds

#endif 