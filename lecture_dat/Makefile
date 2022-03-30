
IN_FILES=$(wildcard *.cpp)
OUT_FILES=$(patsubst %.cpp,bin/%,$(IN_FILES) )

DOC_IMAGES_PNG:=$(patsubst $(DOC_IMAGES_LOC)/%.cpp,BUILD/img/png/%.png, $(DOC_IMAGES_SRC))

all: $(OUT_FILES)

bin/%:%.cpp spike.hpp
#lecture1: lecture1.cpp spike.hpp
	$(CXX) -o $@ $<

clean:
	rm out_data/*

