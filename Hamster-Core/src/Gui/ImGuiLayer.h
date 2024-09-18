//
// Created by Jaden on 23/08/2024.
//

#ifndef IMGUILAYER_H
#define IMGUILAYER_H

#include <imgui.h>
#include <imgui_impl_opengl3.h>

#include "Core/Layer.h"

namespace Hamster {

class ImGuiLayer : public Layer {
public:
  ~ImGuiLayer() override = default;

  void Begin();
  void End();

  void OnAttach() override;
  void OnDetach() override;
  void OnUpdate() override;

  void AttachDefaultColourScheme();
};

} // namespace Hamster

#endif // IMGUILAYER_H
