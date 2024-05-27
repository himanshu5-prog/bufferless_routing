systemSim: flit.o router.o system.o test_system.o
	g++ flit.o router.o system.o test_system.o -o systemSim

flit.o: src/Flit/flit.cc src/Flit/flit.hh
	g++ -c src/Flit/flit.cc

router.o: src/Router/router.cc src/Router/router.hh
	g++ -c src/Router/router.cc

system.o: src/System/system.cc src/System/system.hh
	g++ -c src/System/system.cc

test_system.o: test/test_system.cc
	g++ -c test/test_system.cc

clean:
	rm *.o systemSim