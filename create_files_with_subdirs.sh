#!/bin/bash

#making a directory with time and date as the title
dir_name=$(date +"%Y-%m-%d_%H-%M")
mkdir "$dir_name"
echo "Main Directory's name is... $dir_name"

#creating a string of coding languages to distribute to the files
lang="Python Java ML C SQL Assembly CSS Script Ruby C++"
#num is used as a counter for file creation, 
#only creating tuserr*.txt file name number up to 10
num=1

#making 10 subdirectories inside the main
for i in $(seq 1 10); do
   sub=$(printf "file1%02d" $i)
#specifying to create the subdirectory under main
   mkdir "$dir_name/$sub"

#when a subdirectory is made, all the files for that directory will be created
   for l in $lang; do
#naming it accourding to it's specific number
      file=$(printf "tuser5%02d.txt" $num)

#placing the language title inside the file then placing 
#the file inside the subdirecotry
      echo "$l" > "$dir_name/$sub/$file"
      echo "file $file was created under $sub..."
#incremeneting num
      num=$((num + 1))
#stopping the counter at 10 then resetting to 1
      if [ $num -gt 10 ]; then
          num=1
      fi
   done
done
echo  "Subdirectories have been created..."

