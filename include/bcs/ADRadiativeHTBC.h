#pragma once

#include "ADIntegratedBC.h"

/**
 * Boundary condition for convective heat flux where temperature and heat transfer coefficient are
 * given by material properties.
 */
class ADRadiativeHTBC : public ADIntegratedBC
{
public:
  static InputParameters validParams();

  ADRadiativeHTBC(const InputParameters & parameters);

protected:
  virtual ADReal computeQpResidual() override;

  /// Stefan-Boltzmann constant
  const ADReal _stefan_boltzmann_constant;

  /// Area of the boundary
  const ADReal _Area;

  /// _Celsius toggle
  const bool _Celsius;
  /// Far-field temperature variable
  const ADMaterialProperty<Real> & _T_infinity;

  /// Convective heat transfer coefficient
  const ADMaterialProperty<Real> & _emissivity;
};
