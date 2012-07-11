#pragma once
#ifndef DS_APP_APP_H_
#define DS_APP_APP_H_

#include <cinder/app/AppBasic.h>
#include "ds/app/engine.h"
#include "ds/app/engine_settings.h"

namespace ds {

/**
 * \class ds::App
 * Handle the main app setup.
 */
class App : public ci::app::AppBasic {
  public:
    App();
    ~App();

    virtual void                mouseDown( MouseEvent event );	
    virtual void                mouseMove( MouseEvent event );
    virtual void                mouseDrag( MouseEvent event );
    virtual void                mouseUp( MouseEvent event );	
    virtual void                touchesBegan( TouchEvent event );
    virtual void                touchesMoved( TouchEvent event );
    virtual void                touchesEnded( TouchEvent event );
    virtual void                prepareSettings(Settings*);
    virtual void				        setup();
    virtual void	    			    update();
    virtual void	    			    draw();

  protected:
    ds::EngineSettings          mEngineSettings;
    ds::Engine&                 mEngine;

  private:
    typedef ci::app::AppBasic   inherited;
};

} // namespace ds

#endif // DS_APP_ENGINE_H_