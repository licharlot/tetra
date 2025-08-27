// Including the "ADKernel" base class here so we can extend it
#include "ADKernelGrad.h"

/**
 * Computes the residual contribution: sigma * grad_elec grad_phi
 */
class ElectricConduction : public ADKernelGrad
{
public:
  static InputParameters validParams();

  ElectricConduction(const InputParameters & parameters);

protected:
  virtual ADRealVectorValue precomputeQpResidual() override;

  const ADMaterialProperty<Real> & _resistivity;
};
