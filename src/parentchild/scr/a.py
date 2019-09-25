import sys
sys.path.insert(1,'./lib')
import example
print(example.Type.Cat);
print(example.getAnimal(example.Type.Cat))
print(example.Type.Dog);
print(example.getAnimal(example.Type.Dog))
