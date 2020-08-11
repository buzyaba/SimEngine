#pragma once

#include "Core/Object.h"

#ifdef USE_OPENGL
#include "GraphicManager.hpp"
#endif

class IGraphicPresenter {
  public:
    virtual void addTObject(TObject *obj) {}
    virtual void deleteTObject(const TObject *obj) {}
    virtual void setGraphicManager(TGraphicManager *manager) {}
};

#ifdef USE_OPENGL
class TGraphicPresenter : public IGraphicPresenter {
  private:
    TGraphicManager *_manager;

  public:
    TGraphicPresenter() : _manager(nullptr) {}
    virtual void setGraphicManager(TGraphicManager *manager) override {
        _manager = manager;
    }
    virtual void addTObject(TObject *obj) override {
        _manager->addNewObject(obj);
    }
    virtual void deleteTObject(const TObject *obj) override {}
};
#endif
