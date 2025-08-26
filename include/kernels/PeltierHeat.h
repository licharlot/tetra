#include "ADKernelGrad.h"

/**
 * Computes the residual contribution: ST J nabla phi
 */
class PeltierHeat : public ADKernelGrad
{
public:
  static InputParameters validParams();

  PeltierHeat(const InputParameters & parameters);

protected:
  virtual ADRealVectorValue precomputeQpResidual() override;

  /// Peltier coefficient
  const ADMaterialProperty<Real> & _peltier;
  /// Current density
  const ADMaterialProperty<RealVectorValue> & _J;
};
