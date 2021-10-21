APPNAME = main
EXT = .cpp
SRCDIR = src
OBJDIR = obj
EXECDIR = bin
INDIR = include

CC = g++
CXXFLAGS = -std=c++11 -Wall -I./$(INDIR)
LDFLAGS = -lSDL2 -lSDL2_image -lGL -lGLU -g 



SRC = $(wildcard $(SRCDIR)/*$(EXT))
OBJ = $(SRC:$(SRCDIR)/%$(EXT)=$(OBJDIR)/%.o)

compile: $(APPNAME)

# Builds the app
$(APPNAME): $(OBJ)
	$(CC) $(CXXFLAGS) -o $(EXECDIR)/$@ $^ $(LDFLAGS)


# Building rule for .o files and its .cpp in combination with all .h
$(OBJDIR)/%.o: $(SRCDIR)/%$(EXT)
	$(CC) $(CXXFLAGS) -o $@ -c $<


.PHONY: clean
clean:
	rm $(OBJ) $(EXECDIR)/$(APPNAME) 2>/dev/null


