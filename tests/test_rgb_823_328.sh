set -sex
./pride rgb > expect.txt
./pride rgb | ./pride 823 | ./pride 328  > result.txt
test $(diff --suppress-common-lines -y expect.txt result.txt | wc -l) -le 32
rm expect.txt result.txt
