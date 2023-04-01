//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "SeebeckEnergyBC.h"

registerMooseObject("TetraApp", SeebeckEnergyBC);

InputParameters
SeebeckEnergyBC::validParams()
{
  InputParameters params = ADIntegratedBC::validParams();
  params.addRequiredCoupledVar("temp", "Temperature");
  params.addClassDescription("Compute the outflow boundary condition.");
  return params;
}

SeebeckEnergyBC::SeebeckEnergyBC(const InputParameters & parameters)
  : ADIntegratedBC(parameters),
    _grad_temp(adCoupledGradient("temp")),
    _seebeck(getADMaterialProperty<Real>("seebeck")),
    _resistance(getADMaterialProperty<Real>("resistance"))
// _thermal_conductivity(getADMaterialProperty<Real>("thermal_conductivity"))
{
}

ADReal
SeebeckEnergyBC::computeQpResidual()
{
  return -_test[_i][_qp] * (_seebeck[_qp] / _resistance[_qp]) * _grad_temp[_qp] * _normals[_qp];
}
