PROJECT=cpng

CC=gcc

SRCDIR=./src
INCDIR=./include
OBJDIR=./obj

CFLAGS=-I$(INCDIR)

SRCS=$(wildcard $(SRCDIR)/*.c)
DEPS=$(wildcard $(INCDIR)/*.h)
OBJS=$(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRCS))

ifndef VERBOSE
.SILENT:
endif

$(PROJECT): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ 

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

.PHONY: clean
clean:
	rm -f $(OBJDIR)/*.o
