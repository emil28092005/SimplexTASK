GXX := g++ -std=c++20
flags := -Wall -fsanitize=address
TOOLS := tools
BUILD := build

build:
	mkdir -p $(BUILD)
	$(GXX) -c $(flags) $(TOOLS)/elimination.cpp -o $(BUILD)/elimination.obj
	$(GXX) -c $(flags) $(TOOLS)/math.cpp -o $(BUILD)/math.obj
	$(GXX) -c $(flags) $(TOOLS)/matrix.cpp -o $(BUILD)/matrix.obj
	$(GXX) -c $(flags) simplex.cpp -o $(BUILD)/simplex.obj
	$(GXX) -c $(flags) main.cpp -o $(BUILD)/main.obj

	$(GXX) $(BUILD)/*.obj $(flags) -o simplex.out

$(BUILD)/elimination.obj: $(TOOLS)/elimination.cpp
	$(GXX) -c $(flags) $(TOOLS)/elimination.cpp -o $(BUILD)/elimination.obj

$(BUILD)/math.obj: $(TOOLS)/math.cpp
	$(GXX) -c $(flags) $(TOOLS)/math.cpp -o $(BUILD)/math.obj

$(BUILD)/matrix.obj: $(TOOLS)/matrix.cpp
	$(GXX) -c $(flags) $(TOOLS)/matrix.cpp -o $(BUILD)/matrix.obj

$(BUILD)/simplex.obj: simplex.cpp
	$(GXX) -c $(flags) simplex.cpp -o $(BUILD)/simplex.obj

$(BUILD)/main.obj: main.cpp
	$(GXX) -c $(flags) main.cpp -o $(BUILD)/main.obj

simplex.out: $(BUILD)/elimination.obj $(BUILD)/math.obj $(BUILD)/matrix.obj $(BUILD)/simplex.obj $(BUILD)/main.obj
	$(GXX) $(BUILD)/*.obj $(flags) -o simplex.out

test: simplex.out
	./simplex.out

clean:
	rm -rf $(BUILD)
	rm -rf simplex.out

rebuild:
	rm -rf $(BUILD)
	rm -rf simplex.out

	mkdir -p $(BUILD)
	$(GXX) -c $(flags) $(TOOLS)/elimination.cpp -o $(BUILD)/elimination.obj
	$(GXX) -c $(flags) $(TOOLS)/math.cpp -o $(BUILD)/math.obj
	$(GXX) -c $(flags) $(TOOLS)/matrix.cpp -o $(BUILD)/matrix.obj
	$(GXX) -c $(flags) simplex.cpp -o $(BUILD)/simplex.obj
	$(GXX) -c $(flags) main.cpp -o $(BUILD)/main.obj

	$(GXX) $(BUILD)/*.obj $(flags) -o simplex.out

	$(BUILD)/elimination.obj: $(TOOLS)/elimination.cpp
	$(GXX) -c $(flags) $(TOOLS)/elimination.cpp -o $(BUILD)/elimination.obj

	$(BUILD)/math.obj: $(TOOLS)/math.cpp
	$(GXX) -c $(flags) $(TOOLS)/math.cpp -o $(BUILD)/math.obj

	$(BUILD)/matrix.obj: $(TOOLS)/matrix.cpp
	$(GXX) -c $(flags) $(TOOLS)/matrix.cpp -o $(BUILD)/matrix.obj

	$(BUILD)/simplex.obj: simplex.cpp
	$(GXX) -c $(flags) simplex.cpp -o $(BUILD)/simplex.obj

	$(BUILD)/main.obj: main.cpp
	$(GXX) -c $(flags) main.cpp -o $(BUILD)/main.obj
