// Including the "ADKernel" base class here so we can extend it
#include "ADKernelGrad.h"

/**
 * Computes the residual contribution: grad_u - S(T) * grad_temp
 */
class Conduction_Energy : public ADKernelGrad
{
public:
  static InputParameters validParams();

  Conduction_Energy(const InputParameters & parameters);

protected:
  /// ADKernel objects must override precomputeQpResidual
  virtual ADRealVectorValue precomputeQpResidual() override;

  /// The variables which hold the value for seabeck
  // const ADVariableValue & _temp;

  const ADMaterialProperty<Real> & _seebeck;
  const ADMaterialProperty<Real> & _resistance;
};
