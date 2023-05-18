#include "parameters.h"

#include <vector>
#include <map>


Parameters::Parameters() {
}

void Parameters::addParameter(ConPar<bool> parameter) { m_boolConpars.emplace(parameter.getName(), parameter); }
void Parameters::addParameter(ConPar<std::string> parameter) {
	m_stringConpars.emplace(parameter.getName(), parameter);
}
void Parameters::addParameter(ConPar<int> parameter) { m_intConpars.emplace(parameter.getName(), parameter); }
void Parameters::addParameter(ConPar<float> parameter) { m_floatConpars.emplace(parameter.getName(), parameter); }
