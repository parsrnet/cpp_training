CXX=clang++
CXXFLAGS=-std=c++17

ODIR=obj

bankcli: bankcli.cpp $(ODIR)/account.o
	$(CXX) $(CXXFLAGS) bankcli.cpp -o $@ obj/account.o

$(ODIR)/account.o: account.cpp account.h
	$(CXX) -c -o $@ $< $(CXXFLAGS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ bankcli
