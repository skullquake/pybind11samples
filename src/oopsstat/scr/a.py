import sys
sys.path.insert(1,'./lib')
import example
def a():
    lstobj=[]
    for i in range(8):
        lstobj.append(example.Obj(''))
    print(example.Obj.getC())
a()
print(example.Obj.getC())
