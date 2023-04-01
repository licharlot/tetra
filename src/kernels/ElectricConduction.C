#include "ElectricConduction.h"

registerMooseObject("TetraApp", ElectricConduction);

InputParameters
ElectricConduction::validParams()
{
  InputParameters params = ADKernelGrad::validParams();
  params.addClassDescription("Compute the electric conduction potential by : "
                             "$(\\sigma \\nabla u )$");
  return params;
}

ElectricConduction::ElectricConduction(const InputParameters & parameters)
  : ADKernelGrad(parameters),

    _resistance(getADMaterialProperty<Real>("resistance"))
{
}

ADRealVectorValue
ElectricConduction::precomputeQpResidual()
{
  return (1 / _resistance[_qp]) * _grad_u[_qp];
}
