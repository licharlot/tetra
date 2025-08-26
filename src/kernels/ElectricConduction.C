#include "ElectricConduction.h"

registerMooseObject("TetraApp", ElectricConduction);

InputParameters
ElectricConduction::validParams()
{
  InputParameters params = ADKernelGrad::validParams();
  params.addClassDescription("Computes contribution from electric potential to  the electric conduction potential by : "
                             "$(\\sigma \\nabla V \\nabla \\phi )$");
  return params;
}

ElectricConduction::ElectricConduction(const InputParameters & parameters)
  : ADKernelGrad(parameters),

    _resistivity(getADMaterialProperty<Real>("resistivity"))
{
}

ADRealVectorValue
ElectricConduction::precomputeQpResidual()
{
  return (-1 / _resistivity[_qp]) * _grad_u[_qp];
}
