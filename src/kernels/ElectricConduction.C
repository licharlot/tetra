#include "ElectricConduction.h"

registerMooseObject("TetraApp", ElectricConduction);

InputParameters
ElectricConduction::validParams()
{
  InputParameters params = ADKernel::validParams();
  params.addClassDescription("Compute the electric conduction potential by : "
                             "$(\\sigma \\nabla u )$");
  // params.addRequiredCoupledVar("temp", "temperature_variable");

  // params.addRequiredParam<MaterialPropertyName>(
  //     "seebeck_val",
  //     "Material property providing Seebeck value of the material (It can be a val or a temp "
  //     "dependent function).");
  return params;
}

ElectricConduction::ElectricConduction(const InputParameters & parameters)
  : ADKernelGrad(parameters),

    // _seebeck(getADMaterialProperty<Real>("seebeck")),
    _resistance(getADMaterialProperty<Real>("resistance"))
{
}

ADRealVectorValue
ElectricConduction::precomputeQpResidual()
{
  // return _seebeck_val[_qp] * _grad_u[_qp];
  // return _grad_u[_qp] - _seebeck[_qp] * _grad_temp[_qp];

  return (1 / _resistance[_qp]) * _grad_u[_qp];
}
