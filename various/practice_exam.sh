#!/bin/bash
clear
result=${PWD##*/} 
echo "so $result select the number of the exam you want to practice. "
num=1
for d in ../exams/* ; do
    echo $num ":  $d"
    let num+=1
done
read exam
cp -r ../exams/exam$exam* ./
