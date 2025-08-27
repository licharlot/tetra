#pragma once

#include "Material.h"

/**
 * This material declares the current density material using the electric potential
 * and the seebeck effect
 */

class CurrentDensityMaterial : public Material
{
public:
  static InputParameters validParams();

  CurrentDensityMaterial(const InputParameters & parameters);

protected:
  virtual void computeQpProperties();

  /// Electric potential gradient
  const ADVariableGradient & _grad_elec;
  /// Temperature gradient
  const ADVariableGradient & _grad_temp;
  /// Seebeck coefficient
  const ADMaterialProperty<Real> & _seebeck;
  /// Electric resistivity
  const ADMaterialProperty<Real> & _resistivity;
  /// Current density
  ADMaterialProperty<RealVectorValue> & _current_density;
};
