CC := gcc
OBJS := hello.o first.o second.o
DEPENDS := first.h second.h

.PHONY: clean

%.o: %.c $(DEPENDS)
	$(CC) -c -o $@ $<

hello: $(OBJS)
	$(CC) -o hello $(OBJS)

clean:
	rm *.o
