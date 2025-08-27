
#pragma once

#include "ADKernelValue.h"

/**
 * This kernel calculates the heat source term corresponding to joule heating,
 * Q = J * E = J * grad V, where V is the electrical potential
 */
class TEJouleHeat : public ADKernelValue
{
public:
  static InputParameters validParams();

  TEJouleHeat(const InputParameters & parameters);

protected:
  virtual ADReal precomputeQpResidual() override;

private:
  /// Current density
  const ADMaterialProperty<RealVectorValue> & _J;
  /// Electric potential gradient
  const ADVariableGradient & _grad_elec;
};
