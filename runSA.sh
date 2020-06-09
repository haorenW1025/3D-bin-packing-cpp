#!/bin/bash
i=0
./bin_packing ${1} "${2}/output${i}.txt" 1000 0.9
i=i+1
./bin_packing ${1} "${2}/output${i}.txt" 5000 0.9
i=i+1
./bin_packing ${1} "${2}/output${i}.txt" 10000 0.9
i=i+1
./bin_packing ${1} "${2}/output${i}.txt" 50000 0.9
i=i+1
./bin_packing ${1} "${2}/output${i}.txt" 100000 0.9
i=i+1
./bin_packing ${1} "${2}/output${i}.txt" 1000 0.95
i=i+1
./bin_packing ${1} "${2}/output${i}.txt" 5000 0.95
i=i+1
./bin_packing ${1} "${2}/output${i}.txt" 10000 0.95
i=i+1
./bin_packing ${1} "${2}/output${i}.txt" 50000 0.95
i=i+1
./bin_packing ${1} "${2}/output${i}.txt" 100000 0.95
i=i+1
./bin_packing ${1} "${2}/output${i}.txt" 100 0.98
i=i+1
./bin_packing ${1} "${2}/output${i}.txt" 1000 0.98
i=i+1
./bin_packing ${1} "${2}/output${i}.txt" 5000 0.98
i=i+1
./bin_packing ${1} "${2}/output${i}.txt" 10000 0.98
i=i+1
./bin_packing ${1} "${2}/output${i}.txt" 50000 0.98
i=i+1
./bin_packing ${1} "${2}/output${i}.txt" 100000 0.98
i=i+1
./bin_packing ${1} "${2}/output${i}.txt" 100 0.99
i=i+1
./bin_packing ${1} "${2}/output${i}.txt" 1000 0.99
i=i+1
./bin_packing ${1} "${2}/output${i}.txt" 5000 0.99
i=i+1
./bin_packing ${1} "${2}/output${i}.txt" 10000 0.99
i=i+1
./bin_packing ${1} "${2}/output${i}.txt" 50000 0.99
i=i+1
./bin_packing ${1} "${2}/output${i}.txt" 100000 0.99
i=i+1
./bin_packing ${1} "${2}/output${i}.txt" 1000 0.999
i=i+1
./bin_packing ${1} "${2}/output${i}.txt" 5000 0.999
i=i+1
./bin_packing ${1} "${2}/output${i}.txt" 10000 0.999
i=i+1
./bin_packing ${1} "${2}/output${i}.txt" 50000 0.999
i=i+1
./bin_packing ${1} "${2}/output${i}.txt" 100000 0.999
