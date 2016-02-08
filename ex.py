# https://mkaz.github.io/2012/10/10/python-string-format/
# Python Essential Reference, Fourth Edition (2009).pdf
# python -m pdb ex.py
# python -m cProfile ex.py
import sys
import time

# It is faster to use 'from math import sqrt' and 'sqrt(x)' rather
# than typing 'math.sqrt(x)'.
from math import sqrt;
class MyClass:
    """A simple example class"""
    i = 12345
    def f(self):
        return 'hello world'

class MyMath(object):
  @staticmethod
  def add(x,y):
    return x + y

class Date(object):
  def __init__(self,year, month, day):
    self.year = year
    self.month = month
    self.day = day
  @classmethod
  def now(cls):
    t = time.localtime()
    return cls(t.tm_year, t.tm_mon, t.tm_mday)
  @classmethod
  def tomorrow(cls):
    t = time.localtime(time.time()+86400)
    return cls(t.tm_year, t.tm_mon, t.tm_mday)
  # Modify string conversion
  def __str__(self):
    return "%02d/%02d/%04d" % (self.day, self.month, self.year)

def print_matches(matchtext):
  """
  print_matchers
  Coroutine: a type of function is created by using the yield
  as an expression (yield).
  """
  print "Looking for", matchtext
  while True:
    line = (yield) # Get a line of text
    if matchtext in line:
      print line

def main(argv):
  for a in argv:
    print(a)
  print("{:.2f}".format(3.1415926));
  s1 = "so much depends upon {}".format("a red wheel barrow")
  s2 = "glazed with {} water beside the {} chickens".format("rain", "white")
  print(s1)
  print(s2)
  s1 = " {0} is better than {1} ".format("emacs", "vim")
  s2 = " {1} is better than {0} ".format("emacs", "vim")
  print(s1)
  print(s2)
  pi = 3.14159
  print(" pi = %1.2f " % pi)
  s1 = "cats"
  s2 = "dogs"
  s3 = " %s and %s living together" % (s1, s2)
  print(s3)
  set = " ({0}, {1}, {2}, {3}, {4}, {5}, {6}, {7}) ".format("a","b","c","d","e","f","g", "h")
  print(set)
  madlib = " I {verb} the {object} off the {place} ".format(verb="took", object="cheese", place="table")
  print(madlib)
  str = "Oh {0}, {0}! wherefore art thou {0}?".format("Romeo")
  print(str)
  print("{0:d} - {0:x} - {0:o} - {0:b} ".format(21))

  ## defining formats
  email_f = "Your email address was {email}".format

  ## use elsewhere
  print(email_f(email="bob@example.com"))

  ## Escaping Braces
  print(" The {0} set is often represented as {{0}}".format("empty"))
  print(" The {0} set is often represented as {0}".format("empty"))

  a = "Hello World"
  b = 'Python is groovy'
  c = """Computer says 'No'"""
  print '''Content-type: text/html
  <h1> Hello World </h1>
  Click <a href="http://www.python.org">here</a>.
  '''
  matcher = print_matches("python")
  matcher.next()
  matcher.send("Hello World")
  matcher.send("python coroutines is cool")
  matcher.send("yow!")
  matcher.close()
  print issubclass.__doc__
  print print_matches.__doc__

  a = 37
  b = a
  c = []
  c.append(a)
  print sys.getrefcount(a)
  del a
  b = 36
  c[0] = 2.0
  print sys.getrefcount(b)
  shengliangsong = 99999
  print sys.getrefcount(shengliangsong)
  print sys.getrefcount(12345)
  print sys.getrefcount(1)
  print sys.getrefcount(12)
  print sys.getrefcount(123)
  print sys.getrefcount(1234)
  print sys.getrefcount(12345)

  a = Date.now()
  print(a)
  b = Date.tomorrow()
  print(b)
  c = Date.now()
  print(b)
  print MyMath.add(3,4)
  print sqrt(9)

  x = MyClass()
  print x.i
  print x.f()
  print x.__doc__
  pass


if __name__ == '__main__':
  main(sys.argv)
