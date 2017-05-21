{
  mt2->Draw("GenSusyMScan1", "fabs(GenSusyMScan2 - 200) < 0.01");
  TCanvas * c2 = new TCanvas();
  c2->cd();
  mt2->Draw("GenSusyMScan1", "fabs(GenSusyMScan2 - 600) < 0.01");
}
