enum binning { kRA2 , k13TeV , kNumBinning };

int classicRA2(double MHT, double HT, int NJets){

  

  return -1 ;

}

int scrabble(double MHT, double HT, double NJets ){

  //cout << "SCRABBLE" << endl;
  

  if( MHT < 200 || HT < 500 || NJets < 4 ) return -1 ;

  int binHTMHT = -1;
  int binNJet = -1;

  if( MHT > 200 && MHT < 500 ){

    //cout << "low MHT" << endl;

    if( HT > 500 && HT < 800 ) 
      binHTMHT = 1;
    else if( HT > 800 && HT < 1200 ) 
      binHTMHT = 2;
    else if( HT > 1200 ) 
      binHTMHT = 3;
    else 
      return -1;

  }else if( MHT > 500 && MHT < 750 ){

    //cout << "med MHT" << endl;

    if( HT > 500 && HT < 1200 )
      binHTMHT = 4 ; 
    else if( HT > 1200 ) 
      binHTMHT = 5;
    else
      return -1;

  }else if( MHT > 750 ){

    //cout << "high MHT" << endl;

    if( HT > 800 )
      binHTMHT = 6 ; 
    else 
      return -1;

  }else 
    return -1;

  if( NJets >= 4 && NJets <= 6 ){
      //low NJet
      binNJet = 0 ;
  }else if( NJets >= 7 && NJets <= 8 ){
      //Medium NJet
      binNJet = 1 ;
  }else if( NJets >= 9 ){
      //High NJet
      binNJet = 2;
  }else
     return -1;


  //cout << "binNJet: " << binNJet << endl;
  //cout << "binHTMHT: " << binHTMHT << endl;

  return binNJet*6+binHTMHT ;



}



int  computeBin(double MHT, double HT, double NJets,binning bins = k13TeV){
  
  //cout << "computeBin" << endl;

  if( bins == kRA2 ) return classicRA2( MHT , HT , NJets ) ;  
  else if( bins == k13TeV ) return scrabble( MHT , HT , NJets ) ;  
  else { 
    cout << "computeBin() No binning found!" << endl;
    return -1; 
  }

}
