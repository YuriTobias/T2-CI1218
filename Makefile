PROGS = main

CC = gcc
CFLAGS = -std=c99 -Wall -g
LFLAGS = -lm

%.o:  %.c
	$(CC) $(CFLAGS) -c $<

debug: CFLAGS += -g -D__DEBUG__

all debug: $(PROGS)

$(PROGS) : % : %.o libstack.o liblist.o libscale.o libviewequiv.o
	$(CC) $(CFLAGS) -o $@ $^ $(LFLAGS)

clean:
	@echo "Limpando sujeira ..."
	@rm -f *% *.bak *~

purge: clean
	@echo "Limpando tudo ..."
	@rm -rf core *.o
	@rm -f $(PROGS)
