libbgi.a: drawing.o misc.o mouse.o palette.o text.o winbgi.o winthread.o file.o dibutil.o winbgi.h winbgim.h graphics.h
	ar -rv libbgi.a drawing.o misc.o mouse.o palette.o text.o winthread.o winbgi.o file.o dibutil.o
	del \cs1300\lib\libbgi.a
	copy libbgi.a \cs1300\lib
	del \cs1300\include\winbgi.h
	copy winbgi.h \cs1300\include

clean:
	del *.o 
	del *.exe 
	del libbgi.a

drawing.o: drawing.cxx winbgi.h winbgitypes.h
	g++ -c drawing.cxx

misc.o: misc.cxx winbgi.h winbgitypes.h
	g++ -c misc.cxx

mouse.o: mouse.cxx winbgi.h winbgitypes.h
	g++ -c mouse.cxx

palette.o: palette.cxx winbgi.h winbgitypes.h
	g++ -c palette.cxx

text.o: text.cxx winbgi.h winbgitypes.h
	g++ -c text.cxx

winbgi.o: winbgi.cxx winbgi.h winbgitypes.h
	g++ -c winbgi.cxx

winthread.o: winthread.cxx winbgi.h winbgitypes.h
	g++ -c winthread.cxx

dibutil.o: dibutil.c dibutil.h dibapi.h
	g++ -c dibutil.c

file.o: file.c dibutil.h dibapi.h winbgitypes.h
	g++ -c file.c

graphics.h: winbgi.h
	del graphics.h
	copy winbgi.h graphics.h
	del \cs1300\include\graphics.h
	copy graphics.h \cs1300\include

winbgim.h: winbgi.h
	del winbgim.h
	copy winbgi.h winbgim.h
	del \cs1300\include\winbgim.h
	copy winbgim.h \cs1300\include

bgi.exe: bgi.cxx
	g++ bgi.cxx -o bgi
	del \cs1300\bin\bgi++.exe
	copy bgi.exe \cs1300\bin
	rename \cs1300\bin\bgi.exe bgi++.exe

