#!/bin/bash

#declare -a Samples=(ttsl ttdl singletop qcd_ht ttw_mg_lo ttz_mg_lo ttg tth dyjetsll_ht gjets_dr0p05_ht wjets_ht100to200 wjets_ht1200to2500 wjets_ht200to400 wjets_ht2500toInf wjets_ht400to600 wjets_ht600to800 wjets_ht800to1200 zinv_ht)

declare -a Samples=(T1qqqq_mg1700 T1bbbb_mg1700 T1tttt_mg1700 T1qqqq_mg2200 T1bbbb_mg2200 T1tttt_mg2200 T2qq_msq1200 T2bb_msq1200 T2tt_msq1200 T2bt_msq1200 T2bW_msq1200 T2qq_msq800 T2bb_msq800 T2tt_msq800 T2bt_msq800 T2bW_msq800)

INDIR=../SkimmedSUSYSignal/Unclean/
OUTDIR=../SkimmedSUSYSignal/Clean/

for SAMPLE in ${Samples[@]}; do
    eval 'nohup nice -n 10 ./SelectionSkim.exe ${INDIR} ${SAMPLE} ${OUTDIR} >& logs/${SAMPLE}_selection_log.txt &'
done

