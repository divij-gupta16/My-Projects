from graphics import *
import cmath
from scipy.special import gamma

win = GraphWin('Trial 1', 1200, 800) # give title and dimensions

InitialGrid = [[0 for q in range(21)] for k in range(21)]

for c in range(21):
    for i in range(21):
        InitialGrid[i][c] = Point(350 + i*25, 150 + c*25)

class TPoint():
    def __init__(self, value):
        self.value = value
        self.p = Point(350 + (250 + self.value.real*50), 150 + (250 - self.value.imag*50))
    def Add(self,val):
        self.value += val
        self.p = Point(350 + (250 + self.value.real*50), 150 + (250 - self.value.imag*50))
    def Multiply(self,val):
        self.value *= val
        self.p = Point(350 + (250 + self.value.real*50), 150 + (250 - self.value.imag*50))
    def SquareRoot(self):
        self.value = cmath.sqrt(self.value)
        self.p = Point(350 + (250 + self.value.real*50), 150 + (250 - self.value.imag*50))
    def Invert(self):
        if self.value == complex(0,0):
            self.value = complex(0,0)
        else:
            self.value = 1/self.value
        self.p = Point(350 + (250 + self.value.real*50), 150 + (250 - self.value.imag*50))
    def Exponent(self,val):
        self.value = val**self.value
        self.p = Point(350 + (250 + self.value.real*50), 150 + (250 - self.value.imag*50))
    def Base(self,val):
        if (self.value == 0):
            self.value = 0
        else:
            self.value = self.value**val
        self.p = Point(350 + (250 + self.value.real*50), 150 + (250 - self.value.imag*50))
    def Sin(self):
        self.value = cmath.sin(self.value)
        self.p = Point(350 + (250 + self.value.real*50), 150 + (250 - self.value.imag*50))
    def Cos(self):
        self.value = cos(self.value)
        self.p = Point(350 + (250 + self.value.real*50), 150 + (250 - self.value.imag*50))
    def Tan(self):
        self.value = tan(self.value)
        self.p = Point(350 + (250 + self.value.real*50), 150 + (250 - self.value.imag*50))
    def Zeta(self):
        tot = 0
        for ah in range(100000):
            tot += 1/((1+ah)**self.value)
        self.value = tot
        self.p = Point(350 + (250 + self.value.real*50), 150 + (250 - self.value.imag*50))
    def Area(self):
        self.value = self.value**2 * pi
        self.p = Point(350 + (250 + self.value.real*50), 150 + (250 - self.value.imag*50))
    def Quadratic(self,a,b,c):
        self.value = a*(self.value**2) + b*self.value + c
        self.p = Point(350 + (250 + self.value.real*50), 150 + (250 - self.value.imag*50))
    def Cubic(self,a,b,c,d):
        self.value = a*(self.value**3) + b*(self.value**2) + c*self.value + d
        self.p = Point(350 + (250 + self.value.real*50), 150 + (250 - self.value.imag*50))
    def Quartic(self,a,b,c,d,e):
        self.value = a*(self.value**4) + b*(self.value**3) + c*(self.value**2) + d*self.value + e
        self.p = Point(350 + (250 + self.value.real*50), 150 + (250 - self.value.imag*50))
    def Sinh(self):
        self.value = sinh(self.value)
        self.p = Point(350 + (250 + self.value.real*50), 150 + (250 - self.value.imag*50))
    def Cosh(self):
        self.value = cosh(self.value)
        self.p = Point(350 + (250 + self.value.real*50), 150 + (250 - self.value.imag*50))
    def Tanh(self):
        self.value = tanh(self.value)
        self.p = Point(350 + (250 + self.value.real*50), 150 + (250 - self.value.imag*50))
    def Lorentz(self, beta, v):
        Gamma = 1/((cmath.sqrt(1 - beta**2)))
        T = Gamma*(self.value.real - (v*self.value.imag))
        X = Gamma*(self.value.real - ((v/25)*self.value.imag))
        self.value = complex(T,X)
        self.p = Point(350 + (250 + self.value.real*50), 150 + (250 - self.value.imag*50)) 
    def Mobius(self,a,b,c,d):
        self.value = (a*self.value + b)/(c*self.value + d)
        self.p = Point(350 + (250 + self.value.real*50), 150 + (250 - self.value.imag*50))
    def Logarithm(self, base):
        self.value = cmath.log(self.value, base)
        self.p = Point(350 + (250 + self.value.real*50), 150 + (250 - self.value.imag*50))
    def Gamma(self):
        if self.value == complex(0,0):
            self.value = self.value
        else:
            self.value = gamma(self.value)
        self.p = Point(350 + (250 + self.value.real*50), 150 + (250 - self.value.imag*50))
TPoints = [[0 for d in range(21)] for z in range(21)]

def drawInitialGrid():        
    for l in range(21):
        for m in range(21):
            IG = Circle(InitialGrid[m][l], 2)
            TPoints[m][l] = TPoint(complex(-5+m/2,5-l/2))
            if (l==10):
                IG.setFill(color_rgb(150,150,150))
            elif (m==10):
                IG.setFill(color_rgb(150,150,150))
            else:
                IG.setFill(color_rgb(230, 230, 230))
            IG.setWidth(0)
            IG.draw(win)

    for v in range(21):
        for n in range(21):
            if (n < 20):
                ILX = Line(TPoints[n][v].p, TPoints[n+1][v].p)
            if (v < 20):
                ILY = Line(TPoints[n][v].p, TPoints[n][v+1].p)
            if (n==10 and v<20):
                ILY.setOutline(color_rgb(150,150,150))
            else:
                if (v<20):
                    ILY.setOutline(color_rgb(230, 230, 230))            
            if (v==10 and n<20):
                ILX.setOutline(color_rgb(150,150,150))
            else:
                if (n<20):
                    ILX.setOutline(color_rgb(230, 230, 230))
            if (n<20):    
                ILX.setWidth(1)
                ILX.draw(win)
            if (v<20):
                ILY.setWidth(1)
                ILY.draw(win)

def drawFinalGrid():
    for qw in range(21):
        for er in range(21):
            TPoints[qw][er].Sin() # Enter function
            FG = Circle(TPoints[qw][er].p, 2)
            if (qw==10):
                FG.setFill('red')
            elif (er==10):
                if (qw > 10):
                    FG.setFill('blue')
                else:
                    FG.setFill('black')
            else:
                FG.setFill('green')
            FG.setWidth(0)
            FG.draw(win)
    for h in range(21):
        for e in range(21):
            if (e < 20):
                FLX = Line(TPoints[e][h].p, TPoints[e+1][h].p)
            if (h < 20):
                FLY = Line(TPoints[e][h].p, TPoints[e][h+1].p)
            if (e==10 and h<20):
                FLY.setOutline('red')
            else:
                if (h<20):
                    FLY.setOutline('green')            
            if (h==10 and e<20):
                if (e > 10):
                    FLX.setOutline('blue')
                else:
                    FLX.setOutline('black')
            else:
                if (e<20):
                    FLX.setOutline('green')
            if (e<20):    
                FLX.setWidth(1)
                FLX.draw(win)
            if (h<20):
                FLY.setWidth(1)
                FLY.draw(win)

drawInitialGrid()
drawFinalGrid()
