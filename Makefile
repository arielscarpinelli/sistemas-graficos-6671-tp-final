CXXFLAGS =	-O0 -g -Wall -fmessage-length=0 -c

OBJS =		$(patsubst %.cpp,%.o, $(wildcard src/*.cpp)) $(patsubst %.cpp,%.o, $(wildcard src/dff/*.cpp)) $(patsubst %.cpp,%.o, $(wildcard src/3ds/*.cpp))

LIBS =		-lglut32 -lglu32 -lopengl32 -lwinmm -lkernel32 -luser32 -lgdi32

TARGET =	sg.exe

%.o: %.cpp src/Model.h

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean

.cpp.o:
	$(CXX) $(CXXFLAGS) $< -o $@
	