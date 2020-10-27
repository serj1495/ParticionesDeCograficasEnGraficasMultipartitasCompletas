all: main

main:main.cpp  nontaggedcotreenode.o binarycotreenode.o cotreenode.o subcographfinder.o m2_identifier.o m2_certifier.o skm2_finder.o
	g++ main.cpp nontaggedcotreenode.o binarycotreenode.o cotreenode.o subcographfinder.o m2_identifier.o m2_certifier.o skm2_finder.o -o main.exe

skm2_finder.o:skm2_finder.cpp skm2_finder.h cotreenode.o m2_certifier.o
	g++ skm2_finder.cpp skm2_finder.h cotreenode.o m2_certifier.o -c

m2_certifier.o: m2_certifier.cpp m2_certifier.h cotreenode.o
	g++ m2_certifier.cpp cotreenode.o -c

m2_identifier.o: m2_identifier.cpp m2_identifier.h subcographfinder.o
	g++ m2_identifier.cpp subcographfinder.o -c

subcographfinder.o: subcographfinder.cpp subcographfinder.h cotreenode.o binarycotreenode.o
	g++ subcographfinder.cpp cotreenode.o binarycotreenode.o -c

cotreenode.o: cotreenode.cpp cotreenode.h nontaggedcotreenode.o
	g++ cotreenode.cpp nontaggedcotreenode.o -c

binarycotreenode.o: binarycotreenode.cpp binarycotreenode.h
	g++ binarycotreenode.cpp -c

nontaggedcotreenode.o: nontaggedcotreenode.cpp nontaggedcotreenode.h
	g++ nontaggedcotreenode.cpp -c

