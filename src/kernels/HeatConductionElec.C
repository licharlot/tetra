#include "HeatConductionElec.h"

registerMooseObject("TetraApp", HeatConductionElec);

InputParameters
HeatConductionElec::validParams()
{
  InputParameters params = ADKernelGrad::validParams();
  params.addClassDescription("Compute the electric conduction potential by : "
                             "$(\\sigma \\nabla u )$");
  return params;
}

HeatConductionElec::HeatConductionElec(const InputParameters & parameters)
  : ADKernelGrad(parameters),

    _thermal_conductivity(getADMaterialProperty<Real>("thermal_conductivity"))
{
}

ADRealVectorValue
HeatConductionElec::precomputeQpResidual()
{
  return _thermal_conductivity[_qp] * _grad_u[_qp];
}
