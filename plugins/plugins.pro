
TEMPLATE = subdirs

CONFIG += ordered

DIRS = $$system(dir /AD /B)
DIRS -= template

SUBDIRS = $$DIRS
