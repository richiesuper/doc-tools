CC=cc
CFLAGS=-Wall -Wextra -Wshadow -pedantic -O2
EXEC=doc-tools
OBJ=doc-tools.o
SRC=doc-tools.c

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

$(OBJ): $(SRC)
	$(CC) $(CFLAGS) -c -o $@ $^

clean:
	rm -f $(EXEC) $(OBJ)

.PHONY: clean
