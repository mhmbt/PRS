CC= gcc
CFLAGS= -Wall
LDFLAGS=

EXEC=serveur1

all:$(EXEC)

serveur1:serveur1.o UDP1.o
	$(CC) -o $@ $^

serveur1.o:UDP.h
%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

.PHONY: clean mrproper
clean:
		rm -rf *.o

mrproper: clean
	rm -rf $(EXEC)
