SRC =    Log.cpp 				\
		 LogEntry.cpp			\
		 LogReader.cpp			\
	  	 Date.cpp 				\
	  	 Lockable.cpp			\
		 Runable.cpp			\
	  	 PthreadLockable.cpp 	\
	  	 PthreadRunable.cpp		\
	  	 Args.cpp				\
		 PthreadTimer.cpp       \
		 RdFile.cpp	            \
		 Base.cpp

# TARGET = framework.a
LIB = libframework.so

LIBDIR = /usr/local/lib
INCDIR = /usr/local/include/framework

OBJ  := $(patsubst %.cpp,%.o,$(SRC))
HDR  := $(patsubst %.cpp,%.h,$(SRC))

# CC     = g++
CXXFLAGS = -Wall -g -std=c++17


all: $(LIB) 

$(LIB) : $(OBJ) $(HDR)
	@echo "Building shared library"
	$(CXX) $(CXXFLAGS) -shared -o $(LIB) $(OBJ)
	cp $(LIB) $(LIBDIR)
	mkdir -p $(INCDIR)
	cp *.h $(INCDIR) 

%.o: %.cpp
	$(CXX) -c $(CXXFLAGS) $< -o $@

clean:
	rm -f *.a *.o $(LIB)
	rm -f $(LIBDIR)/$(LIB)
	rm -rf $(INCDIR)

.PHONEY: test runtest doxygen clean