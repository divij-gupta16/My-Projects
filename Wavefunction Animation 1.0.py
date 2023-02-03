import numpy as np
import matplotlib.pyplot as plt
import cmath
def Psi(x,c,t):
    return (1/(np.pi*2))*np.exp(-(x-c*t)**2) * np.exp(5j*(x-c*t))
vel = 0.3
xmax = 20
x = np.arange(-1, xmax, 0.0005)
for i in range(0,int(xmax/vel)):
    plt.clf()
    plt.plot(x, Psi(x,vel,i).real, 'k')
    plt.plot(x, 1000*(Psi(x,vel,i).real*Psi(x,vel,i).imag)**2, 'b')
    plt.pause(0.000000001)
plt.show()
