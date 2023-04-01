#include "JouleHeating.h"

registerMooseObject("TetraApp", JouleHeating);

InputParameters
JouleHeating::validParams()
{
  InputParameters params = ADKernelValue::validParams();
  params.addClassDescription("Compute the joule heating : "
                             "-$ \\sigma \\nabla u \\cdot \\nabla u \\phi $");
  params.addRequiredCoupledVar("elec", "Electrostatic potential for joule heating.");

  // params.addRequiredParam<MaterialPropertyName>(
  //     "seebeck_val",
  //     "Material property providing Seebeck value of the material (It can be a val or a temp "
  //     "dependent function).");
  return params;
}

JouleHeating::JouleHeating(const InputParameters & parameters)
  : ADKernelValue(parameters),

    _grad_elec(adCoupledGradient("elec")),
    // _seebeck(getADMaterialProperty<Real>("seebeck")),
    _resistance(getADMaterialProperty<Real>("resistance"))
{
}

ADReal
JouleHeating::precomputeQpResidual()
{
  // return _seebeck_val[_qp] * _grad_u[_qp];
  // return _grad_u[_qp] - _seebeck[_qp] * _grad_temp[_qp];

  // return -(_seebeck[_qp] * _seebeck[_qp] / _resistance[_qp]) * _u[_qp] * _grad_u[_qp];
  return -(1 / _resistance[_qp]) * _grad_elec[_qp] * _grad_elec[_qp];
}
