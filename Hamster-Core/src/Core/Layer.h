//
// Created by jaden on 17/07/24.
//

#ifndef LAYER_H
#define LAYER_H
#include "Events/ApplicationEvents.h"

namespace Hamster {
// Pure virtual class, intended for internal use for major component lifecycly
// events, will in future extend to user use

class Layer {
public:
  virtual ~Layer() = default;

  virtual void OnAttach() {};

  virtual void OnDetach() {};

  virtual void OnUpdate() {};

  virtual void OnImGuiUpdate() {};
};
} // namespace Hamster

#endif // LAYER_H
