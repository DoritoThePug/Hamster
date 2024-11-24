//
// Created by Jaden on 31/08/2024.
//

#ifndef SCENEEVENTS_H
#define SCENEEVENTS_H

#include "Event.h"
#include "Core/UUID.h"

namespace Hamster {
  class CollisionEvent : public Event {
  public:
    CollisionEvent(UUID& uuidA, UUID& uuidB) : uuidA(uuidA), uuidB(uuidB) {};

    [[nodiscard]] UUID& GetUUIDA() const {return uuidA;}
    [[nodiscard]] UUID& GetUUIDB() const {return uuidB;}

    BIND_EVENT_TYPE(Collision);
  private:
    UUID& uuidA;
    UUID& uuidB;
  };
} // namespace Hamster

#endif // SCENEEVENTS_H
