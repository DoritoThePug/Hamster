//
// Created by Jaden on 24/08/2024.
//

#ifndef PROPERTYEDITOR_H
#define PROPERTYEDITOR_H
#include <iostream>
#include <ostream>
#include <glm/glm.hpp>

#include <Hamster.h>
#include <Gui/Panel.h>


class PropertyEditor : public Hamster::Panel {
public:
    PropertyEditor(std::shared_ptr<Hamster::Scene> scene) : Hamster::Panel(scene, true) {
    };

    void Render() override;

    void SetSelectedEntity(Hamster::UUID uuid);

private:
    Hamster::UUID m_SelectedEntity = Hamster::UUID::GetNil();
    Hamster::Transform *m_Transform = nullptr;
    Hamster::Sprite* m_Sprite = nullptr;
};


#endif //PROPERTYEDITOR_H
