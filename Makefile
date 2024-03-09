CC = gcc
flags = -lm -lraylib
opt = -fsanitize=address -g
out = chess

default:
	$(CC) *.c $(flags) -o $(out)

dev:
	$(CC) *.c $(flags) $(opt) -o $(out)
run:
	./chess
clean:
	rm chess
