CC=emcc
WEBCORE_DIR=../WebCore
SOURCES:=main.cpp $(wildcard src/*.cpp) $(wildcard $(WEBCORE_DIR)/src/*.cpp) $(wildcard $(WEBCORE_DIR)/imgui/*.cpp)
#LDFLAGS=-O2 --llvm-opts 2
#LDFLAGS=-O0 -g -s DEMANGLE_SUPPORT=1
LDFLAGS=-O3
OUTPUT=out/game.js
#OUTPUT=out/game.html
USE_IMGUI=-I$(WEBCORE_DIR)/imgui/
USE_VORBIS=-s USE_VORBIS=1
USE_LIBPNG=-s USE_LIBPNG=1 -s USE_ZLIB=1
USE_WEBGL=-s FULL_ES3=1 -s USE_GLFW=3 -s USE_WEBGL2=1 -lGLU -lGL
USE_WEBGL_MOB=-s FULL_ES2=1 -s USE_GLFW=3 -lGLU -lGL
USE_ENGINE_WEBCORE=-I$(WEBCORE_DIR)/include/
USE_ASYNC_FILES=-s EMTERPRETIFY=1 -s EMTERPRETIFY_ASYNC=1
USE_BULLET=-I../Bullet/bullet/src -s USE_BULLET=1
#-s USE_WEBGL2=1

all: $(SOURCES) $(OUTPUT)

$(OUTPUT): $(SOURCES)
	$(CC) $(USE_BULLET) -Isrc -I/usr/local/include/ $(SOURCES) $(USE_IMGUI) -std=c++1z $(USE_VORBIS) $(USE_LIBPNG) $(USE_WEBGL) $(USE_ENGINE_WEBCORE) --bind $(LDFLAGS) -o $(OUTPUT) -s WASM=1 -s ALLOW_MEMORY_GROWTH=1 -s ASSERTIONS=1 --preload-file data --emrun

clean:
	rm $(OUTPUT)
