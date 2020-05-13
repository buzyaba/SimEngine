#pragma once

#include "BasicExamples/ObjectOfObservation.h"

class TRoad: public TObjectOfObservation {
 protected:
    unsigned long int oldGoTime;
    std::vector < TRoad*> roadNeighboring;
    bool isCanGo;
    //GL
    static unsigned int meshBuffer;
 private:
    void initBuffer() override;
    unsigned int getMeshBuffer() override {return meshBuffer;};
 public:
    explicit TRoad(std::string _name="", const glm::vec3& _pos=glm::vec3(.0f),
                                         const glm::vec3& _scale=glm::vec3(1.0f));
   virtual void setScale(const glm::vec3& _size) override;
   virtual void setPosition(const glm::vec3& pos) override;
   virtual void setRotation(const btScalar& yaw, const btScalar& pitch, const btScalar& roll) override;
   void drawElements(const std::vector<TObject*>& objects);
   void initDraw(const std::vector<TObject*>& objects);
   virtual TObjectOfObservation* Clone() { return new TRoad();}
   virtual std::string ClassName() override { return "TRoad";}
};
