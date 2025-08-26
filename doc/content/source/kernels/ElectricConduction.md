# ElectricConduction

## Description

This kernels adds the following contribution to the electric potential residuals:
\begin{equation}
- \int \frac{1}{\rho_e} \nabla V \cdot \nabla \phi d\Omega
\end{equation}

where $\rho_e$ is the electric resistivity, $V$ is the electric potential, and $\phi$ is the test function.


!syntax parameters /Kernels/ElectricConduction

!syntax inputs /Kernels/ElectricConduction

!syntax children /Kernels/ElectricConduction
