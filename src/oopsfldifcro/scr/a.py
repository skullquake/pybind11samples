import sys
sys.path.insert(1,'./lib')
import example
a=example.Obj('foo')
print(a.d)
a.setD('bar');
print(a.d)
#a.d='baz'#disallowed
