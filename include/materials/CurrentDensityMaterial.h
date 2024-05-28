//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#pragma once

#include "Material.h"

/**
 * This material automatically declares as functor material properties whatever is passed to it
 * through the parameters 'prop_names' and uses the gradients of the functors from 'prop_values'
 * as the values for those properties.
 */

class CurrentDensityMaterial : public Material
{
public:
  static InputParameters validParams();

  CurrentDensityMaterial(const InputParameters & parameters);

protected:
  virtual void computeQpProperties();

  const ADVariableGradient & _grad_elec;
  const ADVariableGradient & _grad_temp;
  const ADMaterialProperty<Real> & _seebeck;
  const ADMaterialProperty<Real> & _resistivity;
  ADMaterialProperty<RealVectorValue> & _current_density;
};
