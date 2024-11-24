//
// Created by Jaden on 24/08/2024.
//

#ifndef PROPERTYEDITOR_H
#define PROPERTYEDITOR_H
#include <filesystem>
#include <glm/glm.hpp>
#include <iostream>
#include <ostream>

#include <Gui/Panel.h>
#include <Hamster.h>

class PropertyEditor : public Hamster::Panel {
public:
  PropertyEditor(std::shared_ptr<Hamster::Scene> scene)
      : Hamster::Panel(scene, true) {};

  void Render() override;

  void SetSelectedEntity(Hamster::UUID uuid);

private:
  void OpenFile(std::filesystem::path path);

  Hamster::UUID m_SelectedEntity = Hamster::UUID::GetNil();
  Hamster::Transform *m_Transform = nullptr;
  Hamster::Sprite *m_Sprite = nullptr;
  Hamster::Behaviour *m_Behaviour = nullptr;

  Hamster::Rigidbody *m_Rigidbody = nullptr;
};

#endif // PROPERTYEDITOR_H
