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
    Hierarchy(std::shared_ptr<Hamster::Scene> scene) : Hamster::Panel(scene, true) {
    };

    void SetSelectedEntity(const entt::entity entity);

    entt::entity GetSelectedEntity() const;

    void Render() override;

private:
    entt::entity m_SelectedEntity = entt::null;
};


#endif //HIERARCHY_H
