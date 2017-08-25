all: proc_scanner

proc_scanner: main.c queue.c proc.c opt.c
	$(CC) -o $@ $^

clean:
	$(RM) proc_scanner