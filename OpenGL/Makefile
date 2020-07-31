# Makefile by Matheus Souza (github.com/mfbsouza)

# Settings
CC := clang++
SRCDIR := src
BUILDDIR:= build
BINDIR := bin
NAME := program

SRCEXT := cpp
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJETCS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))

# Compiler & Linker Flags
CFLAGS := -Wall
LIB := -lSDL2 -lSDL2_image -lGLEW -lGL
INC := -I include

$(BINDIR)/$(NAME): $(OBJETCS)
	@echo " Linking..."
	@mkdir -p $(BINDIR)
	@echo " $(CC) $^ -o $(BINDIR)/$(NAME) $(LIB)"; $(CC) $^ -o $(BINDIR)/$(NAME) $(LIB)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIR)
	@echo " $(CC) $(CFLAGS) $(INC) -c -o $@ $<"; $(CC) $(CFLAGS) $(INC) -c -o $@ $<

clean:
	@echo " Cleaning...";
	@echo " $(RM) -r $(BUILDDIR) $(BINDIR)"; $(RM) -r $(BUILDDIR) $(BINDIR)

.PHONY: clean
