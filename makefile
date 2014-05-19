################===========================######################
#		CYK parser for CNF Grammars			#
################===========================######################
# Ioannidis Christos, hrioan@inf.uth.gr				#
# Konstadelias Ioannis, konstadel@inf.uth.gr			#
#################################################################

EXEC   = CYK
OBJS   = ErrorChecks.o GrammarStore.o main.o
CC     = gcc
CFLAGS = -O3 -g -Wall -Wextra #-fdiagnostics-print-source-range-info

all: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(EXEC)

ErrorChecks.o: include/ErrorChecks.c include/ErrorChecks.h
	$(CC) $(CFLAGS) -c include/ErrorChecks.c -o ErrorChecks.o

GrammarStore.o: include/GrammarStore.c include/GrammarStore.h
	$(CC) $(CFLAGS) -c include/GrammarStore.c -o GrammarStore.o

main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o main.o

clean:
	rm -f -v $(EXEC) $(OBJS) *~ ./include/*~
