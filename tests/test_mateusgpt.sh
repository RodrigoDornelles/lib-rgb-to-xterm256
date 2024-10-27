set -sex
./pride xterm | ./pride xterm2rgb > expect.txt
./pride xterm | ./pride xterm2rgb | ./pride mateusgpt | ./pride xterm2rgb > result.txt
test $(diff --suppress-common-lines -y expect.txt result.txt | wc -l) -eq 4
rm expect.txt result.txt
