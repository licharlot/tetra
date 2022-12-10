#include "SeebeckEnergy.h"

registerMooseObject("TetraApp", SeebeckEnergy);

InputParameters
SeebeckEnergy::validParams()
{
  InputParameters params = ADKernel::validParams();
  params.addClassDescription("Compute the energy potential by : "
                             "$(\\sigma \\alpha \\nabla u  )$");
  // params.addRequiredCoupledVar("temp", "temperature_variable");

  // params.addRequiredParam<MaterialPropertyName>(
  //     "seebeck_val",
  //     "Material property providing Seebeck value of the material (It can be a val or a temp "
  //     "dependent function).");
  return params;
}

SeebeckEnergy::SeebeckEnergy(const InputParameters & parameters)
  : ADKernelGrad(parameters),

    _seebeck(getADMaterialProperty<Real>("seebeck")),
    _resistance(getADMaterialProperty<Real>("resistance"))
{
}

ADRealVectorValue
SeebeckEnergy::precomputeQpResidual()
{
  // return _seebeck_val[_qp] * _grad_u[_qp];
  // return _grad_u[_qp] - _seebeck[_qp] * _grad_temp[_qp];

  return (_seebeck[_qp] / _resistance[_qp]) * _grad_u[_qp];
}
