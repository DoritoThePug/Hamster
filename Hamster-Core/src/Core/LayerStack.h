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
    LayerStack();
    ~LayerStack();

    void PushLayer(Layer* layer);

    std::vector<Layer*>::iterator begin();
    std::vector<Layer*>::iterator end();
    std::vector<Layer*>::iterator rbegin();
    std::vector<Layer*>::iterator rend();
private:
    std::vector<Layer*> m_layerStack;
};

} // Hamster

#endif //LAYERSTACK_H
