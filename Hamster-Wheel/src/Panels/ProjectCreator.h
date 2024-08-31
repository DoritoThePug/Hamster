//
// Created by Jaden on 31/08/2024.
//

#ifndef PROJECTCREATOR_H
#define PROJECTCREATOR_H

#include "Gui/Panel.h"

#include <string>
#include <windows.h>
#include<shlobj.h>
#include <memory>

#include <Hamster.h>


class ProjectCreator : public Hamster::Panel {
public:
    ProjectCreator() : Hamster::Panel(false) {
    };

    void Render() override;

private:
    bool m_WindowOpen = false;

    std::shared_ptr<Hamster::Scene> m_Scene;

    std::string OpenWindowsFileDialog(HWND owner);
};


#endif //PROJECTCREATOR_H
