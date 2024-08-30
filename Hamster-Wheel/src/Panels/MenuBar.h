//
// Created by Jaden on 30/08/2024.
//

#ifndef MENUBAR_H
#define MENUBAR_H
#include <memory>

#include "Core/Scene.h"
#include "Gui/Panel.h"


class MenuBar {
public:
    MenuBar(std::shared_ptr<Hamster::Scene> scene) : m_Scene(std::move(scene)) {};

    void Render();

private:
    std::shared_ptr<Hamster::Scene> m_Scene;
};



#endif //MENUBAR_H
