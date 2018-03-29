#!/bin/sh

echo "Creating exported folder"
mkdir "exported"

echo "Creating folder exported/word"
mkdir "exported/word"
echo "Exporting README.md in .docx format"

pandoc opdrachten/opdracht_1/README.md -s -o exported/word/opdracht_1.docx &&
pandoc opdrachten/opdracht_2_1/README.md -s -o exported/word/opdracht_2_1.docx &&
pandoc opdrachten/opdracht_2_2/README.md -s -o exported/word/opdracht_2_2.docx &&
pandoc opdrachten/opdracht_3_1/README.md -s -o exported/word/opdracht_3_1.docx &&
pandoc opdrachten/opdracht_3_2/README.md -s -o exported/word/opdracht_3_2.docx &&
pandoc opdrachten/opdracht_4_1/README.md -s -o exported/word/opdracht_4_1.docx &&
pandoc opdrachten/opdracht_4_2/README.md -s -o exported/word/opdracht_4_2.docx &&
pandoc opdrachten/opdracht_4_3/README.md -s -o exported/word/opdracht_4_3.docx &&
pandoc opdrachten/opdracht_5_1/README.md -s -o exported/word/opdracht_5_1.docx &&
pandoc opdrachten/opdracht_5_2/README.md -s -o exported/word/opdracht_5_2.docx

echo "done"
