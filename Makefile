all: proc_scanner

proc_scanner: main.c queue.c proc.c opt.c
	gcc -o $@ $^

clean:
	rm proc_scanner
