#!/bin/bash

# Define arrays for CPU models, clock speeds, and memory types
cpu_models=("X86TimingSimpleCPU" "X86MinorCPU")
clock_speeds=("1000MHz" "1200MHz" "1400MHz" "1600MHz" "1800MHz" "2000MHz")
memory_types=("DDR3_1600_8x8" "DDR3_2133_8x8" "LPDDR2_S4_1066_1x32")

# Base command components
gem5_path="/home/other/CSE530-FA2022/gem5/build/X86/gem5.opt"
config_path="/home/other/CSE530-FA2022/gem5/configs/example/se.py"
cmd_path="/home/grads/vzs5407/Ass3/test/a.out"
options="100 100"
i=0

# Iterate over each combination of CPU model, clock speed, and memory type
for cpu_model in "${cpu_models[@]}"; do
  for clock_speed in "${clock_speeds[@]}"; do
    for mem_type in "${memory_types[@]}"; do
      # Construct the command
      ((i++))
      echo $i
      # Check the condition and print if true
      if (( i > 0 && i < 7 )); then 
        echo $i
      
        command="$gem5_path $config_path --cmd=$cmd_path --options=\"$options\" --cpu-type=$cpu_model --caches --l2cache --l1d_size=32768 --l1i_size=32768 --l2_size=131072 --cpu-clock=\"$clock_speed\" --mem-type=$mem_type"
        
        # Print the command (or execute it using eval if desired)
        echo $command
        
        # Uncomment the line below to execute the command
        eval $command
        mkdir -p m5out/output
        mv m5out/stats.txt m5out/output/${cpu_model}${clock_speed}${mem_type}stats.txt
        mv m5out/config.ini m5out/output/${cpu_model}${clock_speed}${mem_type}config.ini
        echo $i done
      fi
    done
  done
done