#!/bin/bash
# Usage: ./run_fstp_mcap_sims.sh

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
./fstp_mcap 1 &
./fstp_mcap 2 &
./fstp_mcap 3 &
./fstp_mcap 4 &
./fstp_mcap 6 &
./fstp_mcap 8 &
./fstp_mcap 12 &
./fstp_mcap 16 &
./fstp_mcap 24 &
./fstp_mcap 32 &
./fstp_mcap 48 &
./fstp_mcap 64 &
./fstp_mcap 96 &
./fstp_mcap 128 &
./fstp_mcap 192 &
./fstp_mcap 256 &
./fstp_mcap 384 &
