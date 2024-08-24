//
// Created by Jaden on 24/08/2024.
//

#ifndef PROPERTYEDITOR_H
#define PROPERTYEDITOR_H



class PropertyEditor {
public:
    void Render();
    bool IsPanelOpen() {return m_WindowOpen;}
private:
    bool m_WindowOpen = true;

    //temp
    float m_f = 0.0f;
};



#endif //PROPERTYEDITOR_H
