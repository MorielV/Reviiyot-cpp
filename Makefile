# All Targets
all: reviiot

# Tool invocations
# Executable "reviiyot" depends on the files Hand.o Card.o Player.o Deck.o Game.o

reviiot: bin/Card.o bin/Hand.o bin/Player.o bin/Deck.o bin/Game.o bin/reviiyot.o 
	@echo 'Building target: reviiyot'
	@echo 'Invoking: C++ Linker'
	g++ -o bin/reviiot bin/Card.o bin/Hand.o bin/Player.o bin/Deck.o bin/Game.o bin/reviiyot.o 
	@echo 'Finished building target: reviiot'
	@echo ' '

# Depends on the source and header files
bin/Card.o: src/Card.cpp	
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/Card.o src/Card.cpp
	
bin/Deck.o: src/Deck.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/Deck.o src/Deck.cpp
	
bin/Hand.o: src/Hand.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/Hand.o src/Hand.cpp
	
bin/Player.o: src/Player.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/Player.o src/Player.cpp

bin/Game.o: src/Game.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/Game.o src/Game.cpp
	
bin/reviiyot.o: src/reviiyot.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/reviiyot.o src/reviiyot.cpp


#Clean the build directory
clean: 
	rm -f bin/*
