OS=$(shell $(CXX) -dumpmachine)
ifneq (,$(findstring mingw,$(OS)))
SOEXT?=dll
BINEXT?=exe
else
SOEXT?=so
BINEXT?=out
endif
ifneq (,$(findstring mingw,$(OS)))
RUNENV=PYTHONHOME=/usr PYTHONPATH='C:/opt/msys64/mingw64/lib/python27.zip':'C:/opt/msys64/mingw64/lib/python2.7':'C:/opt/msys64/mingw64/lib/python2.7/plat-win32':'C:/opt/msys64/mingw64/lib/python2.7/lib-tk':'C:/opt/msys64/mingw64/lib/python2.7/lib-old':'C:/opt/msys64/mingw64/lib/python2.7/lib-dynload':'C:/building/msys64/mingw64':'C:/opt/msys64/mingw64/lib/python2.7/site-packages'
else
RUNENV=
endif

ifeq ($(PREFIX),)
PREFIX := /usr/local
endif
CC=gcc
CXX=g++
AR=ar
BUILDDIR=./bin/build
BIN=./bin/a.$(BINEXT)
SRCDIR=src
SRC:=$(shell find $(SRCDIR) -name '*.cpp')
OBJS:=$(addprefix $(BUILDDIR)/,$(SRC:%.cpp=%.o))
CFLAGS=\
	-I./include\
	-I../cpputils/include\
	`pkg-config --cflags python`
LDFLAGS=\
	-L../cpputils/lib\
	`pkg-config --libs python`
DBPATH=./db
DBPORT=5432
DBHOST=127.0.0.1
DBNAM=test
all:\
	$(BIN)
$(BIN):$(OBJS)
	@$(CXX)\
		$(CFLAGS)\
		$(OBJS)\
		$(LDFLAGS)\
		-o $(BIN)
$(BUILDDIR)/%.o: %.cpp
	@printf "generating $@...\n"
	@mkdir -p $(@D)
	@$(CXX)\
		$(CFLAGS)\
		-c $<\
		$(LDFLAGS)\
		-o $@
.phony:\
	run	\
	clean	\
	lsvar	\
	dbrm	\
	dbmk	\
	dbinit	\
	dbstart	\
	dbstop	\
	dbpsql	\
	dbsize	\
	dbls	\
	dbdrop	

clean:
	@rm -r $(BIN) $(BUILDDIR)
run: $(BIN)
	$(RUNENV) $(BIN)
deploy: $(BIN)
	chmod ugo+rwx $(BIN)
	cp $(BIN) /usr/lib/cgi-bin/
test: deploy
	curl http://localhost:8080/cgi-bin/a.out
lsvar:
	@echo $(BIN)
	@echo $(OBJS)
	@echo $(SRC)
	@echo $(SRCDIR)
	@echo $(PREFIX)
dbmk:
	initdb \
		$(DBPATH)
dbrm:
	rm \
		-r $(DBPATH)
dbstart:
	pg_ctl \
		-D $(DBPATH) \
		-o "-p $(DBPORT)" \
		start
dbstop:
	pg_ctl \
		-D $(DBPATH) \
		-o "-p $(DBPORT)" \
		stop 
dbpsql:
	psql \
		-h $(DBHOST) \
		-p $(DBPORT) \
		$(DBNAM)
dbvacuum:
	psql \
		-P pager=off\
		-h $(DBHOST) \
		-p $(DBPORT) \
		-d $(DBNAM)\
		-c "vacuum full;"
dbsize:
	psql \
		-P pager=off\
		-h $(DBHOST)\
		-p $(DBPORT)\
		-d $(DBNAM)\
		-c "select pg_database_size('$(DBNAM)'),pg_size_pretty( pg_database_size('$(DBNAM)'));"
dbls:
	psql \
		-P pager=off\
		-h $(DBHOST) \
		-p $(DBPORT) \
		-d postgres \
		-c "SELECT * FROM pg_catalog.pg_tables;"

dbdrop:
	psql \
		-P pager=off\
		-h $(DBHOST) \
		-p $(DBPORT) \
		-d postgres \
		-c "drop database $(DBNAM);"
dbinit:
	psql \
		-P pager=off\
		-h $(DBHOST) \
		-p $(DBPORT) \
		-d postgres\
		-c "create database $(DBNAM);"
