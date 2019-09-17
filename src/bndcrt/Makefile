OS=$(shell $(CXX) -dumpmachine)
ifneq (,$(findstring mingw,$(OS)))
SOEXT?=`python3-config --extension-suffix`
BINEXT?=.exe
else
SOEXT?=`python3-config --extension-suffix`
BINEXT?=.out
endif
ifneq (,$(findstring mingw,$(OS)))
RUNENV=PYTHONHOME=/usr
else
RUNENV=
endif

ifeq ($(PREFIX),)
PREFIX := /usr/local
endif
CC=gcc
CXX=g++
AR=ar
PYTHON=python
PYTHON3=python3
SRCPY=./scr/a.py
BUILDDIR=./bin/build
BASENAME=example
BIN=./bin/$(BASENAME)$(BINEXT)
LIB=./lib/$(BASENAME)$(SOEXT)
SRCDIR=src
SRC:=$(shell find $(SRCDIR) -name '*.cpp')
OBJS:=$(addprefix $(BUILDDIR)/,$(SRC:%.cpp=%.o))
CFLAGS=\
	-I./include\
	-I../cpputils/include\
	`pkg-config --cflags python3`\
	-O3\
	-Wall\
	-std=c++11
LDFLAGS=\
	-L../cpputils/lib\
	`pkg-config --libs python3`
all:\
	$(LIB)
$(LIB):$(OBJS)
	@mkdir -p $(@D)
	@$(CXX)\
		$(CFLAGS)\
		$(OBJS)\
		-shared\
		$(LDFLAGS)\
		-o $(LIB)
$(BUILDDIR)/%.o: %.cpp
	@printf "generating $@...\n"
	@mkdir -p $(@D)
	@$(CXX)\
		$(CFLAGS)\
		-c $<\
		-fPIC\
		$(LDFLAGS)\
		-o $@
.phony:\
	run\
	clean\
	lsvar
clean:
	@rm -r ./bin ./lib
run:
	$(PYTHON3) $(SRCPY)
lsvar:
	@echo $(BIN)
	@echo $(OBJS)
	@echo $(SRC)
	@echo $(SRCDIR)
	@echo $(PREFIX)




