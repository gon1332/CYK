################===========================######################
#		CYK parser for CNF Grammars			#
################===========================######################
# Ioannidis Christos, hrioan@inf.uth.gr				#
# Konstadelias Ioannis, konstadel@inf.uth.gr			#
#################################################################

EXEC   = cyk
OBJS   = ErrorChecks.o GrammarStore.o main.o
CC     = gcc
CFLAGS = -std=c99 -O3 -g -Wall -Wextra
LIBXML = `xml2-config --cflags --libs`

all: $(OBJS)
	$(CC) $(CFLAGS) $(LIBXML) $(OBJS) -o $(EXEC)

ErrorChecks.o: include/ErrorChecks.c include/ErrorChecks.h
	$(CC) $(CFLAGS) -c include/ErrorChecks.c -o ErrorChecks.o

GrammarStore.o: include/GrammarStore.c include/GrammarStore.h
	$(CC) $(CFLAGS) -c include/GrammarStore.c -o GrammarStore.o

main.o: main.c
	$(CC) $(CFLAGS) $(LIBXML) -c main.c -o main.o

clean:
	rm -f -v $(EXEC) $(OBJS) *~ ./include/*~
