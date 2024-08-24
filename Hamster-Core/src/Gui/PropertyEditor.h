//
// Created by Jaden on 21/08/2024.
//

#ifndef PROPERTYEDITOR_H
#define PROPERTYEDITOR_H

namespace Hamster {

class PropertyEditor {
public:
    void Render();
private:
    bool m_WindowOpen = true;
    float m_f = 0.0f;
};

} // Hamster

#endif //PROPERTYEDITOR_H
