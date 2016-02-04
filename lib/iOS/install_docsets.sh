#!/bin/sh
#
# Copies the Upsight docset from the current folder to the user's ~/Library

DST="$HOME/Library/Developer/Shared/Documentation/DocSets/"
ls -d *.docset | xargs -I {} cp -R {} $DST
echo "The Upsight Developer Documents have been installed. Please restart Xcode."