# PeltierHeat

## Description

This kernels adds the following contribution to the heat conduction residuals:
\begin{equation}
- \int S T \vec{J} \cdot \nabla \phi d\Omega
\end{equation}

where $S$ is the Seebeck coefficient, $T$ is the temperature, $\vec{J}$ is the current density and $\phi$ is the test function.


!syntax parameters /Kernels/PeltierHeat

!syntax inputs /Kernels/PeltierHeat

!syntax children /Kernels/PeltierHeat
