#pragma once

#include "BasicExamples/ObjectOfObservation.h"

class TRoad: public TObjectOfObservation {
 protected:
    unsigned long int oldGoTime;
    std::vector <TRoad*> roadNeighboring;
    bool isCanGo;
    //GL
    static unsigned int meshBuffer;
    void initBuffer() override;
    unsigned int getMeshBuffer() override {return meshBuffer;};
 public:
    explicit TRoad(std::string _name=""
    #ifdef USE_OpenGL
    ,const glm::vec3& _pos=glm::vec3(.0f), const glm::vec3& _scale=glm::vec3(1.0f)
    #endif
    );
   #ifdef USE_OpenGL
   virtual void setScale(const glm::vec3& _size) override;
   virtual void setPosition(const glm::vec3& pos) override;
   virtual void setRotation(const btScalar& yaw, const btScalar& pitch, const btScalar& roll) override;
   #endif
   void drawElements(const std::vector<TObject*>& objects);
   void initDraw(const std::vector<TObject*>& objects);
   virtual TObjectOfObservation* Clone() { return new TRoad();}
   virtual std::string ClassName() override { return "TRoad";}
   // FIX THAT LATER
   virtual void Update() override {}
};

class TCarDestroyer: public TRoad {
public:
    TCarDestroyer(std::string _name=""
#ifdef USE_OpenGL
        ,const glm::vec3& _pos = glm::vec3(.0f), const glm::vec3& _scale = glm::vec3(1.0f)
#endif
    );
    virtual bool IsCanGo() const noexcept { return true; }
    virtual void Go() {}
    virtual std::string ClassName() override { return "TCarDestroyer"; }
    virtual TObjectOfObservation* Clone() { return new TCarDestroyer(); }
    // UPDATE
};

class TCarCreator: public TRoad {
public:
    TCarCreator(std::string _name=""
#ifdef USE_OpenGL
        ,const glm::vec3& _pos = glm::vec3(.0f), const glm::vec3& _scale = glm::vec3(1.0f)
#endif
    );
    virtual TObjectOfObservation* Clone() { return new TCarCreator(); }
    virtual std::string ClassName() override { return "TCarCreator"; }
    // ADD UPDATE
};