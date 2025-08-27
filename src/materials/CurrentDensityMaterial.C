#include "CurrentDensityMaterial.h"
registerMooseObject("TetraApp", CurrentDensityMaterial);

InputParameters
CurrentDensityMaterial::validParams()
{
  InputParameters params = Material::validParams();
  params.addClassDescription("Material object for current density");
  params.addRequiredCoupledVar("elec", "Electrical potential variable");
  params.addRequiredCoupledVar("temp", "Temperature variable");

  return params;
}

CurrentDensityMaterial::CurrentDensityMaterial(const InputParameters & parameters)
  : Material(parameters),
    _grad_elec(adCoupledGradient("elec")),
    _grad_temp(adCoupledGradient("temp")),
    _seebeck(getADMaterialProperty<Real>("seebeck")),
    _resistivity(getADMaterialProperty<Real>("resistivity")),
    _current_density(declareADProperty<RealVectorValue>("current_density"))
{
}
void
CurrentDensityMaterial::computeQpProperties()
{
  _current_density[_qp] = -(_grad_elec[_qp] / _resistivity[_qp] + _seebeck[_qp] * _grad_temp[_qp]/_resistivity[_qp]);
}
