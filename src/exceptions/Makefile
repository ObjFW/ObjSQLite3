include ../../extra.mk

STATIC_PIC_LIB_NOINST = ${EXCEPTIONS_LIB_A}
STATIC_LIB_NOINST = ${EXCEPTIONS_A}

SRCS = SL3BindObjectFailedException.m		\
       SL3ClearBindingsFailedException.m	\
       SL3Exception.m				\
       SL3ExecuteStatementFailedException.m	\
       SL3OpenFailedException.m			\
       SL3PrepareStatementFailedException.m	\
       SL3ResetStatementFailedException.m

INCLUDES = ${SRCS:.m=.h}

include ../../buildsys.mk

CPPFLAGS += -I. -I.. -DSL3_PUBLIC_IVARS

