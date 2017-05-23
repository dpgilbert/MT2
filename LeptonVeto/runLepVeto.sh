#!/bin/bash

eval 'nohup nice -n 10 ./LeptonVetoLooper < ../UnskimmedRunLists/ttdl.txt >& ttdl_log.txt &'

