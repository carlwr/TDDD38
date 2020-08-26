#!/bin/bash
clear
echo "Hello new user of this practice program!"
echo "What is your name?"
read name
mkdir $name
cp various/new_session.sh $name/
chmod +x $name/new_session.sh

cp various/practice_exam.sh $name/
chmod +x $name/practice_exam.sh

echo "$name/"  | tee -a .gitignore

