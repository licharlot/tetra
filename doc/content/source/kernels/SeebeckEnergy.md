# SeebeckEnergy

## Description

This kernels adds the following contribution to the electric potential residuals:
\begin{equation}
- \int \frac{S}{\rho_e} \nabla T \cdot \nabla \phi d\Omega
\end{equation}

where $S$ is the Seebeck coefficient, $\rho_e$ is the electric resistivity, $T$ is the temperature, and $\phi$ is the test function.


!syntax parameters /Kernels/SeebeckEnergy

!syntax inputs /Kernels/SeebeckEnergy

!syntax children /Kernels/SeebeckEnergy
