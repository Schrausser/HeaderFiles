//------------------------------------------------------------------------| DATACONV.HPP                                 //
//                                                                        | Daten Konvertierungs Funktionen,             // 
//                                                                        | von Dietmar Schrausser, (C) SCHRAUSSER 2011  // 
//

//#include "";
#include "math.h"
#include "time.h"
 
CString ftoc(double x0, int dez);               // ftoc(), fliesskomma zu CString
CString ftoc_exp(double x0, int dez, int sw );  // ftoc_exp(), fliesskomma zu CString in exponentialschreibweise
CString itoc(int x_);                           // itoc(), integer zu CString
CString ctoc(char *c);                          // ctoc(), char zu CString 
char *ctoa(CString c_);                         // ctoa(), CString zu char
int ftoi(double x_);                            // ftoi(), fliesskomma zu integer 
double itof(int x_);                            // itof(), integer zu fliesskomma
  
//CString CompileStamp(BOOL Lngw);

//--------------------------------------------------------------------------------------| ftoc(), fliesskomma zu CString
//                                                                                      | bsp. cvar= ftoc(fvar, 8);
CString ftoc( double x0, int dez ) 
{
	                 int nZ=100, npkt,  vz;
	char *str = ecvt(x0, nZ,    &npkt, &vz  );

		                             CString c_=""; 
	if(vz!=0)                                c_+='-';   // x<0
	
	if(npkt<=0)                                         // x<1
	{
		                                     c_+='0';
										     c_+='.';
		for(int i_=1;i_<=-npkt;i_++)         c_+='0'; 
		for(    i_=0;i_<dez+npkt;i_++)       c_+=str[i_]; 
	}

	if(npkt>0)                                         // x>=1
	{
		for(int i_=0;i_<npkt;i_++)           c_+=str[i_];  
										     c_+='.'; 
		for(    i_=npkt;i_<=dez+npkt-1;i_++) c_+=str[i_]; 
	}

	                                  return c_;     // CString
}

// alternativ-version //
//--------------------------------------------------------------------------------------| ftoc(), fliesskomma zu CString
//                                                                                      | bsp. cvar= ftoc(fvar, 8);
//CString ftoc(double x0 /*fliesskommavariable*/, int dezstellen /*dezimalstellen*/ ) 
/*{
	CString c_; 
	        c_="";
	
	char ccc[200];
	int sw_E;
	                   dezstellen+=2;

		                       int dezstellen1,  vorz;
	strcpy(ccc,ecvt(x0,dezstellen,&dezstellen1, &vorz)); //double to string
		
	double a_x=sqrt(pow(x0,2));//absolutwert

						  int leng; //anzahl der ziffern vor dem dezimalpunkt 
		if(a_x<1 )            leng=0;
		
		if(a_x>=1 && a_x<10)   leng=1;
		if(a_x>=10 && a_x<100) leng=2;
		if(a_x>=100 && a_x<1000) leng=3;
		if(a_x>=1000 && a_x<10000) leng=4;
		if(a_x>=10000 && a_x<100000) leng=5;
		if(a_x>=100000 && a_x<1000000) leng=6;
		if(a_x>=1000000 && a_x<10000000) leng=7;
		if(a_x>=10000000 && a_x<100000000) leng=8;
		if(a_x>=100000000 && a_x<1000000000) leng=9;
		if(a_x>=1000000000 && a_x<10000000000) leng=10;
		if(a_x>=10000000000 && a_x<100000000000) leng=11;
		if(a_x>=100000000000 && a_x<1000000000000) leng=12;
		if(a_x>=1000000000000 && a_x<10000000000000) leng=13;
		if(a_x>=10000000000000 && a_x<100000000000000) leng=14;
		if(a_x>=100000000000000 && a_x<1000000000000000) leng=15;
		if(a_x>=1000000000000000 && a_x<10000000000000000) leng=16;
		if(a_x>=10000000000000000 ) sw_E=1;

		                     int n0;
							     n0=0;

		if(a_x<0.1 && a_x>=0.01) n0=1; //anzahl nullen nach dem dezimalpunkt
		if(a_x<0.01 && a_x>=0.001) n0=2; 
		if(a_x<0.001 && a_x>=0.0001) n0=3;
		if(a_x<0.0001 && a_x>=0.00001) n0=4;
		if(a_x<0.00001 && a_x>=0.000001) n0=5;
		if(a_x<0.000001 && a_x>=0.0000001) n0=6;
		if(a_x<0.0000001 && a_x>=0.00000001) n0=7;
		if(a_x<0.00000001 && a_x>=0.000000001) n0=8;
		if(a_x<0.000000001 && a_x>=0.0000000001) n0=9;
		if(a_x<0.0000000001 && a_x>=0.00000000001) n0=10;
		if(a_x<0.00000000001 && a_x>=0.000000000001) n0=11;
		if(a_x<0.000000000001 && a_x>=0.0000000000001) n0=12;
		if(a_x<0.0000000000001 && a_x>=0.00000000000001) n0=13;
		if(a_x<0.00000000000001 && a_x>=0.000000000000001) n0=14;
		if(a_x<0.000000000000001 && a_x>=0.0000000000000001) n0=15;
		if(a_x<0.0000000000000001 && a_x>=0.00000000000000001) n0=16;
		if(a_x<0.00000000000000001 ) sw_E=1;

		if(a_x==0) {leng=0;sw_E=0;}

	if(sw_E==1)            c_="E";	
	if(sw_E!=1)
	{
		if(x0<0 )          c_+="-";  //x<0	
				
		for(int iLauf=0;iLauf<leng;iLauf++)
		                   c_+=ccc[iLauf]; //ziffern vor dezimalpunkt einlesen

		if(x0>=0 && x0<1 ) c_+="0."; //0<=x<1
		else               c_+=".";  //dezimalpunkt

		if(n0>0)for(iLauf=1;iLauf<=n0 ;iLauf++)
			               c_+="0";//nullen nach dezimalpunkt generieren

		for(iLauf=leng;iLauf<=leng+dezstellen-n0-3 ;iLauf++)
			               c_+=ccc[iLauf];//ziffern nach dezimalpunkt einlesen
	}
	                	
	                return c_; //CString
}
*/

//--------------------------------------------------------------------------------------| ftoc_exp(), fliesskomma zu CString in exponentialschreibweise
//                                                                                      | bsp. cvar= ftoc(fvar, 8, 1);
CString ftoc_exp(double x0 /*fliesskommavariable*/, int dezstellen /*dezimalstellen*/, int sw /*schreibweise*/ ) 
{
	CString c_; 
	        c_="";

	char ccc[200];
	int sw_E;
	                   dezstellen+=2; 
	
		                       int dezstellen1,  vorz;
	strcpy(ccc,ecvt(x0,dezstellen,&dezstellen1, &vorz)); //double to string
		
	double a_x=sqrt(pow(x0,2));//absolutwert

						  CString leng; //anzahl der ziffern vor dem dezimalpunkt 
		if(a_x<1 )            leng="0";
		
		if(a_x>=1 && a_x<10)   leng="0";
		if(a_x>=10 && a_x<100) leng="1";
		if(a_x>=100 && a_x<1000) leng="2";
		if(a_x>=1000 && a_x<10000) leng="3";
		if(a_x>=10000 && a_x<100000) leng="4";
		if(a_x>=100000 && a_x<1000000) leng="5";
		if(a_x>=1000000 && a_x<10000000) leng="6";
		if(a_x>=10000000 && a_x<100000000) leng="7";
		if(a_x>=100000000 && a_x<1000000000) leng="8";
		if(a_x>=1000000000 && a_x<10000000000) leng="9";
		if(a_x>=10000000000 && a_x<100000000000) leng="10";
		if(a_x>=100000000000 && a_x<1000000000000) leng="11";
		if(a_x>=1000000000000 && a_x<10000000000000) leng="12";
		if(a_x>=10000000000000 && a_x<100000000000000) leng="13";
		if(a_x>=100000000000000 && a_x<1000000000000000) leng="14";
		if(a_x>=1000000000000000 && a_x<10000000000000000) leng="15";
		if(a_x>=10000000000000000 ) sw_E=1;
                  
		if(a_x<0.1 && a_x>=0.01) leng="-1"; 
		if(a_x<0.01 && a_x>=0.001) leng="-2"; 
		if(a_x<0.001 && a_x>=0.0001) leng="-3";
		if(a_x<0.0001 && a_x>=0.00001) leng="-4";
		if(a_x<0.00001 && a_x>=0.000001) leng="-5";
		if(a_x<0.000001 && a_x>=0.0000001) leng="-6";
		if(a_x<0.0000001 && a_x>=0.00000001) leng="-7";
		if(a_x<0.00000001 && a_x>=0.000000001) leng="-8";
		if(a_x<0.000000001 && a_x>=0.0000000001) leng="-9";
		if(a_x<0.0000000001 && a_x>=0.00000000001) leng="-10";
		if(a_x<0.00000000001 && a_x>=0.000000000001) leng="-11";
		if(a_x<0.000000000001 && a_x>=0.0000000000001) leng="-12";
		if(a_x<0.0000000000001 && a_x>=0.00000000000001) leng="-13";
		if(a_x<0.00000000000001 && a_x>=0.000000000000001) leng="-14";
		if(a_x<0.000000000000001 && a_x>=0.0000000000000001) leng="-15";
		if(a_x<0.0000000000000001 && a_x>=0.00000000000000001) leng="-16";
		if(a_x<0.00000000000000001 ) sw_E=1;

		if(a_x==0) {leng="0";sw_E=0;}

	if(sw_E==1)   c_="E";	
	if(sw_E!=1)
	{
		if(x0<0 ) c_+="-";
		          c_+=ccc[0];
		          c_+="."; 
		
		for(int iLauf=1;iLauf<=dezstellen-3;iLauf++)  //ziffern nach dezimalpunkt einlesen
			      c_+=ccc[iLauf];
		 
		if(sw==0) c_+="x10h";    // schreibweise

		if(sw==1)
		{                        		
		          c_+="E";       
		    if(x0>= 1 ||   
	           x0<=-1)   	
		          c_+="+"; 
		}
		          c_+=leng;	 
	}
	       return c_; //CString
}

//--------------------------------------------------------------------------------------| itoc(), integer zu CString
//                                                                                      | bsp. cvar= itoc(ivar);
CString itoc(int x_) 
{
	          char ccc[100];
           itoa(x_,ccc,10);
	const char* cc=ccc;																	 
	CString c_=cc;		                    
	 
	 return c_; //CString
}

//--------------------------------------------------------------------------------------| ctoc(), char zu CString  
//                                                                                      | bsp. cstr= ctoc(chr[1]);
CString ctoc(char *c)
{
	const char *cc;
	            cc=c;
	     return cc; //CString
}

//--------------------------------------------------------------------------------------| ftoi(), fliesskomma zu integer 
//                                                                                      | bsp. ivar= ftoi(fvar);
int ftoi(double x_) 
{
	int    i_;
		   i_=0;
		   i_=atoi(ftoc(x_,8 /*dezimalstellen*/));
	return i_; //int
}

//--------------------------------------------------------------------------------------| itof(), integer zu fliesskomma  
//                                                                                      | bsp. fvar= itof(ivar);
double itof(int x_){return atoi(itoc(x_));};

//--------------------------------------------------------------------------------------| ctoa(), CString zu char  
//                                                                                      | bsp. chr= ctoa(cstr);
char *ctoa(CString c_)
{
	 char *c="";
	strcpy(c,c_);   
	return c;     //charpointer
}




