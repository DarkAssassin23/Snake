TARGET = snake
CC = gcc
CFLAGS = -Wall -g

INCLUDES = -I headers/
INCLUDES += -I $(shell  grep "INCLUDES" .config | cut -d '=' -f 2-)
LIBDIR = $(shell  grep "LIBDIR" .config | cut -d '=' -f 2-)

OBJDIR = obj

ifeq ($(OS),Windows_NT)
	LIBS = -L $(LIBDIR)/ -lraylibdll -lopengl32 \
		   -lgdi32 -lwinmm
# 	LDFLAGS = -Wl,--subsystem,windows 
 	DEFS = -D_WIN32
else
	UNAMEOS = $(shell uname -s)
	ifeq ($(UNAMEOS),Darwin)
		LIBS = -framework CoreVideo -framework IOKit -framework Cocoa \
        -framework GLUT -framework OpenGL -L $(LIBDIR)/ \
        -lraylib -lm
	endif
	ifeq ($(UNAMEOS),Linux)
		LIBS = -L $(LIBDIR)/ -lraylib -lGL -lm \
        -ldl -lrt
	endif
endif
LIBS += -lpthread

.PHONY: default all release debug clean

default: $(TARGET)
all: default

release: CFLAGS = -Os
release: clean $(TARGET)

debug: CFLAGS = -g -Wall
debug: $(TARGET)

OBJECTS = $(patsubst %.c, $(OBJDIR)/%.o, $(wildcard src/*.c))
HEADERS = $(wildcard headers/*.h)

$(OBJDIR)/%.o: %.c $(HEADERS)
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@ $(DEFS)
	@echo "CC          "$@

$(TARGET): $(OBJECTS)
	@$(CC) $(OBJECTS) -o $@ $(LIBS) $(LDFLAGS)
	@echo "Created --> "$@

clean: 
	$(RM) -r $(TARGET) $(OBJDIR)
