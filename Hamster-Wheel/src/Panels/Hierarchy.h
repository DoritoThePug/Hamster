//
// Created by Jaden on 25/08/2024.
//

#ifndef HIERARCHY_H
#define HIERARCHY_H

#include <entt/entt.hpp>

#include <Hamster.h>
#include <Gui/Panel.h>

class Hierarchy : public Hamster::Panel {
public:
    Hierarchy(Hamster::Application& app);

    void SetSelectedEntity(const entt::entity entity);
    entt::entity GetSelectedEntity() const;

    void Render() override;
private:
    entt::entity m_SelectedEntity = entt::null;
    Hamster::Application& m_App;
};



#endif //HIERARCHY_H
