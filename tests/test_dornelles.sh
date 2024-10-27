set -sex
./pride xterm | ./pride xterm2rgb > expect.txt
./pride xterm | ./pride xterm2rgb | ./pride dornelles | ./pride xterm2rgb > result.txt
test $(diff --suppress-common-lines -y expect.txt result.txt | wc -l) -eq 0
rm expect.txt result.txt
