#include <pybind11/pybind11.h>

namespace py = pybind11;

//-------------------------------------------------------------------------
// AssetManager
//-------------------------------------------------------------------------
#include <Utils/AssetManager.h>

void AssetManagerBinding(py::module_& m) {
	py::class_<Hamster::AssetManager>(m, "AssetManager")
		.def("AddShader", &Hamster::AssetManager::AddShader)
		.def("GetShader", &Hamster::AssetManager::GetShader)
		
		.def("AddTexture", &Hamster::AssetManager::AddTexture)
		.def("GetTexture", &Hamster::AssetManager::GetTexture);
}
