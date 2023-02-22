//---------------------------------------------------------------------------------------| FN_SORT.H                                    //
//                                                                                       | Vektor Sortierungs-Funktion                  // 
//                                                                                       | von Dietmar Schrausser, (C) SCHRAUSSER 2011  // 
//

//#include "_"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>
#include <search.h>
#include <iostream.h>
//#include "D:\_EIGENEDATEIEN_\1_LAUFENDES\1_SYSTEM\3_C_PROGRAMME\__H_C_\DATACONV.H"

void fn_sort(char in_[33010][20],  int n_, short sw); //fn_sort(), sortiert eine datenvektor
int     sort_function( const void *a, const void *b); //


//--------------------------------------------------------------------------------------| fn_sort(), sortiert eine datenvektor                 //
//                                                                                      | bsp. fn_sort(in_, 300, 0);                           //
//                                                                                      | dateiausgabe des sortierten vektors in "~tmp_sort"   //
//                                                                                      | vektorausgebe des sortierten vektors in double out_  //

void fn_sort(char in_[33010][20]/*String Vektor*/, int n_/*Anzahl der Werte n*/, short sw/*aufsteigend(0)/absteigend(1)*/)    
{	
	FILE   *inStream,*outStream; 

	int x, iLauf, jLauf;

	char *fl="~tmp_sort";

	double min, out_[33010];//
	                                                      min=atof(in_[0]); 
	for (iLauf=1;iLauf< n_;iLauf++) if(atof(in_[iLauf]) < min) min = atof(in_[iLauf]); //minimalwertbestimmung
	
	if(min <0) //bei negativwerten subtraktion von min (nullsetzung), qsort funktion erkennt minuszeichen nicht (stringfunktion) 
	{
		                                        outStream = fopen( fl, "w" );
		for (iLauf=0;iLauf< n_;iLauf++) fprintf(outStream, "%f\n", atof(in_[iLauf])-min);
		                                fclose( outStream );
		                                        
		                                        inStream = fopen( fl, "r" ); 
		for (iLauf=0;iLauf< n_;iLauf++) fscanf( inStream, "%s",  in_[iLauf]);
		                                fclose( inStream  );
		
		/* vektordefinition (CString ftoc besser...)								 
		for (iLauf=0;iLauf< n_;iLauf++)
		{
			->ftoa(atof(in_[iLauf])-min,tmp_c,16);
			        strcpy(in_[iLauf],tmp_c);
		}*/
	}
	outStream = fopen( fl, "w" );

	for(iLauf=0;iLauf<n_;iLauf++)//führende nullen setzen, sodass die zeichenlänge konstant ist (qsort stringfunktionsbedingte modifikation)
	{
		                     x=strlen(in_[iLauf]);
        for(jLauf=0;jLauf<15-x;jLauf++) {fprintf(outStream, "0"); }
		                                fprintf(outStream, "%s\n",in_[iLauf]); 
	/* vektordefinition 
		for(jLauf=0;jLauf<15-x;jLauf++) tmp_c[jLauf]='0';
			                            strcpy(tmp_c, in_[iLauf]);
										       strcpy(in_[iLauf],tmp_c);*/
	}
	fclose( outStream );
	                                        inStream = fopen( fl, "r" );
	for (iLauf=0;iLauf< n_;iLauf++) fscanf( inStream, "%s",  in_[iLauf]); //modifizierte werte einlesen	
	                                fclose( inStream  );
	
	qsort((void *)in_, n_, sizeof(in_[0]), sort_function);//qsort Funktion
     
	if (min>=0) min=0; // bei negativwerten addition von min
	                                      
                                   outStream = fopen( fl,"w" );
	
	if (!sw) for(iLauf=0;iLauf<=n_-1;iLauf++)//aufsteigend
	{   
		                           out_[iLauf]=atof(in_[iLauf])+min; //vektor ausgabe 
		fprintf( outStream, "%f",out_[iLauf]); //datei ausgabe 
		if(iLauf<n_-1)fprintf( outStream, "\n"); 
	
	}
	
	if (sw) for(iLauf=n_-1;iLauf>=0;iLauf--)//absteigend
	{
		                            out_[iLauf]=atof(in_[iLauf])+min; //vektor ausgabe 
		fprintf( outStream, "%f", out_[iLauf]);//datei ausgabe 
		if(iLauf>0)fprintf( outStream, "\n"); 
	}
        fclose( outStream );	
}

int sort_function( const void *a, const void *b)
{
	     return( strcmp((char*)a,      (char*)b) );
}


