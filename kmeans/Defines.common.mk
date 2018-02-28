# ==============================================================================
#
# Defines.common.mk
#
# ==============================================================================

architecture := $(shell uname -m)

ifeq ($(architecture),ppc64)
CFLAGS += -DALIGNED_ALLOC_MEMORY
endif

CFLAGS += -DOUTPUT_TO_STDOUT

PROG := kmeans

SRCS += \
	cluster.c \
	common.c \
	kmeans.c \
	normal.c \
	$(LIB)/mt19937ar.c \
	$(LIB)/random.c \
	$(LIB)/thread.c \
	$(LIB)/qs_scheduler.c \
	$(LIB)/qs_schunit.c \
#
OBJS := ${SRCS:.c=.o}


# ==============================================================================
#
# End of Defines.common.mk
#
# ==============================================================================
