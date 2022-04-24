PRG         	:=Game
SRC_DIR     	:=FrameWork/source
SRC_USE_DIR     :=source

OBJ_DIR     	:=FrameWork/object
OBJ_USE_DIR     :=object

DEP_DIR     	:=FrameWork/object
DEP        		:=$(wildcard $(DEP_DIR)/*.d)

SRC         	:=$(wildcard $(SRC_DIR)/*.cpp)
SRC_USE			:=$(wildcard $(SRC_USE_DIR)/*.cpp)

OBJ         	:=$(addprefix $(OBJ_DIR)/,$(patsubst %.cpp,%.o,$(notdir $(SRC))))
OBJ_USE     	:=$(addprefix $(OBJ_USE_DIR)/,$(patsubst %.cpp,%.o,$(notdir $(SRC_USE))))

$(PRG): $(OBJ) $(OBJ_USE)
	$(CXX) -O2 $^ -o $@ -ldl -lGLESv2 -lGLU -lGL -lglfw3 -pthread -lGL -lGLEW  -lfreetype -ldl -lX11

$(OBJ_DIR)/%.o: FrameWork/source/%.cpp
	$(CXX) -O2 -g -c -MMD -MP $< -o $@
-include $(DEP)

$(OBJ_USE_DIR)/%.o: source/%.cpp
	$(CXX) -O2 -g -c -MMD -MP $< -o $@
-include $(DEP)
	
clean:
	rm -f ./$(OBJ_USE_DIR)/*.o ./$(OBJ_DIR)/*.o *.out ./$(OBJ_DIR)/*.d ./$(OBJ_USE_DIR)/*.d $(PRG)
	