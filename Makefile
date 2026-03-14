HEADERS := $(patsubst %/,%,$(wildcard */))
CXXFLAGS := -O2 -Wall -Wextra -fsanitize=address -fsanitize=undefined -fstack-protector-all -ggdb
all : clean $(HEADERS) 

$(HEADERS): %: %Test.out
	@echo "Test $*..."
	cd $* && ./$<

%Test.out : main.cpp
	-rm $*/$*Test.out
	cd $* && g++ $(CXXFLAGS) -DHEADER=\"$*/$*.h\" -o $@ ../main.cpp $*Test.cpp $*.cpp


clean : 
	-rm -rf */*.out

.PHONY: $(HEADERS) clean all