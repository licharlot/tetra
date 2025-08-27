#include "ADKernelGrad.h"

/**
 * Computes the residual contribution: sigma S grad_T grad_phi
 */
class SeebeckEnergy : public ADKernelGrad
{
public:
  static InputParameters validParams();

  SeebeckEnergy(const InputParameters & parameters);

protected:
  virtual ADRealVectorValue precomputeQpResidual() override;

  /// Temperature gradient
  const ADVariableGradient & _grad_temp;
  /// Seebeck coefficient
  const ADMaterialProperty<Real> & _seebeck;
  /// Electric resistivity
  const ADMaterialProperty<Real> & _resistivity;
};
