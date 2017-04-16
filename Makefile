CC=g++
DEPS = decisionNode.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

decisionTree: DecisionTree.o decisionNode.o
	g++ -o $@ $^

clean:
	rm *.o decisionTree
