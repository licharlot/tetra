// Including the "ADKernel" base class here so we can extend it
#include "ADKernelGrad.h"

/**
 * Computes the residual contribution: grad_u - S(T) * grad_temp
 */
class HeatConductionElec : public ADKernelGrad
{
public:
  static InputParameters validParams();

  HeatConductionElec(const InputParameters & parameters);

protected:
  /// ADKernel objects must override precomputeQpResidual
  virtual ADRealVectorValue precomputeQpResidual() override;

  const ADMaterialProperty<Real> & _thermal_conductivity;
};
