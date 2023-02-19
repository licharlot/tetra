//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "ADRadiativeHTBC.h"
#include "MathUtils.h"

registerMooseObject("TetraApp", ADRadiativeHTBC);

InputParameters
ADRadiativeHTBC::validParams()
{
  InputParameters params = ADIntegratedBC::validParams();
  params.addClassDescription(
      "Convective heat transfer boundary condition with temperature and heat "
      "transfer coefficent given by material properties.");

  params.addParam<Real>("stefan_boltzmann_constant", 5.670367e-8, "The Stefan-Boltzmann constant.");
  params.addParam<Real>("Area", 1, "Area of the boundary");
  params.addParam<bool>(
      "Celsius", false, "If true, the temperature is in Celsius, otherwise Kelvin");
  params.addRequiredParam<MaterialPropertyName>(
      "T_infinity", "Material property for far-field temperature (in Celsuis)");
  params.addRequiredParam<MaterialPropertyName>("emissivity", "Emmissivity of the boundary");

  return params;
}

ADRadiativeHTBC::ADRadiativeHTBC(const InputParameters & parameters)
  : ADIntegratedBC(parameters),
    _stefan_boltzmann_constant(getParam<Real>("stefan_boltzmann_constant")),
    _Area(getParam<Real>("Area")),
    _Celsius(getParam<bool>("Celsius")),
    _T_infinity(getADMaterialProperty<Real>("T_infinity")),
    _emissivity(getADMaterialProperty<Real>("emissivity"))

{
}

ADReal
ADRadiativeHTBC::computeQpResidual()
{
  if (_Celsius)
    return _test[_i][_qp] * _emissivity[_qp] * _Area * _stefan_boltzmann_constant *
           MathUtils::positivePart((MathUtils::pow(_u[_qp] + 273.15, 4) -
                                    MathUtils::pow(_T_infinity[_qp] + 273.15, 4)));
  else
    return _test[_i][_qp] * _emissivity[_qp] * _Area * _stefan_boltzmann_constant *
           MathUtils::positivePart(
               (MathUtils::pow(_u[_qp], 4) - MathUtils::pow(_T_infinity[_qp], 4)));
}
