PROG_NOINST = tests${PROG_SUFFIX}
SRCS = Tests.m

include ../buildsys.mk
include ../extra.mk

post-all: ${RUN_TESTS}

.PHONY: run
run:
	rm -f libobjsqlite3.so.${OBJSQLITE3_LIB_MAJOR}
	rm -f libobjsqlite3.so.${OBJSQLITE3_LIB_MAJOR_MINOR}
	rm -f objsqlite3.dll libobjsqlite3.${OBJSQLITE3_LIB_MAJOR}.dylib
	if test -f ../src/libobjsqlite3.so; then \
		${LN_S} ../src/libobjsqlite3.so \
		    libobjsqlite3.so.${OBJSQLITE3_LIB_MAJOR}; \
		${LN_S} ../src/libobjsqlite3.so \
		    libobjsqlite3.so.${OBJSQLITE3_LIB_MAJOR_MINOR}; \
	elif test -f ../src/libobjsqlite3.so.${OBJSQLITE3_LIB_MAJOR_MINOR}; \
	then \
		${LN_S} ../src/libobjsqlite3.so.${OBJSQLITE3_LIB_MAJOR_MINOR} \
		    libobjsqlite3.so.${OBJSQLITE3_LIB_MAJOR_MINOR}; \
	fi
	if test -f ../src/objsqlite3.dll; then \
		${LN_S} ../src/objsqlite3.dll objsqlite3.dll; \
	fi
	if test -f ../src/libobjsqlite3.dylib; then \
		${LN_S} ../src/libobjsqlite3.dylib \
		    libobjsqlite3.${OBJSQLITE3_LIB_MAJOR}.dylib; \
	fi
	LD_LIBRARY_PATH=.$${LD_LIBRARY_PATH+:}$$LD_LIBRARY_PATH \
	DYLD_FRAMEWORK_PATH=../src:../src/runtime$${DYLD_FRAMEWORK_PATH+:}$$DYLD_FRAMEWORK_PATH \
	DYLD_LIBRARY_PATH=.$${DYLD_LIBRARY_PATH+:}$$DYLD_LIBRARY_PATH \
	LIBRARY_PATH=.$${LIBRARY_PATH+:}$$LIBRARY_PATH \
	${WRAPPER} ./${PROG_NOINST}; EXIT=$$?; \
	rm -f libobjsqlite3.so.${OBJSQLITE3_LIB_MAJOR}; \
	rm -f libobjsqlite3.so.${OBJSQLITE3_LIB_MAJOR_MINOR} objsqlite3.dll; \
	rm -f libobjsqlite3.${OBJSQLITE3_LIB_MAJOR}.dylib; \
	exit $$EXIT

${PROG_NOINST}: ${LIBOBJSQLITE3_DEP}

CPPFLAGS += -I../src
LIBS := -L../src -lobjsqlite3 ${LIBS}
LD = ${OBJC}
