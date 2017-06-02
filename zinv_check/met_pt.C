{
  TChain tc("mt2");
  tc.Add("/hadoop/cms/store/user/olivito/AutoTwopler_babies/merged/MT2/V00-08-18_mc/output/zinv_ht100to200_nonext_output_1.root");
  tc.Add("/hadoop/cms/store/user/olivito/AutoTwopler_babies/merged/MT2/V00-08-18_mc/output/zinv_ht200to400_nonext_output_1.root");
  tc.Add("/hadoop/cms/store/user/olivito/AutoTwopler_babies/merged/MT2/V00-08-18_mc/output/zinv_ht200to400_nonext_output_2.root");
  tc.Add("/hadoop/cms/store/user/olivito/AutoTwopler_babies/merged/MT2/V00-08-18_mc/output/zinv_ht400to600_ext1_output_1.root");
  tc.Add("/hadoop/cms/store/user/olivito/AutoTwopler_babies/merged/MT2/V00-08-18_mc/output/zinv_ht400to600_ext1_output_2.root");
  tc.Add("/hadoop/cms/store/user/olivito/AutoTwopler_babies/merged/MT2/V00-08-18_mc/output/zinv_ht400to600_ext1_output_3.root");
  tc.Add("/hadoop/cms/store/user/olivito/AutoTwopler_babies/merged/MT2/V00-08-18_mc/output/zinv_ht600to800_nonext_output_1.root");
  tc.Add("/hadoop/cms/store/user/olivito/AutoTwopler_babies/merged/MT2/V00-08-18_mc/output/zinv_ht600to800_nonext_output_2.root");
  tc.Add("/hadoop/cms/store/user/olivito/AutoTwopler_babies/merged/MT2/V00-08-18_mc/output/zinv_ht800to1200_nonext_output_1.root");
  tc.Add("/hadoop/cms/store/user/olivito/AutoTwopler_babies/merged/MT2/V00-08-18_mc/output/zinv_ht1200to2500_nonext_output_1.root");

  TCanvas c1("c1");
  c1.SetLogy();
  tc.Draw("met_pt>>h(25,0,500)","evt_scale1fb" );
  h->Draw("E");
  c1.SaveAs("met_pt.pdf");
  TFile tf("met_pt_hist.root","RECREATE");
  h->Write();
  tf.Close();
}
