#include "Interface.h"
#include <pybind11/pybind11.h>
namespace py = pybind11;



DDRLPR_API py::str Recognize(std::string filename);