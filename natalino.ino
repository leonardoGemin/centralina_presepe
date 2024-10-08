/* *********************************************************
 * Centralina Alba-Giorno-Tramonto-Notte per presepe
 *
 * Created on 09 december 2017
 *
 * by Leonardo Gemin
 * web: lgemin.altervista.org
 *
/* *********************************************************/




//DEFINIZIONE PIN DI INPUT/OUTPUT

#define alba_diss         2   //dissolvenza, VERDE
#define giorno_diss       3   //dissolvenza, ARANCIONE
#define tramonto_diss     4   //dissolvenza, MARRONE
#define notte_diss        5   //dissolvenza, BLU

#define casette          22   //sincro
#define fuoco            23   //sincro

#define temp_alba        A0   //potenziometro, VERDE
#define temp_giorno      A1   //potenziometro, ARANCIONE
#define temp_tramonto    A2   //potenziometro, MARRONE
#define temp_notte       A3   //potenziometro, BLU



//VARIABILI GLOBALI

double fasi[8];
double m = 10 / 32 ;
double q = 20;


/* *************************************************** */
/* *********************  SETUP  ********************* */
/* *************************************************** */
void setup() {
  Serial.begin( 9600 );

  //Dichiarazione INPUT/OUTPUT
  pinMode( alba_diss, OUTPUT );
  pinMode( giorno_diss, OUTPUT );
  pinMode( tramonto_diss, OUTPUT );
  pinMode( notte_diss, OUTPUT );
  
  pinMode( casette, OUTPUT );
  pinMode( fuoco, OUTPUT );
  
  pinMode( temp_alba, INPUT );
  pinMode( temp_giorno, INPUT );
  pinMode( temp_tramonto, INPUT );
  pinMode( temp_notte, INPUT );


  //Dichiarazione 
  analogWrite( alba_diss, 255 );
  analogWrite( giorno_diss, 255 );
  analogWrite( tramonto_diss, 255 );
  analogWrite( notte_diss, 255 );
  
  digitalWrite( casette, HIGH );
  digitalWrite( fuoco, HIGH );

  delay(5000);
}


/* *************************************************** */
/* ******************  CICLO LOOP  ******************* */
/* *************************************************** */
void loop() {
  //DICHIARAZIONE DURATA DI OGNI FASE
  fasi[0] = fasi[1] = analogRead( temp_alba ) * m + q ;       //ALBA 1, 2
  fasi[2] = fasi[3] = analogRead( temp_giorno ) * m + q ;     //GIORNO 1, 2
  fasi[4] = fasi[5] = analogRead( temp_tramonto ) * m + q ;   //TRAMONTO 1, 2
  fasi[6] = fasi[7] = analogRead( temp_notte ) * m + q ;      //NOTTE 1, 2
  
  
  // FASE 0: ALBA_1 
  for ( int i=0; i<256; i++ ) {
    analogWrite( alba_diss, i );
    analogWrite( giorno_diss, 0 );
    analogWrite( tramonto_diss, 0 );
    analogWrite( notte_diss, 255-i );
  
    digitalWrite( fuoco, LOW );
    
    if ( i<128 ) {
      digitalWrite( casette, LOW );
    } else {
      digitalWrite( casette, HIGH );
    }

    delay( fasi[0] );
  }
  
  // FASE 1: ALBA_2 
  for ( int i=0; i<256; i++ ) {
    analogWrite( alba_diss, 255-i );
    analogWrite( giorno_diss, i );
    analogWrite( tramonto_diss, 0 );
    analogWrite( notte_diss, 0 );
  
    digitalWrite( fuoco, HIGH );
    
    if ( i<128 ) {
      digitalWrite( casette, HIGH );
    } else {
      digitalWrite( casette, LOW );
    }

    delay( fasi[1] );
  }
  
  // FASE 2: GIORNO_1
  for ( int i=0; i<256; i++ ) {
    analogWrite( alba_diss, 0 );
    analogWrite( giorno_diss, 255 );
    analogWrite( tramonto_diss, 0 );
    analogWrite( notte_diss, 0 );
  
    digitalWrite( casette, LOW );
    digitalWrite( fuoco, LOW );

    delay( fasi[2] );
  } 

  // FASE 3: GIORNO_2
  for ( int i=0; i<256; i++ ) {
    analogWrite( alba_diss, 0 );
    analogWrite( giorno_diss, 255 );
    analogWrite( tramonto_diss, 0 );
    analogWrite( notte_diss, 0 );
  
    digitalWrite( casette, LOW );
    if ( i<128 ) {
      digitalWrite( fuoco, LOW );
    } else {
      digitalWrite( fuoco, HIGH );
    }

    delay( fasi[3] );
  }

  // FASE 4: TRAMONTO_1
  for ( int i=0; i<256; i++ ) {
    analogWrite( alba_diss, 0 );
    analogWrite( giorno_diss, 255-i );
    analogWrite( tramonto_diss, i );
    analogWrite( notte_diss, 0 );
  
    digitalWrite( casette, LOW );
    digitalWrite( fuoco, HIGH );
    
    delay( fasi[4] );
  }

  // FASE 5: TRAMONTO_2
  for ( int i=0; i<256; i++) {
    analogWrite( alba_diss, 0 );
    analogWrite( giorno_diss, 0 );
    analogWrite( tramonto_diss, 255-i );
    analogWrite( notte_diss, i );
  
    digitalWrite( casette, HIGH );
    digitalWrite( fuoco, HIGH );

    delay( fasi[5] );
  }

  // FASE 6: NOTTE_1
  for ( int i=0; i<256; i++) {
    analogWrite( alba_diss, 0 );
    analogWrite( giorno_diss, 0 );
    analogWrite( tramonto_diss, 0 );
    analogWrite( notte_diss, 255 );
  
    digitalWrite( casette, HIGH );
    if ( i<128 ) {
      digitalWrite( fuoco, HIGH );
    } else {
      digitalWrite( fuoco, LOW );
    }
    
    delay( fasi[6] );
  }

  // FASE 7: NOTTE_2
  for ( int i=0; i<256; i++) {
    analogWrite( alba_diss, 0 );
    analogWrite( giorno_diss, 0 );
    analogWrite( tramonto_diss, 0 );
    analogWrite( notte_diss, 255 );
  
    digitalWrite( casette, LOW );
    digitalWrite( fuoco, LOW );

    delay( fasi[7] );
  }

}
