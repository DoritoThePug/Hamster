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

#include "Core/Project.h"


class ProjectCreator : public Hamster::Panel {
public:
    ProjectCreator() : Hamster::Panel(false) {
    };

    void Render() override;

private:
    bool m_WindowOpen = false;

    std::shared_ptr<Hamster::Scene> m_Scene;

    std::string OpenWindowsFileDialog(HWND owner);

    void CreateProject();

    Hamster::ProjectConfig m_ProjectConfig;
    char m_ProjectNameInput[100] = "Untitled";

    bool m_NoDirectorySelected = false;
    bool m_DirectoryExists = false;
};


#endif //PROJECTCREATOR_H
