CXX = g++
CFLAGS = -Wall

SRCMAINDIR = ${CURDIR}/examples/example_1/src
INCMAINDIR = ${CURDIR}/examples/example_1/inc
SRCLIBDIR = ${CURDIR}/src
INCLIBDIR = ${CURDIR}/inc
BUILDDIR = ${CURDIR}/build
TESTDIR = ${CURDIR}/examples/example_1/test

MAINSOURCES = ${SRCMAINDIR}/main.cpp
TESTSOURCES = ${TESTDIR}/test.cpp
LIBSOURCES = ${SRCLIBDIR}/JournalLib.cpp

all:clean_all mkdirbuild ${BUILDDIR}/libJournalLib.so main

build_lib: mkdirbuild ${BUILDDIR}/libJournalLib.so

mkdirbuild:
	mkdir -p ${BUILDDIR}

main:main.o JournalWorker.o inputCore.o
	$(CXX) $(CFLAGS) -o ${BUILDDIR}/main ${BUILDDIR}/main.o ${BUILDDIR}/JournalWorker.o ${BUILDDIR}/inputCore.o -L${BUILDDIR} -lJournalLib -lm

JournalWorker.o:${SRCMAINDIR}/JournalWorker.cpp
	$(CXX) $(CFLAGS) -I${INCLIBDIR} -I${INCMAINDIR} -c -o ${BUILDDIR}/JournalWorker.o ${SRCMAINDIR}/JournalWorker.cpp

inputCore.o:${SRCMAINDIR}/inputCore.cpp
	$(CXX) $(CFLAGS) -I${INCLIBDIR} -I${INCMAINDIR} -c -o ${BUILDDIR}/inputCore.o ${SRCMAINDIR}/inputCore.cpp

main.o:${MAINSOURCES}
	$(CXX) $(CFLAGS) -I${INCLIBDIR} -I${INCMAINDIR} -c -o ${BUILDDIR}/main.o ${MAINSOURCES}

${BUILDDIR}/JournalLib.o:${LIBSOURCES}
	$(CXX) $(CFLAGS) -I ${INCLIBDIR} -fPIC -c ${LIBSOURCES} -o ${BUILDDIR}/JournalLib.o

${BUILDDIR}/libJournalLib.so:${BUILDDIR}/JournalLib.o
	$(CXX) $(CFLAGS) -shared -o ${BUILDDIR}/libJournalLib.so ${BUILDDIR}/JournalLib.o -lm

run:
	LD_LIBRARY_PATH=${BUILDDIR} ${BUILDDIR}/main

tests:clean_all mkdirbuild ${BUILDDIR}/libJournalLib.so do_test test_run

do_test:test.o JournalWorker.o inputCore.o
	$(CXX) $(CFLAGS) -o ${BUILDDIR}/do_test ${BUILDDIR}/test.o ${BUILDDIR}/JournalWorker.o ${BUILDDIR}/inputCore.o -L${BUILDDIR} -lJournalLib -lm

test.o:${TESTSOURCES}
	$(CXX) $(CFLAGS) -I${INCLIBDIR} -I${INCMAINDIR} -c -o ${BUILDDIR}/test.o ${TESTSOURCES}

test_run:
	LD_LIBRARY_PATH=${BUILDDIR} ${BUILDDIR}/do_test

clean_all:
	rm -f ${BUILDDIR}/*

clean:
	rm -f ${BUILDDIR}/*.o
