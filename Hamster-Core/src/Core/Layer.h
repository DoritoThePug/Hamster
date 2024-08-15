//
// Created by jaden on 17/07/24.
//

#ifndef LAYER_H
#define LAYER_H

namespace Hamster {

class Layer {
public:
    Layer();
    ~Layer();

    virtual void OnAttach() = 0;
    virtual void OnDetach() = 0;
    virtual void OnUpdate() = 0;
    virtual void OnEvent() = 0;
};

} // Hamster

#endif //LAYER_H
