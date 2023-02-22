//------------------------------------------------------------------------| DATACONV.H                                   //
//                                                                        | Daten Konvertierungs Funktionen,             //                            //
//                                                                        | von Dietmar Schrausser, (C) SCHRAUSSER 2011  // 
//

//char ccc[100];

char *ftoa(double x_, char *c_, int dez ); // ftoa(), fliesskomma zu char

//--------------------------------------------------------------------------------------| ftoa(), fliesskomma zu char
//                                                                                      | bsp. ftoa(fvar, cvar, 8);
char *ftoa(double x_, char *c_, int dez ) 
{
	int iLauf;
	int nZiffern=100, npkt, vz;
	char *string; 
		
	strcpy(c_,"");

	string = ecvt( x_, nZiffern, &npkt, &vz  );

	if(vz!=0)                                     c_[0]='-' ;  // x<0
	
	if(npkt<=0)                                                 // x<1
	{
		                                          c_[vz]='0';
										          c_[vz+1]='.' ;
		for(iLauf=1;iLauf<=-npkt;iLauf++)         c_[iLauf+vz+1]='0' ; 
		for(iLauf=0;iLauf<dez+npkt;iLauf++)       c_[iLauf-npkt+2+vz]=string[iLauf] ; 
	}

	if(npkt>0)                                                  // x>=1
	{
		for(iLauf=0;iLauf<npkt;iLauf++)           c_[iLauf+vz]=string[iLauf] ;  
											      c_[iLauf+vz]='.'; 
		for(iLauf=npkt;iLauf<=dez+npkt-1;iLauf++) c_[iLauf+1+vz]=string[iLauf]  ; 
	}

	return c_;
}