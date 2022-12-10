#include "JouleHeating_Seebeck.h"

registerMooseObject("TetraApp", JouleHeating_Seebeck);

InputParameters
JouleHeating_Seebeck::validParams()
{
  InputParameters params = ADKernelValue::validParams();
  params.addClassDescription("Compute the joule heating effect related by seebeck effect: "
                             "-$ \\sigma \\nabla u \\nabla T \\cdot \\nabla u \\phi $");
  params.addRequiredCoupledVar("temp", "temperature_variable");

  // params.addRequiredParam<MaterialPropertyName>(
  //     "seebeck_val",
  //     "Material property providing Seebeck value of the material (It can be a val or a temp "
  //     "dependent function).");
  return params;
}

JouleHeating_Seebeck::JouleHeating_Seebeck(const InputParameters & parameters)
  : ADKernelValue(parameters),
    _grad_temp(adCoupledGradient("temp")),

    _seebeck(getADMaterialProperty<Real>("seebeck")),
    _resistance(getADMaterialProperty<Real>("resistance"))
{
}

ADReal
JouleHeating_Seebeck::precomputeQpResidual()
{
  // return _seebeck_val[_qp] * _grad_u[_qp];
  // return _grad_u[_qp] - _seebeck[_qp] * _grad_temp[_qp];

  // return -(_seebeck[_qp] * _seebeck[_qp] / _resistance[_qp]) * _u[_qp] * _grad_u[_qp];
  // return -_seebeck[_qp] * _grad_u[_qp] * _grad_u[_qp] * _test[_i][_qp];
  return -(_seebeck[_qp] / _resistance[_qp]) * _grad_temp[_qp] * _grad_u[_qp];
}
