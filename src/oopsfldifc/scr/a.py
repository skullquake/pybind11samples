import sys
sys.path.insert(1,'./lib')
import example
a=example.Obj('foo')
print(a.a)
a.a='bar'
print(a.a)
