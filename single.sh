/home/other/CSE530-FA2022/gem5/build/X86/gem5.opt \
  /home/other/CSE530-FA2022/gem5/configs/example/se.py \
  --cmd=/home/grads/vzs5407/Ass3/test/a.out \
  --options="100 100" --cpu-type=TimingSimpleCPU \
  --caches --l2cache --l1d_size=32768 --l1i_size=32768 --l2_size=131072  --cpu-clock="1GHz" --mem-type=DDR3_1600_8x8