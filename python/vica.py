def integ(f,a,b):
    N=1000
    dx=(b-a)/N
    result=0
    x=a
    while x<=b:
      result+=f(x)
      x+=dx
    result*=dx
    return result
def getCoolString():
    return "snake"
