#include<iostream>
#include "ComputeBin.C"
#include "SetStyle.C"
#ifndef __CINT__
#include "RooGlobalFunc.h"
#endif
#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooGaussian.h"
#include "RooGaussModel.h"
#include "RooConstVar.h"
#include "RooDecay.h"
#include "RooLandau.h"
#include "RooProdPdf.h"
#include "RooHistPdf.h"
#include "RooPlot.h"
#include "TCanvas.h"
#include "TAxis.h"
#include "TH1.h"
using namespace RooFit ;


using namespace std;

void RZGammaSmooth(){



    TStyle *gStyle = new TStyle("gStyle","Style for P-TDR");
    SetStyle st;
    st.SetPars(gStyle);


    TFile *f=new TFile("SuperSkim.root","READ");//SuperSkim.root

    TTree *TreeGJ = (TTree*)f->Get("treeGJ");
    TTree *TreeZJ = (TTree*)f->Get("treeZJ");

    TTree *TreeTTGJ = (TTree*)f->Get("treeTTGJ");
    TTree *TreeTTZ = (TTree*)f->Get("treeTTZ");



    double HTGJ;
    double MHTGJ;
    double PhotonPtGJ;
    int NJetsGJ;
    int BJetsGJ;
    double WtGJ;

    double HTZJ;
    double MHTZJ;
    int NJetsZJ;
    int BJetsZJ;
    double WtZJ;


    double HTTTGJ;
    double MHTTTGJ;
    double PhotonPtTTGJ;
    int NJetsTTGJ;
    int BJetsTTGJ;
    double WtTTGJ;

    double HTTTZ;
    double MHTTTZ;
    int NJetsTTZ;
    int BJetsTTZ;
    double WtTTZ;



    TreeGJ->SetBranchAddress("HTGJ",&HTGJ);
    TreeGJ->SetBranchAddress("MHTGJ",&MHTGJ);
    TreeGJ->SetBranchAddress("PhotonPtGJ",&PhotonPtGJ);
    TreeGJ->SetBranchAddress("NJetsGJ",&NJetsGJ);
    TreeGJ->SetBranchAddress("BJetsGJ",&BJetsGJ);
    TreeGJ->SetBranchAddress("WtGJ",&WtGJ);


    TreeTTGJ->SetBranchAddress("HTTTGJ",&HTTTGJ);
    TreeTTGJ->SetBranchAddress("MHTTTGJ",&MHTTTGJ);
    TreeTTGJ->SetBranchAddress("PhotonPtTTGJ",&PhotonPtTTGJ);
    TreeTTGJ->SetBranchAddress("NJetsTTGJ",&NJetsTTGJ);
    TreeTTGJ->SetBranchAddress("BJetsTTGJ",&BJetsTTGJ);
    TreeTTGJ->SetBranchAddress("WtTTGJ",&WtTTGJ);
    

    TreeZJ->SetBranchAddress("HTZJ",&HTZJ);
    TreeZJ->SetBranchAddress("MHTZJ",&MHTZJ);
    
    TreeZJ->SetBranchAddress("NJetsZJ",&NJetsZJ);
    TreeZJ->SetBranchAddress("BJetsZJ",&BJetsZJ);
    TreeZJ->SetBranchAddress("WtZJ",&WtZJ);

     
    TreeTTZ->SetBranchAddress("HTTTZ",&HTTTZ);
    TreeTTZ->SetBranchAddress("MHTTTZ",&MHTTTZ);
   
    TreeTTZ->SetBranchAddress("NJetsTTZ",&NJetsTTZ);
    TreeTTZ->SetBranchAddress("BJetsTTZ",&BJetsTTZ);
    TreeTTZ->SetBranchAddress("WtTTZ",&WtTTZ);



    // bins for determining pdf


    int nBinsMHTpdf=6;
    int nBinsNJpdf=4;
    double MHTbinspdf[7]={200.,300,400,500.,600,750.,950};
    double NJetsbinspdf[5]={4,5,6,7,8};



     int nBinsHT=8;
     int nBinsMHT=7;
     int nBinsPt=8;
     int nBinsNJ=6;
     int nBinsBJ=5;
     int nBinsS=25;
     double HTbins[9]={500.,650.,800,1000.,1200,1500,1700,2000,3000};
     double MHTbins[8]={200.,300,400,500.,600,750.,950,1500.};
     double Ptbins[9]={100,200.,300,400,500.,600,750.,1000,1500.};
     double NJetsbins[7]={4,5,6,7,8,9,12};
     double BJetsbins[6]={0,1,2,3,4,7};
     int nBinAN=18;
     double nBinANmax=18.5;



    TH2D *h2_MHTNj_Zinv=new TH2D("h2_MHTNj_Zinv","MHT[GeV], NJets",nBinsMHT,MHTbins,nBinsNJ,NJetsbins);
    
    TH2D *h2_MHTNj_ZinvVal=new TH2D("h2_MHTNj_ZinvVal","MHT[GeV], NJets",nBinsMHTpdf,MHTbinspdf,nBinsNJpdf,NJetsbinspdf);
    
    TH2D *h2_MHTNj_GJets=new TH2D("h2_MHTNj_GJets","MHT[GeV], NJets",nBinsMHT,MHTbins,nBinsNJ,NJetsbins);

    TH2D *h2_MHTNj_GJetsVal=new TH2D("h2_MHTNj_GJetsVal","MHT[GeV], NJets",nBinsMHTpdf,MHTbinspdf,nBinsNJpdf,NJetsbinspdf);
    


   for(int iz=0;iz<TreeZJ->GetEntries();iz++){
    TreeZJ->GetEntry(iz);
    int binNumber_Zinv = computeBin( MHTZJ, HTZJ, NJetsZJ, k13TeV);
    if(BJetsZJ==0){
      
   
    h2_MHTNj_Zinv->Fill(MHTZJ,NJetsZJ,WtZJ);
    h2_MHTNj_ZinvVal->Fill(MHTZJ,NJetsZJ,WtZJ);
   
    }  
    }


     for(int ig=0;ig<TreeGJ->GetEntries();ig++){
   TreeGJ->GetEntry(ig);
   int binNumber_GJets = computeBin( MHTGJ, HTGJ, NJetsGJ, k13TeV);
   if(BJetsGJ==0){
    
   
    h2_MHTNj_GJets->Fill(MHTGJ,NJetsGJ,WtGJ);
    h2_MHTNj_GJetsVal->Fill(MHTGJ,NJetsGJ,WtGJ);

    
    }  
    }





   TH2D *h_ZgR_MHTNj = (TH2D*)h2_MHTNj_Zinv->Clone("h_ZgR_MHTNj");
   



   TCanvas *c=new TCanvas("myCanvas","myCanvas");
   c->cd();
   h2_MHTNj_Zinv->Draw("colz text error");
   
   

   RooRealVar MHT("MHT","MHT",200,1500);
   RooRealVar NJets("NJets","NJets",4,12);

 // RooRealVar MHTfit("MHTfit","MHTfit",200,950);//950
 // RooRealVar NJetsfit("NJetsfit","NJetsfit",4,8);//8



   RooDataHist hdatahist("hdatahist","hpdf",RooArgList(MHT,NJets),Import(*h2_MHTNj_GJets));


   //RooDataHist hdatahistforFit("hdatahistforFit","hpdfforFit",RooArgList(MHTfit,NJetsfit),Import(*h2_MHTNj_GJetsVal));


  RooHistPdf histpdf("histpdf","histpdf",RooArgList(MHT,NJets),hdatahist);
 	
  MHT.setRange("myRange",200.0,950.0);
  NJets.setRange("myRange",4.,8.);	
	
  histpdf.fitTo(hdatahist,Range("myRange"));

//  histpdf.fitTo(hdatahistforFit);

  RooPlot* frameMHT = MHT.frame(Title("Projection on MHT"));
  RooPlot* frameNJet = NJets.frame(Title("Projection on NJets"));

  hdatahist.plotOn(frameMHT);
  hdatahist.plotOn(frameNJet);
  
  histpdf.plotOn(frameMHT); histpdf.plotOn(frameNJet);
   

  cout<<"Chi square MHT: "<<frameMHT->chiSquare()<<endl;
  cout<<"Chi square NJets: "<<frameNJet->chiSquare()<<endl;

  TCanvas *can=new TCanvas("myCanvas","myCanvas");
  can->Divide(2,1); 
  can->cd(1);
  frameMHT->Draw();
  can->cd(2);
  frameNJet->Draw();

	 













































}
