#include "SeebeckEnergy.h"

registerMooseObject("TetraApp", SeebeckEnergy);

InputParameters
SeebeckEnergy::validParams()
{
  InputParameters params = ADKernelGrad::validParams();
  params.addClassDescription("Compute the energy potential by : "
                             "$(\\sigma \\alpha \\nabla u  )$");
  params.addRequiredCoupledVar("temp", "temperature_variable");
  return params;
}

SeebeckEnergy::SeebeckEnergy(const InputParameters & parameters)
  : ADKernelGrad(parameters),

    _grad_temp(adCoupledGradient("temp")),

    _seebeck(getADMaterialProperty<Real>("seebeck")),
    _resistance(getADMaterialProperty<Real>("resistance"))
{
}

ADRealVectorValue
SeebeckEnergy::precomputeQpResidual()
{
  return (_seebeck[_qp] / _resistance[_qp]) * _grad_temp[_qp];
}
