CXX = g++
LD = g++
CFLAGS = -Wall -std=c++20 -fexceptions
INC = -I../engine -I../dependencies/glm/include
LIBDIR = -L../engine/bin/Debug
LIB = -lengine
LDFLAGS = 

# Percorsi per la build di debug
OBJDIR_DEBUG = obj/Debug
OUT_DEBUG = bin/Debug/test_program
CFLAGS_DEBUG = $(CFLAGS) -g -D_DEBUG
LIBDIR_DEBUG = $(LIBDIR)
LDFLAGS_DEBUG = $(LDFLAGS)
OBJ_DEBUG = $(OBJDIR_DEBUG)/keyValueStackTest.o \
            $(OBJDIR_DEBUG)/lightTest.o \
            $(OBJDIR_DEBUG)/listTest.o \
            $(OBJDIR_DEBUG)/materialTest.o \
            $(OBJDIR_DEBUG)/meshTest.o \
            $(OBJDIR_DEBUG)/nodeTest.o \
            $(OBJDIR_DEBUG)/test.o \
            $(OBJDIR_DEBUG)/testCamera.o \
            $(OBJDIR_DEBUG)/textureTest.o \
            $(OBJDIR_DEBUG)/vertexTest.o

# Percorsi per la build di release
OBJDIR_RELEASE = obj/Release
OUT_RELEASE = bin/Release/test_program
CFLAGS_RELEASE = $(CFLAGS) -O2
LIBDIR_RELEASE = $(LIBDIR)
LDFLAGS_RELEASE = $(LDFLAGS)
OBJ_RELEASE = $(OBJ_DEBUG:$(OBJDIR_DEBUG)/%.o=$(OBJDIR_RELEASE)/%.o)

# Target principali
all: debug release

clean: clean_debug clean_release

# Regole generiche per la creazione di file .o
$(OBJDIR_DEBUG)/%.o: %.cpp
	@mkdir -p $(OBJDIR_DEBUG)
	$(CXX) $(CFLAGS_DEBUG) $(INC) -c $< -o $@

$(OBJDIR_RELEASE)/%.o: %.cpp
	@mkdir -p $(OBJDIR_RELEASE)
	$(CXX) $(CFLAGS_RELEASE) $(INC) -c $< -o $@

# Target per la build di debug
debug: before_debug out_debug after_debug

before_debug:
	@mkdir -p bin/Debug

out_debug: $(OBJ_DEBUG)
	$(LD) -o $(OUT_DEBUG) $(OBJ_DEBUG) $(LIBDIR_DEBUG) $(LDFLAGS_DEBUG) $(LIB)

after_debug:
	@echo "Build di debug completata."

clean_debug:
	rm -rf $(OBJDIR_DEBUG) $(OUT_DEBUG)

# Target per la build di release
release: before_release out_release after_release

before_release:
	@mkdir -p bin/Release

out_release: $(OBJ_RELEASE)
	$(LD) -o $(OUT_RELEASE) $(OBJ_RELEASE) $(LIBDIR_RELEASE) $(LDFLAGS_RELEASE) $(LIB)

after_release:
	@echo "Build di release completata."

clean_release:
	rm -rf $(OBJDIR_RELEASE) $(OUT_RELEASE)

# Esegui i test
run_tests: debug
	@echo "Esecuzione dei test..."
	LD_LIBRARY_PATH=../engine/bin/Debug ./$(OUT_DEBUG)

.PHONY: all clean debug release run_tests
