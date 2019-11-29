#!/bin/bash
# Usage: ./run_cstp_mcap_sims.sh

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
./cstp_mcap 1 &
./cstp_mcap 2 &
./cstp_mcap 3 &
./cstp_mcap 4 &
./cstp_mcap 6 &
./cstp_mcap 8 &
./cstp_mcap 12 &
./cstp_mcap 16 &
./cstp_mcap 24 &
./cstp_mcap 32 &
./cstp_mcap 48 &
./cstp_mcap 64 &
./cstp_mcap 96 &
./cstp_mcap 128 &
./cstp_mcap 192 &
./cstp_mcap 256 &
./cstp_mcap 384 &
