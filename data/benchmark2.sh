#!/bin/bash
blue=$(tput setaf 4)
gray=$(tput setaf 7)
green=$(tput setaf 2)
teal=$(tput setaf 6)
normal=$(tput sgr0)

for routine in "n-routines/"*; do
    for benchmark in "benchmark/n-h_generate."*; do
        instance_size=${benchmark##*.}
        #Initial log - before program completion
        tmpLogFile=$(mktemp) #tmpfile to allow for pretty colors using printf
        cat > $tmpLogFile <<EOF
$normal============================[INSTANCE SIZE $instance_size]============================$green
Running the $routine benchmark for . 
$normal============================[Input]============================$gray
$(cat $benchmark $routine <(echo exit))
$normal============================[Program Output]===================$teal 

EOF
            printf "$(more $tmpLogFile)" #printf allows for pretty colors
            tmpFile=$(mktemp) #saving to tmp file so it can be logged in follow up log
            run_project="../src/program.exe --non-hamilton"
            #Please note that <(echo $instance_size) is unnecesarry for routines kahn_sort and tarjan_sort, but the program should ignore invalid `actions`.
            result=$(/usr/bin/time -f "%e|%M" $run_project < <(cat $benchmark $routine <(echo exit)) 2>&1 >$tmpFile)
            mem=${result##*|}
            time=${result%|*}

            #Save to .csv
            echo "$instance_size,$time" >> $(basename $routine)non-hamilton_benchmark_time.csv
            echo "$instance_size,$mem" >> $(basename $routine)non-hamilton_benchmark_memory.csv
            
            #Follow up log - after program completion
            cat > $tmpLogFile <<EOF

$(cat $tmpFile)
$normal============================[usr/bin/time]=====================$green
time = $(echo $time) seconds | memory used = $(echo $mem) KBi
Saved to $(basename $routine)non-hamilton_benchmark_time.csv $(basename $routine)_non-hamilton_benchmark_memory.csv

$normal
EOF
        printf "$(more $tmpLogFile)" #printf allows for pretty colors

        
    done
done