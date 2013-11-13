HEADERS = memory.h ReadWriteFile.h

OBJECTS = main.o memory.o ReadWriteFile.o



all: build




%.o:%.c $(HEADERS)

	gcc -c $< -o $@
	




build: $(OBJECTS)
        
	gcc $(OBJECTS) -o program


clean:
  
	-rm -f $(OBJECTS)
  
	-rm -f program