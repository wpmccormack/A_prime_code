#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>

#include <TFile.h>
#include <TProfile.h>
#include <TTree.h>
#include <TH1.h>
#include <TF1.h>
#include <TCanvas.h>
#include "TApplication.h"
#include "TString.h"

#include "TClonesArray.h"
#include "TH2.h"
#include "THStack.h"

#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <TTreeReaderArray.h>
#include <TChain.h>
#include "TLorentzVector.h"

#include "ExRootAnalysis/ExRootClasses.h"
#include "ExRootAnalysis/ExRootTreeReader.h"
#include "ExRootAnalysis/ExRootTreeWriter.h"
#include "ExRootAnalysis/ExRootTreeBranch.h"
#include "ExRootAnalysis/ExRootResult.h"
#include "ExRootAnalysis/ExRootUtilities.h"

using namespace std;

int zp_a_ana(){

  //Defining plots.  Syntax is ("Name", "Plot title; x-axis label; y-axis label", number of bins, leftmost edge of first bin, rightmost edge of last bin)
  TH1F* Photon_E = new TH1F("Photon_E","",70,0,7);
  TH1F* A_E = new TH1F("A_E","",70,0,7);
  TH1F* MM = new TH1F("Missing_Mass","",100,0,.0001);
  
  gSystem->Load("libExRootAnalysis.so");

  //This must be changed to match your output root file
  TFile *myinputfile = new TFile("output_a_zp.root");

  TTree *t = (TTree*)myinputfile->Get("LHEF");

  ExRootTreeReader *treeReader = new ExRootTreeReader(t);

  TClonesArray *branchPart = treeReader->UseBranch("Particle");

  Long64_t allEntries = treeReader->GetEntries();

  cout << "** Chain contains " << allEntries << " events" << endl;

  TRootLHEFParticle *Part[4];

  Long64_t entry;

  // Loop over all events
  for(entry = 0; entry < allEntries; ++entry)
  {

    //if(entry%100 == 0){
    
      treeReader->ReadEntry(entry);
      if(branchPart->GetEntriesFast() >= 2)
	{
	  //if the generation was e+ e- > a zp, then I think the 0th particle is e+, the 1st is the e-, the 2nd is the a, and the 3rd is the A' (which is denoted as zp in the madgraph model)
	  Part[0] = (TRootLHEFParticle*) branchPart->At(0);
	  Part[1] = (TRootLHEFParticle*) branchPart->At(1);
	  Part[2] = (TRootLHEFParticle*) branchPart->At(2);
	  //cout<<Part[2]->PID<<endl;
	  //cout<<Part[2]->M<<endl;
	  //cout<<Part[2]->Eta<<endl;
	  //cout<<"photon E "<<Part[2]->E<<endl;
	  Photon_E->Fill(Part[2]->E);
	  Part[3] = (TRootLHEFParticle*) branchPart->At(3);
	  //cout<<Part[3]->PID<<endl;
	  //cout<<Part[3]->M<<endl;
	  //cout<<Part[3]->Eta<<endl;
	  A_E->Fill(Part[3]->E);
	  MM->Fill( sqrt( (Part[0]->E + Part[1]->E - Part[2]->E)*(Part[0]->E + Part[1]->E - Part[2]->E) - (Part[0]->Px + Part[1]->Px - Part[2]->Px)*(Part[0]->Px + Part[1]->Px - Part[2]->Px) - (Part[0]->Py + Part[1]->Py - Part[2]->Py)*(Part[0]->Py + Part[1]->Py - Part[2]->Py) - (Part[0]->Pz + Part[1]->Pz - Part[2]->Pz)*(Part[0]->Pz + Part[1]->Pz - Part[2]->Pz) ) );
	}
      
      //}
  }

  //You should change the name of this output file every time you run
  TFile file("test_plot.root","RECREATE");
  Photon_E->Write();
  A_E->Write();
  MM->Write();
  
  return 0;
}
