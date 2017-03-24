IDIR =../include
CC=arm-linux-gcc
CFLAGS=-I$(IDIR) -ggdb

ODIR=obj
LDIR =../lib

LIBS=-lm -lrt

_DEPS = SAP.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o SAP.o RTP.o wave.o OutputStreamBuffer.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS) 

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 
