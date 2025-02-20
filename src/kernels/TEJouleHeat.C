//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "TEJouleHeat.h"

registerMooseObject("TetraApp", TEJouleHeat);

InputParameters
TEJouleHeat::validParams()
{
  InputParameters params = ADKernelValue::validParams();
  params.addParam<MaterialPropertyName>("current_density",
                                        "Current density material for joule heating.");

  params.addRequiredCoupledVar("elec", "Electrical potential variable");
  params.addClassDescription("Calculates the heat source term corresponding to electrostatic Joule "
                             "heating, with Jacobian contributions calculated using the automatic "
                             "differentiation system.");
  return params;
}

TEJouleHeat::TEJouleHeat(const InputParameters & parameters)
  : ADKernelValue(parameters),
    _J(getADMaterialProperty<RealVectorValue>("current_density")),
    _grad_elec(adCoupledGradient("elec"))
{
}

ADReal
TEJouleHeat::precomputeQpResidual()
{
  return -_grad_elec[_qp] * _J[_qp];
}
