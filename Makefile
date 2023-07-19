APP = CParserFSM

OBJ_DIR = obj
BIN_DIR = .

VPATH += ./Sources
INCLUDE += -I./Includes

CC = gcc

LIBS =

OBJECTS += $(OBJ_DIR)/CParser.o \
	$(OBJ_DIR)/FSM.o \
	$(OBJ_DIR)/main.o

.PHONY: clean directory

all: directory $(BIN_DIR)/$(APP)

$(BIN_DIR)/$(APP) : $(OBJECTS)
	$(CC) -o $@ $^ $(INCLUDE) $(LIBS)

# C compiler rule
$(OBJ_DIR)/%.o : %.c
	$(CC) -c -o $@ $< $(INCLUDE) $(COMPILE)

directory:
	@mkdir -p $(subst /,\,$(OBJ_DIR));


clean:
	@echo cleaning....;
	@if [ -d $(OBJ_DIR) ]; then rm -rf $(OBJ_DIR); fi
