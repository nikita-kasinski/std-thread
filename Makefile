EXEC=bin/main
TEXEC=bin/testexec
INCLUDE=-Iinclude
SANITIZER=-fsanitize=address,undefined
WARNINGS=-Wall -Wextra -Wpedantic
CPPFLAGS=$(WARNINGS) -std=c++2a $(INCLUDE) #$(SANITIZER)
.PHONY: run test build clean test dirs
$(EXEC): src/main.cpp include/matrix.h
	g++ $(CPPFLAGS) src/main.cpp -o $(EXEC)
$(TEXEC): test/test.cpp
	g++ $(CPPFLAGS) test/test.cpp -o $(TEXEC) -lgtest -lgtest_main
run: dirs $(EXEC)
	valgrind --leak-check=yes ./$(EXEC)
test: dirs $(TEXEC)
	valgrind --leak-check=yes ./$(TEXEC)
build: dirs $(EXEC)
dirs:
	-mkdir -p bin
clean:
	-rm bin/*