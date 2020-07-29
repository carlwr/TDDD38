#!/bin/bash
clear
result=${PWD##*/} 
echo "so $result which seminar do you want to practice?"
read seminar
cp -r ../labs/sem$seminar ./
