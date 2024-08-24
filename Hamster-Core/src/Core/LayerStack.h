//
// Created by jaden on 17/07/24.
//

#ifndef LAYERSTACK_H
#define LAYERSTACK_H

#include <vector>

#include "Layer.h"

namespace Hamster {
    class LayerStack {
    public:
        void PushLayer(Layer *layer);
        void PopLayer(Layer* layer);

        std::vector<Layer *>::iterator begin();

        std::vector<Layer *>::iterator end();

        std::vector<Layer *>::iterator rbegin();

        std::vector<Layer *>::iterator rend();

        std::vector<Layer *>::const_iterator begin()const;

        std::vector<Layer *>::const_iterator end()const;

        std::vector<Layer *>::const_iterator rbegin() const;

        std::vector<Layer *>::const_iterator rend() const;

    private:
        std::vector<Layer *> m_LayerStack;
    };
} // Hamster

#endif //LAYERSTACK_H
