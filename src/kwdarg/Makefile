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
RUNENV=PYTHONHOME=/usr
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
BASENAMELIB=example
BUILDDIRLIB=./bin/build/lib
SRCDIRLIB=src/lib
SRCLIB:=$(shell find $(SRCDIRLIB) -name '*.cpp')
OBJSLIB:=$(addprefix $(BUILDDIRLIB)/,$(SRCLIB:%.cpp=%.o))
LIB=./lib/$(BASENAMELIB)$(SOEXT)
CFLAGSLIB=\
	-I./include\
	-I../cpputils/include\
	`pkg-config --cflags python3`\
	-O3\
	-Wall\
	-std=c++11
LDFLAGSLIB=\
	-L../cpputils/lib\
	`pkg-config --libs python3`
BASENAMEBIN=a
BUILDDIRBIN=./bin/build/app
SRCDIRBIN=src/app
SRCBIN:=$(shell find $(SRCDIRBIN) -name '*.cpp')
OBJSBIN:=$(addprefix $(BUILDDIRBIN)/,$(SRCBIN:%.cpp=%.o))
CFLAGSBIN=\
	-I./include\
	-I../cpputils/include\
	`pkg-config --cflags python3`\
	-O3\
	-Wall\
	-std=c++11
LDFLAGSBIN=\
	-L../cpputils/lib\
	`pkg-config --libs python3`
BIN=./bin/$(BASENAMEBIN)$(BINEXT)

all:\
	$(BIN)
$(BIN):$(OBJSBIN) $(LIB)
	@mkdir -p $(@D)
	@$(CXX)\
		$(CFLAGSBIN)\
		$(OBJSBIN)\
		$(LDFLAGSBIN)\
		-o $(BIN)
$(BUILDDIRBIN)/%.o: %.cpp
	@printf "generating $@...\n"
	@mkdir -p $(@D)
	@$(CXX)\
		$(CFLAGSBIN)\
		-c $<\
		$(LDFLAGSBIN)\
		-o $@

$(LIB):$(OBJSLIB)
	@mkdir -p $(@D)
	@$(CXX)\
		$(CFLAGSLIB)\
		$(OBJSLIB)\
		-shared\
		$(LDFLAGSLIB)\
		-o $(LIB)
$(BUILDDIRLIB)/%.o: %.cpp
	@printf "generating $@...\n"
	@mkdir -p $(@D)
	@$(CXX)\
		$(CFLAGSLIB)\
		-c $<\
		-fPIC\
		$(LDFLAGSLIB)\
		-o $@
.phony:\
	run\
	clean\
	lsvar
clean:
	@rm -r ./bin ./lib
run: $(BIN)
	$(RUNENV) $(BIN) ./scr/a.py
test:
	echo $(BIN)
	echo $(LIB)
lsvar:
	@echo $(BIN)
	@echo $(OBJS)
	@echo $(SRC)
	@echo $(SRCDIR)
	@echo $(PREFIX)




