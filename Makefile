CXX = g++
CFLAGS = -std=c++11 -fopenmp
LFLAGS = -fopenmp -Wall -I/usr/include/libdrm -lGLU -lGL -lglut -O3

target_file  := main
prog_name    := jx
src_dir     := ./src/
object_files := $(patsubst %.cpp, %.o, $(wildcard $(src_dir)*.cpp))

all: $(src_dir)$(target_file)

$(src_dir)$(target_file): $(object_files)
	$(CXX) $(object_files) -o $(prog_name) $(LFLAGS)

%.o: %.cpp
	$(CXX) $(CFLAGS) -c $< -o $@

clean:
	-$(RM) $(prog_name) $(object_files)
