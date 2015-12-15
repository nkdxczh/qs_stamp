# ==============================================================================
#
# Defines.common.mk
#
# ==============================================================================

UNAME_P := $(shell uname -p)
ifeq ($(UNAME_P),ppc64)
    CFLAGS += -mcpu=power8 -mtune=power8
endif

ifeq ($(UNAME_P),x86_64)
    CFLAGS += -mrtm
endif

CC       := gcc
CFLAGS   +=  -g -w -pthread -fpermissive
CFLAGS   += -O2
CFLAGS   += -I$(LIB)
CPP      := g++
CPPFLAGS += $(CFLAGS)
LD       := g++
LIBS     += -lpthread

# Remove these files when doing clean
OUTPUT +=

LIB := ../lib


# ==============================================================================
#
# End of Defines.common.mk
#
# ==============================================================================
