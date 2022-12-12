.SUFFIXES = .cpp .exe .h .x

CC=g++

FLAGS = -Wall -std=c++11

NAME = main
HEADER = area.h
CODE1 = area.cpp
HEADER2 = field.h
CODE2 = field.cpp

$(NAME).exe: $(NAME).cpp $(HEADER)
	$(CC) $(FLAGS) $(NAME).cpp $(CODE1) $(CODE2) $(HEADER) $(HEADER2) -o $(NAME).exe

EXEC = $(NAME).exe

.PHONY: run

run: $(EXEC)
	./$(EXEC)

.PHONY: clean

clean:
	rm -rf *.exe *.out 

.PHONY: tar
tar:
	(cd ../; tar -cvzf Minesweeper.tar.gz  minesweeper )
