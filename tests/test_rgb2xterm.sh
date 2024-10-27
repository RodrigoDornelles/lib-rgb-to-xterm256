set -sex
./pride rgb > expect.txt
./pride rgb | ./pride rgb2xterm | ./pride xterm2rgb > result.txt
test $(diff --suppress-common-lines -y expect.txt result.txt | wc -l) -eq 0
rm expect.txt result.txt
