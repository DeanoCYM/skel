#!/bin/bash
# This file is part of skel
# Copyright (C) Ellis Rhys Thomas <e.rhys.thomas@gmail.com>
# See COPYING file for licence details
#
# Script: skel.sh
# Description: Creates a skeleton folder for a new project
# Author: Ellis Rhys Thomas <e.rhys.thomas@gmail.com>
# Dependencies: git

# failed_exit: Print $1 as error and exit with status 1
function failed_exit ()
{
    echo "Cannot create project." 1>&2
    echo "ERROR: $1." 1>&2
    exit 1
}

# menu: Numbered menu. $1 is the prompt, the remaining args are
# presented as options.
function menu ()
{
    PS3="$1: "
    shift 
    select opt in $@
    do
	if [ -z $opt ]
	then
	    printf "Invalid selection.\n" >&2
	else
	    echo "$opt"
	    return 0
	fi
    done
}

# confirm: Yes/No dialog which returns 1 for yes and 0 for no, $1 is
# the prompt.
function confirm ()
{
    PS3="$1 " 
    select yn in Yes No
    do
	case $yn in 
	    Yes) return 1 ;;
	    No)  return 0 ;;
	    *)   printf "Invalid selection.\n" >&2 ;;
	esac
    done
}

# read_line: Get a line of input from the user, first argument is the
# prompt.
function read_line ()
{
    local line

    while [ -z "$line" ]
    do
	read -p "$1: " line
    done

    echo "$line"
    return 0
}

project="$(read_line "Enter a name for the new project")"
author="$(git config --get user.name)"
email="$(git config --get user.email)"

script="$(readlink -f "${BASH_SOURCE[0]}")"
dir="$(dirname "$script")"	# skel directory
dest="$HOME/git/$project"	# new project directory

licencedir="/usr/share/licenses/common"
disclaimer="$dir/common/disclaimer"

# Language specific options
[ -d "$dest" ] && failed_exit "$dest already exists"
lang=$(menu "Select project language" "c")
src="$dir/$lang"

[ ! -d "$src" ] && failed_exit "skeleton $lang directory not found at $src"
cp -r "$src" "$dest"
case "$lang" in
    "c")
	sed -n 's/^/# /p' "$disclaimer" | cat - "$src/Makefile" > "$dest/Makefile"
	printf "*.o\n" >> "$dest/.gitignore"
	touch "$dest/src/$project.c"
	;;
    *)
	failed_exit "currently unsupported language \"$lang\""
esac

# Licence selection
licence="$(menu "Select a licence" "$(find "$licencedir" -type f)")"
cp "$licence" "$dest/COPYING"

# Actions performed on each new file
for f in $(find "$dest" -type f)
do
    chown "$USER" "$f"
    chmod 644 "$f"
    sed -i "s/@PROJECT/$project/g" "$f"
    sed -i "s/@DATE/$year/g" "$f"
    sed -i "s/@AUTHOR/$author/g" "$f"
    sed -i "s/@EMAIL/$email/g" "$f"
done

# Actions performed on single files
chmod -f a-w "$dest"/doc/template*

# Initialise git repository
confirm "Create git repository?"; do_git=$?
if [ $do_git -eq 1 ]
then 
    git init -q -b "master" "$dest"
    printf "*~\n*#*\n" >> "$dest/.gitignore"
    git -C "$dest" add .
    git -C "$dest" commit -m "$lang project skeleton structure created with skel.sh"
fi

exit 0
