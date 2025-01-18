LDFLAGS=-pthread -lm -ltbb
CXXFLAGS=-O2 -std=c++20 -Wall -Werror -Wextra -Wno-missing-field-initializers

all:
	$(CXX) main.cpp $(LDFLAGS) $(CXXFLAGS) -o no-colors-img 

install: all
	cp no-colors-img /usr/local/bin/no-colors-img

clean:
	rm no-colors-img

.PHONY: all install clean
