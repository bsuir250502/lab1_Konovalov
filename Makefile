OBJ = lab1.o
CFLAGS = -Wall -std=c89 -pedantic

all: bin

bin: $(OBJ)
	gcc $(CFLAGS) $(OBJ) -o bin

%.o : %.c
	gcc $(CFLAGS) -c $<

clean:
	rm bin $(OBJ)
