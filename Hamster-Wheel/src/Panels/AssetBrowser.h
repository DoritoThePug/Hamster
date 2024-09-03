//
// Created by Jaden on 03/09/2024.
//

#ifndef ASSETBROWSER_H
#define ASSETBROWSER_H
#include "Gui/Panel.h"


#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

class AssetBrowser : public Hamster::Panel {
public:
    AssetBrowser(std::shared_ptr<Hamster::Scene> scene) : Hamster::Panel(scene) {
    };

    void Render() override;

    std::string OpenWindowsFileDialog(HWND owner);
};


#endif //ASSETBROWSER_H
