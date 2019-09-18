import sys
sys.path.insert(1,'./lib')
import example
print(example.add())
print(example.sub())
o=example.Obj("a")
print(o)
print(o.getA())
o.setA("b")
print(o.getA())
