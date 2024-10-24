#!/bin/sh

# update-library.sh
# copies music and updates the lib.pl file for cmus
# -------------------------------------------------

# Obtain path that this script is running from
CURRENT=$(pwd)

# This is the buildroot overlay path
WORKING=external/board/aulos/overlay

# Set to path where your music resides
SOURCE=$HOME/Music/*

# This is where cmus will look for music
MUSIC=/home/aulos/music

# This is where the cmus configuration file is
CMUS=home/aulos/.config/cmus/

# Set where your music should end up at
DEST=$CURRENT/$WORKING$MUSIC

echo "Copying music from \n$SOURCE \nto $DEST\n"

rsync \
    --update \
    --times \
    --recursive \
    --exclude '- *.jpg' \
    --exclude '- *.png' \
    --quiet \
    $SOURCE \
    $DEST

echo "Generating lib.pl file at \n$CURRENT/$WORKING/$CMUS\n"

cd $DEST
find $(pwd) -name \*.mp3 >> $CURRENT/$WORKING/$CMUS/lib.pl
sed -i "s,$DEST,$MUSIC,g" $CURRENT/$WORKING/$CMUS/lib.pl

echo "Done!"
