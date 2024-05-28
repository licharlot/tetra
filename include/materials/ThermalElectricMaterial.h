// This file is part of the MOOSE framework
// https://www.mooseframework.org
//
// All rights reserved, see COPYRIGHT for full restrictions
// https://github.com/idaholab/moose/blob/master/COPYRIGHT
//
// Licensed under LGPL 2.1, please see LICENSE for details
// https://www.gnu.org/licenses/lgpl-2.1.html

#pragma once

#include "Material.h"

template <bool is_ad>
class ThermalElectricMaterialTempl : public Material
{
public:
  static InputParameters validParams();

  ThermalElectricMaterialTempl(const InputParameters & parameters);

protected:
  virtual void computeQpProperties();

private:
  const bool _has_temp;

  const GenericVariableValue<is_ad> & _temperature;
  const Real _my_seebeck;
  GenericMaterialProperty<Real, is_ad> & _seebeck;
  const Function * const _seebeck_temperature_function;

  const Real _my_resistivity;
  GenericMaterialProperty<Real, is_ad> & _resistivity;
  const Function * const _resistivity_temperature_function;

  GenericMaterialProperty<Real, is_ad> & _Peltier;
  GenericMaterialProperty<Real, is_ad> & _Thomson;
  GenericMaterialProperty<Real, is_ad> & _elec_conductivity;
};

typedef ThermalElectricMaterialTempl<false> ThermalElectricMaterial;
typedef ThermalElectricMaterialTempl<true> ADThermalElectricMaterial;
