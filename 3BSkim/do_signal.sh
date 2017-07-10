#!/bin/bash

# only dilepton samples
declare -a Samples=(T1qqqq_mg1700 T1bbbb_mg1700 T1tttt_mg1700 T1qqqq_mg2200 T1bbbb_mg2200 T1tttt_mg2200 T2qq_msq1200 T2bb_msq1200 T2tt_msq1200 T2bt_msq1200 T2bW_msq1200 T2qq_msq800 T2bb_msq800 T2tt_msq800 T2bt_msq800 T2bW_msq800)

INDIR=/home/users/dpg/MT2AnalysisEdit/MyCode/SkimmedSUSYSignal/Clean/
OUTDIR=/home/users/dpg/MT2AnalysisEdit/MyCode/3BSkim/SkimmedMC/

for SAMPLE in ${Samples[@]}; do
    eval 'nohup nice -n 10 ./3BSkim.exe ${INDIR} ${SAMPLE} ${OUTDIR} >& logs/${SAMPLE}_3B_selection_log.txt &'
done

