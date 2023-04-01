#include "ThomsonEnergy.h"

registerMooseObject("TetraApp", ThomsonEnergy);

InputParameters
ThomsonEnergy::validParams()
{
  InputParameters params = ADKernelGrad::validParams();
  params.addClassDescription("Compute the energy potentials given by the following: "
                             "$\\sigma \\alpha^{2} T \\nabla T $");
  // params.addRequiredCoupledVar("temp", "temperature_variable");

  // params.addRequiredParam<MaterialPropertyName>(
  //     "seebeck_val",
  //     "Material property providing Seebeck value of the material (It can be a val or a temp "
  //     "dependent function).");
  return params;
}

ThomsonEnergy::ThomsonEnergy(const InputParameters & parameters)
  : ADKernelGrad(parameters),

    _seebeck(getADMaterialProperty<Real>("seebeck")),
    _resistance(getADMaterialProperty<Real>("resistance"))
{
}

ADRealVectorValue
ThomsonEnergy::precomputeQpResidual()
{
  // return _seebeck_val[_qp] * _grad_u[_qp];
  // return _grad_u[_qp] - _seebeck[_qp] * _grad_temp[_qp];

  return (_seebeck[_qp] * _seebeck[_qp] / _resistance[_qp]) * _u[_qp] * _grad_u[_qp];
}
