//
// Created by Jaden on 27/08/2024.
//

#ifndef STARTPAUSEMODAL_H
#define STARTPAUSEMODAL_H

#include <Hamster.h>
#include <Gui/Panel.h>


class StartPauseModal : public Hamster::Panel {
public:
    StartPauseModal(std::shared_ptr<Hamster::Scene> scene) : m_Scene(scene) {};

    void Render() override;

private:
    std::shared_ptr<Hamster::Scene> m_Scene;
};



#endif //STARTPAUSEMODAL_H
