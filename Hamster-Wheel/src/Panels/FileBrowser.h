//
// Created by Jaden on 02/09/2024.
//

#ifndef FILEBROWSER_H
#define FILEBROWSER_H
#include "Gui/Panel.h"


class FileBrowser : public Hamster::Panel {
public:
    explicit FileBrowser(std::shared_ptr<Hamster::Scene> scene) : Hamster::Panel(std::move(scene), true) {
    };

    void Render() override;
};


#endif //FILEBROWSER_H
