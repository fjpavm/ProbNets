# Makefile to test ProbNets
TARGET = main
CFLAGS = -O2 -g

CPP = g++

LIBS=-lgvc \
		-lcgraph

OBJS = main.o \
		ProbNets/BayesianNetwork.o \
		ProbNets/MarkovNetVariable.o \
		ProbNets/MarkovNetwork.o \
		ProbNets/ProbabilisticVariable.o \
		ProbNets/ProbabilityDistribution.o \
		ProbNets/TableFactor.o \
		ProbNets/Variable.o

$(TARGET):  $(OBJS)
	$(CPP) -o $@ $(OBJS) $(LIBS)

.cpp.o:
	$(CPP) -c $< $(CFLAGS) -o $@

ProbNets/BayesianNetwork.o : ProbNets/BayesianNetwork.cpp ProbNets/BayesianNetwork.h
	$(CPP) -c $< $(CFLAGS) -o $@

ProbNets/MarkovNetVariable.o : ProbNets/MarkovNetVariable.cpp ProbNets/MarkovNetVariable.h
	$(CPP) -c $< $(CFLAGS) -o $@

ProbNets/MarkovNetwork.o : ProbNets/MarkovNetwork.cpp ProbNets/MarkovNetwork.h
	$(CPP) -c $< $(CFLAGS) -o $@

ProbNets/ProbabilisticVariable.o : ProbNets/ProbabilisticVariable.cpp ProbNets/ProbabilisticVariable.h
	$(CPP) -c $< $(CFLAGS) -o $@

ProbNets/ProbabilityDistribution.o : ProbNets/ProbabilityDistribution.cpp ProbNets/ProbabilityDistribution.h
	$(CPP) -c $< $(CFLAGS) -o $@

ProbNets/TableFactor.o : ProbNets/TableFactor.cpp ProbNets/TableFactor.h
	$(CPP) -c $< $(CFLAGS) -o $@

ProbNets/Variable.o : ProbNets/Variable.cpp ProbNets/Variable.h
	$(CPP) -c $< $(CFLAGS) -o $@

main.o: main.cpp
	g++ -c $< $(CFLAGS) -o $@


clean:
	rm -f $(TARGET)
	rm -f $(OBJS)
