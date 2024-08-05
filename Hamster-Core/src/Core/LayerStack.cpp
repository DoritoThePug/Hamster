//
// Created by jaden on 17/07/24.
//

#include "LayerStack.h"

namespace Hamster {
    void LayerStack::PushLayer(Layer *layer) {
        m_layerStack.emplace_back(layer);
    }

    std::vector<Layer *>::iterator LayerStack::begin() {
        return m_layerStack.begin();
    }

    std::vector<Layer *>::iterator LayerStack::end() {
        return m_layerStack.end();
    }

    std::vector<Layer *>::iterator LayerStack::rend() {
        return m_layerStack.begin();
    }

    std::vector<Layer *>::iterator LayerStack::rbegin() {
        return m_layerStack.end();
    }
} //Hamster