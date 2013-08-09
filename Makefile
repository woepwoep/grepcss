OBJLIST=print.o value.o file.o property.o selector.o grepcss.o process.o white.o
/usr/local/bin/grepcss: ${OBJLIST}
	cc -o /usr/local/bin/grepcss ${OBJLIST}

.c.o: grepcss.h

clean:
	rm -f ${OBJLIST}
