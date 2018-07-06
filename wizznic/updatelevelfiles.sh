#!/bin/bash

./wizznic -d

cd data/levels/

L=`ls | grep .wzp.tga`

for F in $L
do
  echo "File $F"
  NF=${F/.wzp.tga/.wzp.png}
  rm $NF
  convert $F -crop 230x230+86+4 -resize 110x110 $NF
  rm $F
done
