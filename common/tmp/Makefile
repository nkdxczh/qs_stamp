include ../common/Makefile.flags

.PHONY: default
default: $(PROG)

.PHONY: clean
clean:
	$(RM) $(OBJS) $(PROG) $(OUTPUT)

$(PROG): $(OBJS)
	$(LD) $(LDFLAGS) $^ $(CFLAGS) $(LIBS) -o $(PROG)

include ../common/Makefile.common
