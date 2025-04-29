.PHONY: clean

CC = ${CROSS_COMPILE}gcc
CFLAGS = -w
SOURCES := writer.c
OBJDIR = obj
BINDIR = .
BINNAME = writer

OBJS := $(SOURCES:%.cpp=$(OBJDIR)/%.o)

$(BINDIR)/$(BINNAME): $(OBJS)
	mkdir -p $(BINDIR)
	$(CC) $(CFLAGS) -o $(BINDIR)/$(BINNAME) $(OBJS)

clean:
	-rm -f $(BINDIR)/writer $(OBJDIR)/*
