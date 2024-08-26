//
// Created by Jaden on 24/08/2024.
//

#ifndef PROPERTYEDITOR_H
#define PROPERTYEDITOR_H
#include <iostream>
#include <ostream>
#include <glm/glm.hpp>

#include "Core/Application.h"
#include "Gui/Panel.h"


class PropertyEditor : public Hamster::Panel {
public:
    void Render() override;

    void SetSelectedProperty(Hamster::Transform* transform) {m_Transform = transform;}
private:
    //temp
    Hamster::Transform* m_Transform = nullptr;
};



#endif //PROPERTYEDITOR_H
