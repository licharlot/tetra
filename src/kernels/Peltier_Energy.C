#include "Peltier_Energy.h"

registerMooseObject("TetraApp", Peltier_Energy);

InputParameters
Peltier_Energy::validParams()
{
  InputParameters params = ADKernelValue::validParams();
  params.addClassDescription("Compute the peltier heating effect given by the following: "
                             "-$ \\sigma \\nabla u \\cdot \\nabla u \\phi $");
  // params.addRequiredCoupledVar("temp", "temperature_variable");

  // params.addRequiredParam<MaterialPropertyName>(
  //     "seebeck_val",
  //     "Material property providing Seebeck value of the material (It can be a val or a temp "
  //     "dependent function).");
  return params;
}

Peltier_Energy::Peltier_Energy(const InputParameters & parameters)
  : ADKernelValue(parameters),

    // _seebeck(getADMaterialProperty<Real>("seebeck")),
    _resistance(getADMaterialProperty<Real>("resistance"))
{
}

ADReal
Peltier_Energy::precomputeQpResidual()
{
  // return _seebeck_val[_qp] * _grad_u[_qp];
  // return _grad_u[_qp] - _seebeck[_qp] * _grad_temp[_qp];

  // return -(_seebeck[_qp] * _seebeck[_qp] / _resistance[_qp]) * _u[_qp] * _grad_u[_qp];
  return -(1 / _resistance[_qp]) * _grad_u[_qp] * _grad_u[_qp];
}
