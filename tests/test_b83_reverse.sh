set -sex
./pride l_rgb > expect.txt
./pride l_rgb | ./pride b8to3 | ./pride b3to8  > result.txt
test $(diff --suppress-common-lines -y expect.txt result.txt | wc -l) -le 32
rm expect.txt result.txt
