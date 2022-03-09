CC=gcc
CFLAGS=-Wall

clean:
	rm -f $(HOME)/.local/bin/gpa-calc

install:
	$(CC) gpa-calc.c $(CFLAGS) -o gpa-calc
	cp gpa-calc $(HOME)/.local/bin/gpa-calc
