//
// Created by Jaden on 24/08/2024.
//

#ifndef PROPERTYEDITOR_H
#define PROPERTYEDITOR_H
#include <iostream>
#include <ostream>
#include <glm/glm.hpp>

#include "Gui/Panel.h"


class PropertyEditor : public Hamster::Panel {
public:
    void Render() override;

    void SetSelectedProperty(glm::vec2* transform) {m_Transform = transform;}
private:
    //temp
    glm::vec2* m_Transform = nullptr;
};



#endif //PROPERTYEDITOR_H
