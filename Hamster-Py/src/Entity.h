//
// Created by Jaden on 31/08/2024.
//
#pragma once

#include <Hamster.h>

#include <pybind11/pybind11.h>

namespace py = pybind11;

class PyEntity : public Hamster::Entity {
public:
    using Hamster::Entity::Entity;

    void OnCreate() override {
        PYBIND11_OVERRIDE(
            void,
            Hamster::Entity,
            OnCreate);
    }

    void OnUpdate(float deltaTime) override {
        PYBIND11_OVERRIDE(
            void,
            Hamster::Entity,
            OnUpdate,
            deltaTime);
    }

    void OnDestroyed() override {
        PYBIND11_OVERRIDE(
            void,
            Hamster::Entity,
            OnDestroyed);
    }
};

void EntityBinding(py::module_ &m) {
    py::class_<Hamster::Entity, PyEntity>(m, "Entity")
            .def(py::init<>())
            .def("OnCreate", &Hamster::Entity::OnCreate)
            .def("OnUpdate", &Hamster::Entity::OnUpdate)
            .def("OnDestroyed", &Hamster::Entity::OnDestroyed);
}
