#!/bin/bash
mkdir source_directory
touch source_directory/image1.png \
source_directory/image2.png \
source_directory/notes.txt \
source_directory/report.pdf \
source_directory/document.doc \
source_directory/present.ppt \
source_directory/archive.zip \
source_directory/backup.rar 


mkdir -p organizedDirectory/images organizedDirectory/documents organizedDirectory/others

echo "Files before processing:"
ls source_directory

for file in source_directory/*
do
    case "$file" in

        *.png|*.jpg|*.gif)
            mv "$file" organizedDirectory/images/
            echo "Moved $(basename "$file") to images."
            ;;

        *.txt|*.pdf|*.doc|*.ppt)
            mv "$file" organizedDirectory/documents/
            echo "Moved $(basename "$file") to documents."
            ;;

        *)
            mv "$file" organizedDirectory/others/
            echo "Moved $(basename "$file") to others."
            ;;

    esac
done
echo "Organized files successfuly!"
