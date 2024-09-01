//
// Created by Jaden on 01/09/2024.
//

#ifndef PROJECTSELECTOR_H
#define PROJECTSELECTOR_H

#include <Hamster.h>
#include <Gui/Panel.h>
#include <Core/Project.h>

#include <windows.h>
#include <shlobj.h>


class ProjectSelector : public Hamster::Panel {
public:
    ProjectSelector() {
    };

    ProjectSelector(std::shared_ptr<Hamster::Scene> scene) : Hamster::Panel(scene, false) {
    };

    void Render() override;

private:
    std::string OpenWindowsFileDialog(HWND owner);

    std::filesystem::path m_ProjectFilePath;

    bool m_NoPathSelected = false;
};


#endif //PROJECTSELECTOR_H
