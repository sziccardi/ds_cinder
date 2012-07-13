#include "ds/app/engine_clientserver.h"

namespace ds {

/**
 * \class ds::EngineClientServer
 */
EngineClientServer::EngineClientServer(const ds::cfg::Settings& settings)
    : inherited(settings)
    , mLoadImageService(mLoadImageThread)
{
}

void EngineClientServer::setup()
{
  inherited::setup();

  mLoadImageThread.start(true);
}

void EngineClientServer::update()
{
  updateClient();
}

void EngineClientServer::draw()
{
  drawServer();
}

} // namespace ds
