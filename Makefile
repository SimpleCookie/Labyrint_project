FILES = main.cpp Maze.cpp Inputs.cpp 
OUT_EXE = out_Executable

all: $(OUT_EXE)

$(OUT_EXE): $(FILES) Maze.h Arg_handles.h Inputs.h
	g++ -std=c++11 -o $(OUT_EXE) $(FILES)
clean:
	rm -f *.o core

rebuild: clean $(OUT_EXE)
	./$(OUT_EXE)
