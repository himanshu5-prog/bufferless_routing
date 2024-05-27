Bufferless Routing algorithm

1) The system class contains 16 routers in 4x4 mesh config. Each router contains four (max) input ports in East, West, North and South direction. There are four (max) ouput ports : East, West, North and South.

2) There are forbidden ports depending on location on router. For example: If router is at left corner in mesh, then West and North input ports cannot be used. Similarly, West and North output ports cannot be used. 
Note that west input port means that the flit is coming from west direction.

3) Whenever a flit comes into router, it is always sent out of router. The oldest flit is selected to route in optimized way and rest of the input flits are routed as free output ports are available. 

Code base:

1) There are three classes defined: Flit, Router and System (containing 4x4 routers).

2) If detailed log file needs to be generated then setDebgMode method (present in System class) can be used. By default, debugMode is set to False.

3) The code will print out the port connection, forbidden port list and history in each of router.

4) All tests are in test/directory. For system level test, test/test_system.cpp should be run.

Running the code:

> make
> ./systemSim > log

Resources:

i) Research paper: https://cfallin.org/pubs/tr-2010-001-chipper.pdf

ii) Video lecture by Onur Mutlu: https://www.youtube.com/watch?v=4xB9BZ7ky34&t=3987s&ab_channel=OnurMutluLectures