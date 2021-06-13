# This file is part of exampleapp
# Copyright (C)  Ellis Rhys Thomas <e.rhys.thomas@gmail.com>
# See COPYING file for licence details

CC=cc
CFLAGS=-Wall -Wfatal-errors -g3 -DDEBUG
INCLUDE=$(shell pkg-config --cflags gtk4) -I./src
TARGET=skel
LIBS=$(shell pkg-config --libs gtk4)
OBJ=$(TARGET)_app.o main.o $(TARGET)_appwin.o resources.o #$(TARGET)_prefs.o
APPLICATION_ID=cymru.ert.$(TARGET)
G_RESOURCES=data/ui/window.ui data/ui/menu.ui

.PHONY: all clean tags

all: $(TARGET) tags

# Data processing
src/resources.c: data/$(APPLICATION_ID).gresource.xml $(G_RESOURCES)
	glib-compile-resources $< --target=$@ --generate-source 
# data/schemas/gschemas.compiled: data/schemas/$(APPLICATION_ID).gschema.xml
# 	glib-compile-schemas data/schemas --targetdir=data/schemas/

# Object generation depends on their respective source file, any
# local headers included and data referenced in that source file.
$(TARGET)_win.o: src/$(TARGET)_app.h src/$(TARGET)_appwin.h src/resources.c 
$(TARGET)_app.o: src/$(TARGET)_app.h src/$(TARGET)_appwin.h 
main.o: src/$(TARGET)_app.h
%.o: src/%.c
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@ $(LIBS)

# Target executable generation
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(INCLUDE) $(OBJ) -o $@ $(LIBS)

clean:
	rm -f src/{TAGS,resources.c}
	rm -f $(OBJ)
	rm -f $(TARGET)
tags:
	@etags src/*.c src/*.h --output=src/TAGS
