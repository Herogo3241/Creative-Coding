# Determine the OS
ifeq ($(OS),Windows_NT)
    # Windows-specific settings
    CXX = g++
    LDFLAGS = -lSDL2
    EXEC = app.exe
else
    # Linux-specific settings
    CXX = g++
    LDFLAGS = -lSDL2
    EXEC = app
endif

# The source files
SRC = src/main.cpp src/grid.cpp src/cell.cpp

# The build target
build: $(SRC)
	$(CXX) $(SRC) -o $(EXEC) $(LDFLAGS)

# Run the app after building
run: build
	./$(EXEC)

# Clean the build files
clean:
	rm -f $(EXEC)