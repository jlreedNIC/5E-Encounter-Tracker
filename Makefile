all:
	g++ -std=c++11 -Wall -Wextra -pedantic -pedantic-errors main.cpp button.cpp textbox.cpp initiativelist.cpp diceroll.cpp creature.cpp app.cpp encounter.cpp -o Encounter -lsfml-window -lsfml-graphics -lsfml-system