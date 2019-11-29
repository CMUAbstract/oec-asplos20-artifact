#!/bin/bash
# Usage: ./run_csfp_base_sims.sh

if [ ! -d "../logs/001" ]
then
  mkdir "../logs/001"
fi
if [ ! -d "../logs/002" ]
then
  mkdir "../logs/002"
fi
if [ ! -d "../logs/003" ]
then
  mkdir "../logs/003"
fi
if [ ! -d "../logs/004" ]
then
  mkdir "../logs/004"
fi
if [ ! -d "../logs/006" ]
then
  mkdir "../logs/006"
fi
if [ ! -d "../logs/008" ]
then
  mkdir "../logs/008"
fi
if [ ! -d "../logs/012" ]
then
  mkdir "../logs/012"
fi
if [ ! -d "../logs/016" ]
then
  mkdir "../logs/016"
fi
if [ ! -d "../logs/024" ]
then
  mkdir "../logs/024"
fi
if [ ! -d "../logs/032" ]
then
  mkdir "../logs/032"
fi
if [ ! -d "../logs/048" ]
then
  mkdir "../logs/048"
fi
if [ ! -d "../logs/064" ]
then
  mkdir "../logs/064"
fi
if [ ! -d "../logs/096" ]
then
  mkdir "../logs/096"
fi
if [ ! -d "../logs/128" ]
then
  mkdir "../logs/128"
fi
if [ ! -d "../logs/192" ]
then
  mkdir "../logs/192"
fi
if [ ! -d "../logs/256" ]
then
  mkdir "../logs/256"
fi
if [ ! -d "../logs/384" ]
then
  mkdir "../logs/384"
fi
cd ../build/
cmake ../source/
make
./csfp_base 1 &
./csfp_base 2 &
./csfp_base 3 &
./csfp_base 4 &
./csfp_base 6 &
./csfp_base 8 &
./csfp_base 12 &
./csfp_base 16 &
./csfp_base 24 &
./csfp_base 32 &
./csfp_base 48 &
./csfp_base 64 &
./csfp_base 96 &
./csfp_base 128 &
./csfp_base 192 &
./csfp_base 256 &
./csfp_base 384 &
