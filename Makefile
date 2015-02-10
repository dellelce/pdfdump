
#
# pdf, 2015 by Antonio Dell'elce, antonio@dellelce.com
#

CC             = gcc
TARGET         = pdfdump

SHELL          = /bin/bash

CFILES         = ad.c
OFILES         = ad.o
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

ad.o: ad.c $(HFILES) ./pdf.h
	@echo "CC "ad.c
	@$(CC) -c $(CFLAGS) -o ad.o ad.c

 
#  
# clean
#    
     
clean:
	rm -f $(TARGET) $(OFILES) $(LOC_HFILES) *.exe

#
# redo
#

redo: clean all

