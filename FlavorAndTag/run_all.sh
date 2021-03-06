#!/bin/bash

declare -a Samples=(T1qqqq_mg1700 T1bbbb_mg1700 T1tttt_mg1700 T1qqqq_mg2200 T1bbbb_mg2200 T1tttt_mg2200 T2qq_msq1200 T2bb_msq1200 T2tt_msq1200 T2bt_msq1200 T2bW_msq1200 T2qq_msq800 T2bb_msq800 T2tt_msq800 T2bt_msq800 T2bW_msq800 dyjetsll_ht qcd_ht singletop ttsl ttdl ttg tth ttw_mg_lo ttz_mg_lo wjets zinv_ht zll_dyjetsll_ht)

for SAMPLE in ${Samples[@]}; do
    eval 'nohup nice -n 10 ./FlavorAndTag.exe ../3BSkim/SkimmedMC/${SAMPLE}.root >& logs/${SAMPLE}_log.txt &'
done

declare -a LowSamples=(tth_low ttz_mg_lo_low)

for SAMPLE in ${LowSamples[@]}; do
    eval 'nohup nice -n 10 ./FlavorAndTag.exe ../3BSkim/SkimmedMC_low/${SAMPLE}.root >& logs/${SAMPLE}_log.txt &'
done

declare -a ZeroSamples=(tth_zero ttz_mg_lo_zero)

for SAMPLE in ${ZeroSamples[@]}; do
    eval 'nohup nice -n 10 ./FlavorAndTag.exe ../3BSkim/SkimmedMC_zero/${SAMPLE}.root >& logs/${SAMPLE}_log.txt &'
done



