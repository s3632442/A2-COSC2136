.default: all

all: qwirkle

clean:
	rm -rf qwirkle *.o */*.o */*.dSYM .DS_Store

qwirkle: Model/Board.o Model/LinkedList.o Model/Node.o Model/Player.o Model/Tile.o View/Menu.o Controller/Game.o Controller/Validation.o Controller/DataHandler.o Controller/ScoringSystem.o qwirkle.o
	g++ -Wall -Werror -std=c++14 -g -O -o $@ $^

%/%.o: %/%.cpp
	g++ -Wall -Werror -std=c++14 -g -O -c $^

# 20220720
# https://stackoverflow.com/questions/1139271/makefiles-with-source-files-in-different-directories
