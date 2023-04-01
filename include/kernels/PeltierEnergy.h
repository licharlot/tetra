// Including the "ADKernel" base class here so we can extend it
#include "ADKernelGrad.h"

/**
 * Computes the residual contribution: grad_u - S(T) * grad_temp
 */
class PeltierEnergy : public ADKernelGrad
{
public:
  static InputParameters validParams();

  PeltierEnergy(const InputParameters & parameters);

protected:
  /// ADKernel objects must override precomputeQpResidual
  virtual ADRealVectorValue precomputeQpResidual() override;

  /// The variables which hold the value for seabeck
  // const ADVariableValue & _temp;
  const ADVariableGradient & _grad_elec;
  const ADMaterialProperty<Real> & _seebeck;
  const ADMaterialProperty<Real> & _resistance;
};
