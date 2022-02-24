SRC:=gpioled-lab3.c
OBJ:=gpioled-lab3.o
PRG:=gpioled-lab3

LDFLAGS:=-lgpiod

all: $(OBJ)
	$(CC) $(OBJ) -o $(PRG) $(LDFLAGS)

$(OBJ):
	$(CC) -c $(SRC) -o $(OBJ)

clean:
	rm *.o $(PRG)
