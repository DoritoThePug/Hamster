#include <string>

#include <pybind11/pybind11.h>
#include <glm.hpp>


namespace py = pybind11;

//-------------------------------------------------------------------------
// Application
//-------------------------------------------------------------------------
#include <Core/Application.h>

void ApplicationBinding(py::module_ &m) {
	py::class_<Hamster::Application>(m, "Application")
		.def(py::init<>())
		.def("Run", &Hamster::Application::Run);
}

//-------------------------------------------------------------------------
// GameObject
//-------------------------------------------------------------------------
#include <Core/GameObject.h>

class PyGameObject : public Hamster::GameObject {
public:
	using Hamster::GameObject::GameObject;

	void OnStart() override {
		PYBIND11_OVERRIDE(
			void,
			Hamster::GameObject,
			OnStart
		);
	}

	void OnUpdate(float deltaTime) override {
		PYBIND11_OVERRIDE(
			void,
			Hamster::GameObject,
			OnUpdate,
			deltaTime
		);
	}

	void OnDestroyed() override {
		PYBIND11_OVERRIDE(
			void,
			Hamster::GameObject,
			OnDestroyed
		);
	}
};

void GameObjectBinding(py::module_& m) {
	py::class_<Hamster::GameObject, PyGameObject>(m, "GameObject")
		.def(py::init<Hamster::Application*, std::string, glm::vec2, glm::vec2, float, glm::vec3>())

		.def("SetSprite", &Hamster::GameObject::SetSprite)
		.def("SetPosition", &Hamster::GameObject::SetPosition)
		.def("SetSize", &Hamster::GameObject::SetSize)
		.def("SetRotation", &Hamster::GameObject::SetRotation)
		.def("SetColour", &Hamster::GameObject::SetColour)

		.def("GetSprite", &Hamster::GameObject::GetSprite)
		.def("GetPosition", &Hamster::GameObject::GetPosition)
		.def("GetSize", &Hamster::GameObject::GetSize)
		.def("GetRotation", &Hamster::GameObject::GetRotation)
		.def("GetColour", &Hamster::GameObject::GetColour)
		
		.def("OnStart", &Hamster::GameObject::OnStart)
		.def("OnUpdate", &Hamster::GameObject::OnUpdate)
		.def("OnDestroyed", &Hamster::GameObject::OnDestroyed);
}