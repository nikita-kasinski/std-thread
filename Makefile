EXEC=bin/main
TEXEC=bin/testexec
SANITIZER=-fsanitize=address,undefined
WARNINGS=-Wall -Wextra -Wpedantic
CPPFLAGS=$(SANITIZER) $(WARNINGS) -std=c++2a
.PHONY: run test build clean test dirs
$(EXEC): main.cpp matrix.h
	g++ $(CPPFLAGS) main.cpp -o $(EXEC)
$(TEXEC): test.cpp
	g++ $(CPPFLAGS) test.cpp -o $(TEXEC) -lgtest -lgtest_main
run: dirs $(EXEC)
	./$(EXEC)
test: dirs $(TEXEC)
	./$(TEXEC)
build: dirs $(EXEC)
dirs:
	-mkdir -p bin 
clean:
	-rm bin/*