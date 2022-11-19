#--------------------------makefile description-----------------------------#
#use for gcc/g++ compiler to complate/link
#edited:	miros
#edit time:	Sep 8, 2007
#------------------------compiler and compiler fags-------------------------#
COMPILER=gcc

#COMPLATEFLAGS=-g -D LINUX -D GUN_GCC -I ./../../common/
COMPLATEFLAGS=-g -D FREEBSD -D GUN_GCC -I ./../../common/

LINKER=ar

LINKFLAGS=cvr

DEBUGER=gdb

#--------------------------project settings---------------------------------#

PROJECTNAME=../libs/bsd/dbg/fastFT.a

INCLUDES=./MBCSFilter.c\
		 ./UCSFilter.c

#LIBS=
LIBS=

OBJECTS=./MBCSFilter.o ./UCSFilter.o

#EXTEDOBJECTS=
EXTEDOBJECTS=

#------------------------------make actions---------------------------------#
#use build to be default command
build:		complate	link

complate:
		@echo	"compiler: ${COMPILER}"
		@echo   "begin complate source files:"
		@echo	"${INCLUDES}"
		@$(COMPILER) $(COMPLATEFLAGS) $(INCLUDES) -c $^
		@echo	"complate succeeded"

recomplate:	cleanobjs	complate

link:
		@echo	"linker: ${LINKER}"
		@echo	"begin link object files:"
		@echo	"${OBJECTS}"
		@$(LINKER) $(LINKFLAGS) $(PROJECTNAME) $(OBJECTS)
		@echo	"Done!"

cleanobjs:
		@-rm $(OBJECTS)

cleanapps:
		@-rm $(PROJECTNAME)

cleanall:	cleanobjs	cleanapps

rebuild:	cleanall	build

build-clear:	build		cleanobjs

all:		rebuild	cleanobjs


#----------------------------exports labdles--------------------------------#
.PHONY:	all build rebuild complate recomplate link cleanobjs cleanapps cleanall build-clear

