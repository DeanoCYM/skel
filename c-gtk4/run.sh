#!/bin/bash

export GSETTINGS_SCHEMA_DIR="./data/schemas/"

./$(sed -nr 's/^TARGET=(.*)/\1/p' Makefile) "$@"
