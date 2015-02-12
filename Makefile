COMPILER 	= g++
CPPFLAGS    =
LDFLAGS     =
LIBS        = -lm

DESTDIR 	= bin
BUILDDIR 	= build
TARGET  	= $(DESTDIR)/main
SRCDIR 		= src

SRCEXT = cpp
SOURCES = $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS = $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))

$(TARGET): $(OBJECTS)
	@echo " Linking..."
	$(COMPILER) $^ -o $(TARGET) $(LIB)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@echo " Compiling..."
	@mkdir -p $(BUILDDIR)
	$(COMPILER) $(CPPFLAGS) -c -o $@ $<

clean:
	@echo " Cleaning..."
	$(RM) -r $(BUILDDIR) $(TARGET)

all: $(TARGET)
