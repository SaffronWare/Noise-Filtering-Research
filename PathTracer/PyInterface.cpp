#include <pybind11/pybind11.h>
#include <pybind11/iostream.h>

#include "Analysis.h"
#include "Setup.h"

void cvsample(unsigned int max_iter, unsigned int sample_step, std::string path)
{
	Analysis::sampleConvergence(max_iter, sample_step, path);
}

PYBIND11_MODULE(PathTracerPy, m)
{
	Setup::Setup();

	m.def("cvsample", &cvsample, pybind11::call_guard<pybind11::scoped_ostream_redirect>());
	
}