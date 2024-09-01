//
// Created by Jaden on 30/08/2024.
//

#ifndef MENUBAR_H
#define MENUBAR_H
#include <memory>

#include "ProjectCreator.h"
#include "ProjectSelector.h"
#include "Core/Scene.h"
#include "Gui/Panel.h"


class MenuBar : public Hamster::Panel {
public:
    MenuBar(std::shared_ptr<Hamster::Scene> scene) : Hamster::Panel(scene, true) {
        m_ProjectSelector = std::make_unique<ProjectSelector>(scene);
        m_ProjectCreator = std::make_unique<ProjectCreator>(scene);
    };

    void Render();

private:
    std::shared_ptr<Hamster::Scene> m_Scene;
    std::unique_ptr<ProjectCreator> m_ProjectCreator;
    std::unique_ptr<ProjectSelector> m_ProjectSelector;
};


#endif //MENUBAR_H
