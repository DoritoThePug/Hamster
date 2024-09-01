//
// Created by Jaden on 01/09/2024.
//

#ifndef PROJECTHUBLAYER_H
#define PROJECTHUBLAYER_H

#include <Hamster.h>

#include "EditorLayer.h"
#include "Panels/ProjectSelector.h"


class ProjectHubLayer : public Hamster::Layer {
public:
    explicit ProjectHubLayer(EditorLayer *editorLayer) : m_EditorLayer(editorLayer) {
    };

    void OnAttach() override;

    void OnImGuiUpdate() override;

private:
    std::unique_ptr<ProjectSelector> m_ProjectSelector = std::make_unique<ProjectSelector>();
    EditorLayer *m_EditorLayer = nullptr;
};


#endif //PROJECTHUBLAYER_H
