CXX = g++
AR = ar
LD = g++
WINDRES = windres

INC = -I ../dependencies/glm/include -I ../dependencies/freeglut/include -I ../dependencies/freeimage/include
CFLAGS = -Wall -std=c++20 -fPIC -m64 -fexceptions
RCFLAGS = 
RESINC = 
LIBDIR = 
LIB = -lglut -lfreeimage -lGLU
LDFLAGS = -m64

INC_DEBUG = $(INC)
CFLAGS_DEBUG = $(CFLAGS) -g -D_DEBUG
RESINC_DEBUG = $(RESINC)
RCFLAGS_DEBUG = $(RCFLAGS)
LIBDIR_DEBUG = $(LIBDIR)
LIB_DEBUG = $(LIB)
LDFLAGS_DEBUG = $(LDFLAGS)
OBJDIR_DEBUG = obj/Debug
DEP_DEBUG = 
OUT_DEBUG = bin/Debug/libengine.so

INC_RELEASE = $(INC)
CFLAGS_RELEASE = $(CFLAGS) -O2
RESINC_RELEASE = $(RESINC)
RCFLAGS_RELEASE = $(RCFLAGS)
LIBDIR_RELEASE = $(LIBDIR)
LIB_RELEASE = $(LIB)
LDFLAGS_RELEASE = $(LDFLAGS) -s
OBJDIR_RELEASE = obj/Release
DEP_RELEASE = 
OUT_RELEASE = bin/Release/libengine.so

OBJ_DEBUG = $(OBJDIR_DEBUG)/engine.o \
			$(OBJDIR_DEBUG)/camera.o \
			$(OBJDIR_DEBUG)/light.o \
			$(OBJDIR_DEBUG)/list.o \
			$(OBJDIR_DEBUG)/material.o \
			$(OBJDIR_DEBUG)/mesh.o \
			$(OBJDIR_DEBUG)/node.o \
			$(OBJDIR_DEBUG)/object.o \
			$(OBJDIR_DEBUG)/texture.o \
			$(OBJDIR_DEBUG)/readData.o \
			$(OBJDIR_DEBUG)/ovoReader.o \
			$(OBJDIR_DEBUG)/keyValueStack.o \
			$(OBJDIR_DEBUG)/shadow.o \
			$(OBJDIR_DEBUG)/vertex.o

OBJ_RELEASE = $(OBJDIR_RELEASE)/engine.o \
			$(OBJDIR_RELEASE)/camera.o \
			$(OBJDIR_RELEASE)/light.o \
			$(OBJDIR_RELEASE)/list.o \
			$(OBJDIR_RELEASE)/material.o \
			$(OBJDIR_RELEASE)/mesh.o \
			$(OBJDIR_RELEASE)/node.o \
			$(OBJDIR_RELEASE)/object.o \
			$(OBJDIR_RELEASE)/texture.o \
			$(OBJDIR_RELEASE)/readData.o \
			$(OBJDIR_RELEASE)/ovoReader.o \
			$(OBJDIR_RELEASE)/keyValueStack.o \
			$(OBJDIR_RELEASE)/shadow.o \
			$(OBJDIR_RELEASE)/vertex.o

all: debug release

clean: clean_debug clean_release

#REGOLE PER CREAZIONE FILE .o
$(OBJDIR_RELEASE)/%.o: %.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c $^ -o $@

$(OBJDIR_DEBUG)/%.o: %.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c $^ -o $@

#DEBUG
debug: before_debug out_debug after_debug

before_debug: 
	test -d bin/Debug || mkdir -p bin/Debug
	test -d $(OBJDIR_DEBUG) || mkdir -p $(OBJDIR_DEBUG)

out_debug: before_debug $(OBJ_DEBUG) $(DEP_DEBUG)
	$(LD) -shared $(LIBDIR_DEBUG) $(OBJ_DEBUG)  -o $(OUT_DEBUG) $(LDFLAGS_DEBUG) $(LIB_DEBUG)

after_debug: 

clean_debug: 
	rm -f $(OBJ_DEBUG) $(OUT_DEBUG)
	rm -rf bin/Debug
	rm -rf $(OBJDIR_DEBUG)

#RELEASE
release: before_release out_release after_release

before_release: 
	test -d bin/Release || mkdir -p bin/Release
	test -d $(OBJDIR_RELEASE) || mkdir -p $(OBJDIR_RELEASE)

out_release: before_release $(OBJ_RELEASE) $(DEP_RELEASE)
	$(LD) -shared $(LIBDIR_RELEASE) $(OBJ_RELEASE)  -o $(OUT_RELEASE) $(LDFLAGS_RELEASE) $(LIB_RELEASE)

after_release: 

clean_release: 
	rm -f $(OBJ_RELEASE) $(OUT_RELEASE)
	rm -rf bin/Release
	rm -rf $(OBJDIR_RELEASE)



.PHONY: before_debug after_debug clean_debug before_release after_release clean_release
