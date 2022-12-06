#include "Seebeck_Energy.h"

registerMooseObject("TetraApp", Seebeck_Energy);

InputParameters
Seebeck_Energy::validParams()
{
  InputParameters params = ADKernel::validParams();
  params.addClassDescription("Compute the energy potentials given by the following: "
                             "$(\\sigma \\alpha T \\grad u)$");
  params.addRequiredCoupledVar("temp", "temperature_variable");

  // params.addRequiredParam<MaterialPropertyName>(
  //     "seebeck_val",
  //     "Material property providing Seebeck value of the material (It can be a val or a temp "
  //     "dependent function).");
  return params;
}

Seebeck_Energy::Seebeck_Energy(const InputParameters & parameters)
  : ADKernelGrad(parameters),

    _temp(adCoupledValue("temp")),
    _seebeck(getADMaterialProperty<Real>("seebeck")),
    _resistance(getADMaterialProperty<Real>("resistance"))
{
}

ADRealVectorValue
Seebeck_Energy::precomputeQpResidual()
{
  // return _seebeck_val[_qp] * _grad_u[_qp];
  // return _grad_u[_qp] - _seebeck[_qp] * _grad_temp[_qp];

  return (_seebeck[_qp] / _resistance[_qp]) * _temp[_qp] * _grad_u[_qp];
}
