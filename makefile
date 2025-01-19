LDFLAGS=-pthread -lm -ltbb
CXXFLAGS=-O3 -std=c++17 -Wall -Werror -Wextra -Wno-missing-field-initializers

no-colors-img: main.cpp
	$(CXX) main.cpp $(LDFLAGS) $(CXXFLAGS) -o no-colors-img 

all: no-colors-img 

install: all
	cp no-colors-img /usr/local/bin/no-colors-img

uninstall:
	rm /usr/local/bin/no-colors-img

clean:
	rm no-colors-img

.PHONY: all install clean uninstall
