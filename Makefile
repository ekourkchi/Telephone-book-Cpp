# /*****************************************************************
# //
# //  NAME:		Ehsan Kourkchi
# //
# //  HOMEWORK:		3
# //
# //  CLASS:		ICS 212
# //
# //  INSTRUCTOR:	Ravi Narayan
# //
# //  DATE:		November 25, 2013           
# //
# //  FILE:		Makefile        
# //
# //  DESCRIPTION:	Makefile for "program2.c"
# //
# //****************************************************************/


all: database2.o  llist.o record.h llist.h
	c++ -o database2  database2.o llist.o


database2.o: database2.cpp record.h llist.h
	c++ -c database2.cpp

llist.o: llist.cpp record.h
	c++ -c llist.cpp

.PHONY: clean

clean:
	rm -f *.o