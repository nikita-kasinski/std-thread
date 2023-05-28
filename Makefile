EXEC=bin/main
TEXEC=bin/testexec
SANITIZER=-fsanitize=address,undefined
WARNINGS=-Wall -Wextra -Wpedantic
CPPFLAGS=$(WARNINGS) -std=c++2a #$(SANITIZER)
.PHONY: run test build clean test dirs
$(EXEC): main.cpp matrix.h
	g++ $(CPPFLAGS) main.cpp -o $(EXEC)
$(TEXEC): test.cpp
	g++ $(CPPFLAGS) test.cpp -o $(TEXEC) -lgtest -lgtest_main
run: dirs $(EXEC)
	valgrind --leak-check=yes ./$(EXEC)
test: dirs $(TEXEC)
	valgrind --leak-check=yes ./$(TEXEC)
build: dirs $(EXEC)
dirs:
	-mkdir -p bin 
clean:
	-rm bin/*