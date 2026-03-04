HEADERS := $(filter-out utils,$(basename $(wildcard *.h)))
CXXFLAGS := -O2 -Wall -Wextra -fsanitize=address -fsanitize=undefined -fstack-protector-all -ggdb
all : clean $(HEADERS) 

$(HEADERS): %: %Test.out
	@echo "Test $*..."
	-rm $*.out
	./$<

%Test.out : main.cpp %.h %Test.cpp %.cpp
	g++ $(CXXFLAGS) -DHEADER=\"$*.h\" -o $@ main.cpp $*Test.cpp $*.cpp


clean : 
	-rm *.out

.PHONY: $(HEADERS) clean all