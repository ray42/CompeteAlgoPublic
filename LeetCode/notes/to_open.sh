#!/bin/bash

# First we genlabels
cd Contents
grep -n "label{" *.tex --exclude=contents.tex > contents.tex
cd ../Images
find ./  -printf "%f\n" >> ./../Contents/contents.tex
cd ..

gvim -p Contents/contents.tex \
main.tex \
Contents/LeetCodeP100.tex \







