cc: =gcc
OBJS := hello.o first.o second.o
DEPENDS := first.h second.h

.PHONY: all clean

%.o: %.c $(DEPENDS) // for all .c files, if they depend on the header files, then compile them into .o files
	$(CC) -c -o $@ $< 

hello: $(OBJS)
	$(CC) -o hello $(OBJS)

clean:
	rm *.o