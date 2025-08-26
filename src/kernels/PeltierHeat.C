#include "PeltierHeat.h"

registerMooseObject("TetraApp", PeltierHeat);

InputParameters
PeltierHeat::validParams()
{
  InputParameters params = ADKernelGrad::validParams();
  params.addClassDescription("Computes the heat source from Peltier and Thomson effects : "
                             "$ ST J \\nabla \\phi$");
  return params;
}

PeltierHeat::PeltierHeat(const InputParameters & parameters)
  : ADKernelGrad(parameters),
    _peltier(getADMaterialProperty<Real>("peltier")),
    _J(getADMaterialProperty<RealVectorValue>("current_density"))
{
}

ADRealVectorValue
PeltierHeat::precomputeQpResidual()
{
  return -_peltier[_qp] * _J[_qp];
}
