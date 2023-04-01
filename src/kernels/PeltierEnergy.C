#include "PeltierEnergy.h"

registerMooseObject("TetraApp", PeltierEnergy);

InputParameters
PeltierEnergy::validParams()
{
  InputParameters params = ADKernelGrad::validParams();
  params.addClassDescription("Compute the energy potential by : "
                             "$(\\nabla \\alpha T \\nabla u)$");
  params.addRequiredCoupledVar("elec", "Electrostatic potential for joule heating.");

  // params.addRequiredParam<MaterialPropertyName>(
  //     "seebeck_val",
  //     "Material property providing Seebeck value of the material (It can be a val or a temp "
  //     "dependent function).");
  return params;
}

PeltierEnergy::PeltierEnergy(const InputParameters & parameters)
  : ADKernelGrad(parameters),

    // _temp(adCoupledValue("temp")),
    _grad_elec(adCoupledGradient("elec")),

    _seebeck(getADMaterialProperty<Real>("seebeck")),
    _resistance(getADMaterialProperty<Real>("resistance"))
{
}

ADRealVectorValue
PeltierEnergy::precomputeQpResidual()
{
  // return _seebeck_val[_qp] * _grad_u[_qp];
  // return _grad_u[_qp] - _seebeck[_qp] * _grad_temp[_qp];

  return (_seebeck[_qp] / _resistance[_qp]) * _u[_qp] * _grad_elec[_qp];
}
