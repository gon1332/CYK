################===========================######################
#		CYK parser for CNF Grammars			#
################===========================######################
# Ioannidis Christos, hrioan@inf.uth.gr				#
# Konstadelias Ioannis, konstadel@inf.uth.gr			#
#################################################################

EXEC   = CYK
OBJS   = ErrorChecks.o GrammarStore.o main.o
CC     = clang
CFLAGS = -O3 -g -Wall -Wextra -fdiagnostics-print-source-range-info

all: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(EXEC)

ErrorChecks.o: includes/ErrorChecks.c includes/ErrorChecks.h
	$(CC) $(CFLAGS) -c includes/ErrorChecks.c -o ErrorChecks.o

GrammarStore.o: includes/GrammarStore.c includes/GrammarStore.h
	$(CC) $(CFLAGS) -c includes/GrammarStore.c -o GrammarStore.o

main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o main.o

clean:
	rm -f -v $(EXEC) $(OBJS) *~ ./includes/*~
