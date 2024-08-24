//
// Created by jaden on 17/07/24.
//

#include "LayerStack.h"

#include <algorithm>

namespace Hamster {

    void LayerStack::PushLayer(Layer *layer) {
        m_LayerStack.emplace_back(layer);
    }

    void LayerStack::PopLayer(Layer *layer) {
        auto it = std::find(m_LayerStack.begin(), m_LayerStack.end(), layer);

        if (it != m_LayerStack.end()) {
            layer->OnDetach();
            m_LayerStack.erase(it);
        }
    }

    std::vector<Layer *>::iterator LayerStack::begin() {
        return m_LayerStack.begin();
    }

    std::vector<Layer *>::iterator LayerStack::end() {
        return m_LayerStack.end();
    }

    std::vector<Layer *>::iterator LayerStack::rend() {
        return m_LayerStack.begin();
    }

    std::vector<Layer *>::iterator LayerStack::rbegin() {
        return m_LayerStack.end();
    }


} //Hamster