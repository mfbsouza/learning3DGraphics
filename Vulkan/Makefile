# Makefile by Matheus Souza (github.com/mfbsouza)

# Project name

TARGET = program

# Dir structure

SRCDIR   = src
BUILDDIR = build
SRCEXT   = cpp
SOURCES  = $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS  = $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))

# Compiler and Linker settings
CC = g++
CFLAGS = -Wall
LDFLAGS = 


all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(LDFLAGS) $^ -o $@

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILDDIR) $(TARGET)

.PHONY: all clean
