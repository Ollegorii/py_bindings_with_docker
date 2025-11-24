#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <vector>
#include "svd.h"

namespace py = pybind11;

PYBIND11_MODULE(svd_cpp, m) {
    m.doc() = "SVD decomposition using C++";
    
    m.def("svd", [](const std::vector<std::vector<double>>& A, int max_iter = 1000) {
        std::vector<std::vector<double>> U, Vt;
        std::vector<double> S;
        
        SVD::svd(A, U, S, Vt, max_iter);
        
        return py::make_tuple(U, S, Vt);
    }, py::arg("A"), py::arg("max_iter") = 1000);
}