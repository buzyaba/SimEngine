#pragma once

#include "SimEngine/Object.h"

#ifdef USE_OPENGL
    #include "GraphicManager.hpp"
#else
    class TGraphicManager;
#endif


class IGraphicPresenter {
  public:
    virtual void addTObject(TObject *obj) {}
    virtual void setGraphicManager(TGraphicManager *manager) {}
    virtual void transformsUpdateSignal() {};
    virtual void stopGraphicManager() {};
};

#ifdef USE_OPENGL
class TGraphicPresenter : public IGraphicPresenter {
    TGraphicManager *_manager;
  public:
    TGraphicPresenter() : _manager(nullptr) {}
    void setGraphicManager(TGraphicManager *manager) override {
        _manager = manager;
    }
    void addTObject(TObject *obj) override {
        _manager->addNewObject(obj);
    }
    
    void transformsUpdateSignal() override {
      _manager->needUpdateFlag.store(true, std::memory_order::memory_order_release);
      while(_manager->needUpdateFlag.load(std::memory_order::memory_order_acquire));
    }

    void stopGraphicManager() override {
        _manager->stopDraw();
    };
};
#endif
