The program folders should be structured as such:
homework2/
  homework2.exe
data/
  ignore.txt
  stopwords.txt
  train.txt
  test.txt
  train/<input files>
  test/<input files>

The program expects 3 parameters on the command line:

homework2.exe <path to input files> <name of training index file> <name of testing index file>
ie:
homework2.exe ../data/ train.txt test.txt
NOTE:
  1) The path to input files MUST end in a path delimiter (/ on linux).
  2) The program must have write permissions for generating a temporary file!

train.txt and test.txt should have the format:
<className>
<path to class' input files in the supplied data directory>
ie:
notSpam
train/ham/
spam
train/spam/

You can specify any number of classes and a directory for each class. 

The program will then look for input files from the supplied data directory
and then in the specified class directories.
ie:
notSpam in ../data/train/ham
spam in ../data/train/spam