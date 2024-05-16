#include <pybind11/pybind11.h>
#include <glm.hpp>


namespace py = pybind11;

//-------------------------------------------------------------------------
// Texture
//-------------------------------------------------------------------------
#include <Renderer/Texture.h>

void TextureBinding(py::module_& m) {
	py::class_<Hamster::Texture>(m, "Texture")
		.def(py::init<const char*>());
}
