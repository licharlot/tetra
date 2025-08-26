#include "SeebeckEnergy.h"

registerMooseObject("TetraApp", SeebeckEnergy);

InputParameters
SeebeckEnergy::validParams()
{
  InputParameters params = ADKernelGrad::validParams();
  params.addClassDescription("Computes the contribution of the Seebeck effect "
                             "to the current density continuity equation: "
                             "$(\\sigma S \\nabla T \\nabla \\phi )$");
  params.addRequiredCoupledVar("temp", "Temperature variable");
  return params;
}

SeebeckEnergy::SeebeckEnergy(const InputParameters & parameters)
  : ADKernelGrad(parameters),

    _grad_temp(adCoupledGradient("temp")),

    _seebeck(getADMaterialProperty<Real>("seebeck")),
    _resistivity(getADMaterialProperty<Real>("resistivity"))
{
}

ADRealVectorValue
SeebeckEnergy::precomputeQpResidual()
{
  return -(_seebeck[_qp] / _resistivity[_qp]) * _grad_temp[_qp];
}
