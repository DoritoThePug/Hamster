//
// Created by jaden on 17/07/24.
//

#ifndef LAYER_H
#define LAYER_H
#include "Events/ApplicationEvents.h"

namespace Hamster {
    class Layer {
    public:
        virtual ~Layer() = default;


        virtual void OnAttach() {
        };

        virtual void OnDetach() {
        };

        virtual void OnUpdate() {
        };

        virtual void OnImGuiUpdate() {
        };
    };
} // Hamster

#endif //LAYER_H
