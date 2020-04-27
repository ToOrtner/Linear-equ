#!/usr/bin/python
from src.scripts.fabricate import *
from src.scripts.settings import *
from src.scripts.utils import listfiles
from sys import argv

# Acciones
def build():
  compile()
  link()

def compile():
  for source in sources:
    run(compiler, '-std=c++11', '-O2', '-c', source+'.cpp', '-o', source+'.o')

def link():
  objects = [s+'.o' for s in sources]
  run(compiler, '-o', executable, objects)

def clean():
  autoclean()


def test():
  build()
  import unittest
  unittest.main(module='src.scripts.tptests', exit=False, argv=argv[:1], verbosity=3)

main()
