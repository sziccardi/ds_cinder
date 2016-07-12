#include "private/web_service.h"

#include <ds/app/engine/engine.h>

#include <ds/ui/sprite/web.h>

#include "include/cef_app.h"

#include "simple_app.h"

namespace ds {
namespace web {

/**
 * \class ds::web::Service
 */
Service::Service(ds::Engine& e)
	: ds::AutoUpdate(e, AutoUpdateType::SERVER | AutoUpdateType::CLIENT)
{
	mEngine.registerSpriteImporter("web", [this](ds::ui::SpriteEngine& engine)->ds::ui::Sprite*{
		return new ds::ui::Web(mEngine);
	});

	mEngine.registerSpritePropertySetter("web_url", [this](ds::ui::Sprite& bs, const std::string& theValue, const std::string& fileReferrer){
		ds::ui::Web* webby = dynamic_cast<ds::ui::Web*>(&bs);
		if(!webby){
			DS_LOG_WARNING("Tried to set the web_url of a non-ds::ui::Web sprite. Ignoring!");
			return;
		}

		webby->setUrl(theValue);
	});

	void* sandbox_info = NULL;
	CefMainArgs main_args(GetModuleHandle(NULL));
	int exit_code = CefExecuteProcess(main_args, NULL, sandbox_info);
	if(exit_code >= 0){
		std::cout << "CEF setup exit code: " << exit_code << std::endl;
	} 
	
	CefSettings settings;
	settings.no_sandbox = true;
	settings.multi_threaded_message_loop = true;
	//settings.windowless_rendering_enabled

	CefRefPtr<SimpleApp> app(new SimpleApp);
	CefInitialize(main_args, settings, app.get(), sandbox_info);

	//CefRunMessageLoop();
	
}

Service::~Service() {
	CefShutdown();
}

void Service::start() {
}

void Service::update(const ds::UpdateParams&) {
}

} // namespace web
} // namespace ds