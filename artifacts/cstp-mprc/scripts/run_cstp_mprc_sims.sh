#!/bin/bash
# Usage: ./run_cstp_mprc_sims.sh

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
./cstp_mprc 1 &
./cstp_mprc 2 &
./cstp_mprc 3 &
./cstp_mprc 4 &
./cstp_mprc 6 &
./cstp_mprc 8 &
./cstp_mprc 12 &
./cstp_mprc 16 &
./cstp_mprc 24 &
./cstp_mprc 32 &
./cstp_mprc 48 &
./cstp_mprc 64 &
./cstp_mprc 96 &
./cstp_mprc 128 &
./cstp_mprc 192 &
./cstp_mprc 256 &
./cstp_mprc 384 &
