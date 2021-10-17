# Macros
cxx = g++
cxxflags = -std=c++11 -Wall -Wextra -pedantic -pedantic-errors
sfml = -lsfml-window -lsfml-graphics -lsfml-system

# Files
src = SourceFiles
allSRC = $(src)/main.cpp $(src)/button.cpp $(src)/textbox.cpp $(src)/initiativelist.cpp $(src)/diceroll.cpp $(src)/creature.cpp $(src)/app.cpp $(src)/encounter.cpp
obj = SourceFiles/obj
allOBJ = $(obj)/main.o $(obj)/initiativelist.o $(obj)/app.o $(obj)/diceroll.o $(obj)/button.o $(obj)/creature.o $(obj)/encounter.o $(obj)/textbox.o
exec = 5Eencounter

# Pattern for .cpp files
$(obj)/%.o : $(src)/%.cpp
	mkdir -p $(obj)
	$(cxx) $(cxxflags) $< -c -o $@

# Dependencies

$(exec) : 
	$(cxx) $(cxxflags) $(allOBJ) -o $@ $(sfml)

main.o : initiative.h diceroll.h button.h app.h

initiativelist.o : creature.h diceroll.h

creature.o : textbox.h

textbox.o : button.h

run:
	./$(exec)

all:
	$(cxx) $(cxxflags) $(allSRC) -o $(exec) $(sfml)

clean:
	rm -rf $(obj)