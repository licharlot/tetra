# TEJouleHeat

## Description

This kernels adds the heat source due to the Joule heating in presence the Joule effect:
\begin{equation}
- \int \| \nabla V \cdot \vec{J} \|\phi d\Omega
\end{equation}

where $V$ is the electric potential, $\vec{J}$ is the current density.


!syntax parameters /Kernels/TEJouleHeat

!syntax inputs /Kernels/TEJouleHeat

!syntax children /Kernels/TEJouleHeat
