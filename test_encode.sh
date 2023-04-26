#! /bin/sh
make
# encode file into packets then decode packets back into file
cat lorem_ipsum.txt | ./encode | ./decode > out.txt
# verify that there is no difference between original file and reconstructed packets
diff lorem_ipsum.txt out.txt
rm -f out.txt