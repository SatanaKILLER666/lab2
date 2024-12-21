OBJS = output/main.o output/lab2.o
SOURCE = main.c lab2.c
HEADER = lab2.h
OUT = output/lab2
CFLAGS = -Wall -g -c
CC = gcc

all: $(OUT)

$(OUT): $(OBJS)
	$(CC) -o $@ $^

output/%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -o $@ $<

.PHONY: run clean test

run: $(OUT)
	./$(OUT) input.txt replace "/Lorem/Ipsum/" #Пример команды

clean:
	rm -f $(OBJS) $(OUT)


