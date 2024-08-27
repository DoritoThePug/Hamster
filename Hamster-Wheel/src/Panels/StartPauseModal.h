//
// Created by Jaden on 27/08/2024.
//

#ifndef STARTPAUSEMODAL_H
#define STARTPAUSEMODAL_H

#include <Hamster.h>
#include <Gui/Panel.h>


class StartPauseModal : public Hamster::Panel {
public:
    StartPauseModal(Hamster::Application& app);

    void Render() override;

private:
    Hamster::Application& m_App;
};



#endif //STARTPAUSEMODAL_H
