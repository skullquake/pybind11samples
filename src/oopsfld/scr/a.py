import sys
sys.path.insert(1,'./lib')
import example
a=example.Obj('foo')
print(a)
print(a.b)
a.b='bar'
print(a.b)
print(a)
