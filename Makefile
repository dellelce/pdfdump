
#
# pdf, 2016 by Antonio Dell'elce, antonio@dellelce.com
#

CC             = gcc
TARGET         = pdf

SHELL          = /bin/bash

CFILES         = pdfdump.c
OFILES         = pdfdump.o
LDFLAGS	       = 


LOC_HFILES     = 
HFILES         = $(LOC_HFILES)

INCLUDES       =  -I.
DEBUG          = 
CFLAGS         = -Wall -O2  $(INCLUDES) $(DEBUG)
LIBS           = 


#
# --- RULES ---
#

all: $(TARGET)

$(TARGET):   $(OFILES)
	@echo "LINK " $(TARGET)
	@$(CC) -o $(TARGET) $(LDFLAGS) $(OFILES) $(LIBS)

#
# -- DEPS --
#

pdfdump.o: pdfdump.c $(HFILES) ./pdf.h
	@echo "CC "pdfdump.c
	@$(CC) -c $(CFLAGS) -o pdfdump.o pdfdump.c

 
#  
# clean
#    
     
clean:
	rm -f $(TARGET) $(OFILES) $(LOC_HFILES) *.exe

#
# redo
#

redo: clean all

