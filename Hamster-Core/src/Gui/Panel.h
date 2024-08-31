//
// Created by Jaden on 25/08/2024.
//

#ifndef PANEL_H
#define PANEL_H

namespace Hamster {
    class Panel {
    public:
        explicit Panel(bool defaultOpen = true) : m_WindowOpen(defaultOpen) {
        };

        virtual void Render() = 0;

        [[nodiscard]] bool IsPanelOpen() const { return m_WindowOpen; }

        void OpenPanel() { m_WindowOpen = true; }

    protected:
        bool m_WindowOpen = true;
    };
} // Hamster

#endif //PANEL_H
