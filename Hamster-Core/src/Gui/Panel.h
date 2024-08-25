//
// Created by Jaden on 25/08/2024.
//

#ifndef PANEL_H
#define PANEL_H

namespace Hamster {

class Panel {
public:
    virtual void Render() = 0;
    [[nodiscard]] bool IsPanelOpen() const {return m_WindowOpen;}
protected:
    bool m_WindowOpen = true;
};

} // Hamster

#endif //PANEL_H
