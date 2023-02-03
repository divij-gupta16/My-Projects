import numpy as np
import matplotlib.pyplot as plt
import cmath
def Psi(x,t,k):
    return ((2/np.pi)**(1/4)/(np.sqrt(1+complex(0,2)*t))) * np.exp(-(k**2/4)) * np.exp((-1/(1+complex(0,2)*t))*((x-k*complex(0,0.5))**2))
xmax = 100
v = 0.5
x = np.arange(-xmax, xmax, 0.01)
for i in range(0,100):
    plt.clf()
    plt.autoscale(False,'y')
    plt.plot(x, Psi(x,i,0.001).real, 'k') 
#    plt.plot(x, (Psi(x,i,0.001).real*Psi(x,i,0.00001).imag)**2, 'b')
    plt.pause(0.1)  
plt.show()

