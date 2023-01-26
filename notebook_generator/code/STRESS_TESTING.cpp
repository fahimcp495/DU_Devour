set -e
g++ -O2 -static -std=gnu++17 gen.cpp -o gen
g++ -O2 -static -std=gnu++17 main.cpp -o main
g++ -O2 -static -std=gnu++17 brute.cpp -o brute
for((i = 1; ; ++i)); do
    echo $i
    ./gen $i > in
    # ./main < in > out
    # ./brute < in > out2
    # diff -w out out2 || break
    diff -w <(./main < in) <(./brute < in) || break
done