//
// Created by Jaden on 30/08/2024.
//

#ifndef MENUBAR_H
#define MENUBAR_H
#include <memory>

#include "ProjectCreator.h"
#include "Core/Scene.h"
#include "Gui/Panel.h"


class MenuBar {
public:
    MenuBar(std::shared_ptr<Hamster::Scene> scene) : m_Scene(std::move(scene)) {
    };

    void Render();

    void ChangeActiveScene(std::shared_ptr<Hamster::Scene> scene) {
        m_Scene = std::move(scene);
    };

private:
    std::shared_ptr<Hamster::Scene> m_Scene;
    std::unique_ptr<ProjectCreator> m_ProjectCreator = std::make_unique<ProjectCreator>();
};


#endif //MENUBAR_H
