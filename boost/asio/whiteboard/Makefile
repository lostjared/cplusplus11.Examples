CXX=c++
BOOST_PATH=/opt/local/boost
CXX_FLAGS= -std=c++11   `sdl-config --cflags` -I$(BOOST_PATH)/include
LD_FLAGS= -L/opt/local/lib /opt/local/lib/libSDLmain.a -Wl,-framework,AppKit /opt/local/lib/libSDL.a -L/opt/local/lib /opt/local/lib/libX11.a /opt/local/lib/libX11-xcb.a /opt/local/lib/libxcb.a /opt/local/lib/libXau.a /opt/local/lib/libXdmcp.a /opt/local/lib/libXext.a  /opt/local/lib/libXrandr.a  /opt/local/lib/libXrender.a  -Wl,-framework,OpenGL -Wl,-framework,Cocoa -Wl,-framework,ApplicationServices -Wl,-framework,Carbon -Wl,-framework,AudioToolbox -Wl,-framework,AudioUnit -Wl,-framework,IOKit -L$(BOOST_PATH)/lib  /opt/local/boost/lib/libboost_system.a

all:
	$(CXX) $(CXX_FLAGS) whiteboard.cpp -o whiteboard $(LD_FLAGS)
clean:
	rm -f whiteboard
