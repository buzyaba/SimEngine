#pragma once

#include "SimEngine/ObjectOfObservation.h"

struct RoadLane: public TObjectOfObservation {
    std::vector<TObjectOfObservation*> roads;
    RoadLane(const std::vector<TObjectOfObservation*>& _roads) : TObjectOfObservation("RoadLane"), roads(_roads) {}
};
