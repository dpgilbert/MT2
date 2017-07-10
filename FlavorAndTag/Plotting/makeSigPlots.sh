#!/bin/bash

declare -a Samples=(T1qqqq_mg1700 T1bbbb_mg1700 T1tttt_mg1700 T1qqqq_mg2200 T1bbbb_mg2200 T1tttt_mg2200 T2qq_msq1200 T2bb_msq1200 T2tt_msq1200 T2bt_msq1200 T2bW_msq1200 T2qq_msq800 T2bb_msq800 T2tt_msq800 T2bt_msq800 T2bW_msq800)

for SAMPLE in ${Samples[@]}; do
    eval './plotMaker.exe ../hists/${SAMPLE}.root >& logs/${SAMPLE}.log &'
done