/*
 * robot suiveur de couleur avec PouriCam4 BlindBot
 * Projet ER DUT GEII 2016 
 * TPS et TBT
 * Arduino MEGA + CMUcam4 + adaptateur custom
 * base custom 4x4
 *
 */
#include <SoftwareSerial.h>
SoftwareSerial mySerial(10,3); // RX, TX

int xint=0,yint=0,n=0,limb=20,limh=100,flag=0,flag2=0,intconfidence=0,intpixel=0,limav=20,limar=50;//ini declaration de toutes les variblaes
int espace1=0,espace2=0,espace3=0,espace4=0,espace5=0,espace6=0,espace7=0,espace8=0;//ini declaration des espaces
int octetReception=0; // variable de stockage des valeurs reçues sur le port Série (ASCII)
char caractereRecu=0; // variable pour stockage caractère recuk
int compt=0; // variable comptage caractères reçus

String chaineReception="";//chaine "tampon"
String chainebrute="";//chaine qui sera traiter

//Definitio0 des ports
const int vit =80;

// Moteur Avant
const int enableMAVD = 7; 
const int enableMAVG = 4;
const int inMAVDA = 48;
const int inMAVDB = 49;
const int inMAVGA = 24;
const int inMAVGB = 25;

//Moteur Arrière
const int enableMARD = 5; 
const int enableMARG = 6;
const int inMARGA = 28;
const int inMARGB = 29;
const int inMARDA = 52;
const int inMARDB = 53;



void setup()
{
    pinMode(38, OUTPUT);//gauche
    pinMode(39, OUTPUT);  //droite
    pinMode(3, OUTPUT);//com?
    pinMode(10, INPUT);//com?
    pinMode(46,OUTPUT);//avancer
    pinMode(48,OUTPUT);//reculer
    // Open serial communications and wait for port to open:
    Serial.begin(9600);
    //while (!Serial)
    // set the data rate for the SoftwareSerial port
    mySerial.begin(19200);
    //while (!mySerial)
    mySerial.print("\r");
    delay (100);
  
    // Declaration de ports en tant que sortie
  pinMode(enableMAVD, OUTPUT);
  pinMode(enableMAVG, OUTPUT);
  pinMode(inMAVDA, OUTPUT);
  pinMode(inMAVDB, OUTPUT);
  pinMode(inMAVGA, OUTPUT);
  pinMode(inMAVGB, OUTPUT);
  
  pinMode(enableMARD, OUTPUT);
  pinMode(enableMARG, OUTPUT);
  pinMode(inMARDA, OUTPUT);
  pinMode(inMARDB, OUTPUT);
  pinMode(inMARGA, OUTPUT);
  pinMode(inMARGB, OUTPUT);

  //Déclaration des ports en tant qu'entrée


 }

void loop() 
{
//DEMARAGE 
  //mySerial.print("TC 100 200 4 60 10 90 \r");
  mySerial.print("TC 170 200 90 180 23 100 \r");//demarrage du track color
  mySerial.print("PM 1 \r");//demarrage poll mode(elimination des T)
  //delay (100);
 //AQUISITION
while (mySerial.available()>0) { // tant qu'un octet en réception
        flag=0;
        //Serial.println("debut");
         
         while((octetReception==58)||(octetReception==65)||(octetReception==67)||(octetReception==75)){
           //test si on a :ACK, tant que c'est le cas on efface la chaineReception(elimination ACK genant) 
                octetReception=mySerial.read(); // Lit le 1er octet reçu et le met dans la variable
                compt=compt+1;//seulment pour l'affichage
                //Serial.println("Ascii Caractere "+ String(compt) +" = "+ String(octetReception));
                //Serial.println(octetReception);
                
                chaineReception="";//raz du string
                compt=0; // RAZ compteur
                //flag=1;
                //flag2=1;
                delay(100); // pause obligatoire  
              }
                octetReception=mySerial.read(); // Lit le 1er octet reçu et le met dans la variable
                compt=compt+1;//incrementation
                //Serial.println("Ascii Caractere "+ String(compt) +" = "+ String(octetReception));//affichage du caractere reçu
                //Serial.println(octetReception);
 
          if (octetReception==13) { // si l'octet reçu est cariage return
            //Serial.println("Saut de ligne recu");//cad fin du paquet
            //Serial.println ("Chaine recue="+chaineReception);  //affiche la chaine recue
            chainebrute=chaineReception;//chaine stocker pour traitement plus loin
            chaineReception=""; //RAZ le String de réception
            compt=0; // RAZ compteur
            delay(100); // pause obligatoire
            break; // sort de la boucle while
            }
         else { // si le caractère reçu n'est pas un saut de ligne
           caractereRecu=char(octetReception); // convertit l'octet reçu en caractère
           chaineReception=chaineReception+caractereRecu; // ajoute le caratère au String
           }        
  //delay(100);
  }

//VERIFICTIONS (inutile maintenant ?)
//Serial.println("sortie while");
//Serial.println(flag);
//Serial.println("long");
//Serial.println(chainebrute.length());
//Serial.println(chainebrute);
//int t =chainebrute.charAt(n);
//Serial.println(t);
//elimination ack ?(inutile maintenant que prob ack+T regler ? )
if(flag==0)//test flag ?
  {
//TESTS DES ESPACES DANS LA CHAINE
//espace1 apres T
     do
    {
      n++;
      espace1=n;
    }while (chainebrute.charAt(n) !=32);//tant que le char analyser n'est pas un espaces ont boucle et ont incremente le compteur
     //Serial.println(espace1);// affichage du rang de l'espace
//espace2 apres mx
    do
    {
      n++;
      espace2=n;
    }while (chainebrute.charAt(n) !=32);
    //Serial.println(espace2);
//test espace3 apres my (do while)
    do
    {
      n++;
      espace3=n;
    }while (chainebrute.charAt(n) !=32);
   // Serial.println(espace3);
//test espace4 apres x1
    do
    {
      n++;
      espace4=n;
    }while (chainebrute.charAt(n) !=32);
    //Serial.println(espace4);
//test espace5 apres y1
     do
    {
      n++;
      espace5=n;
    }while (chainebrute.charAt(n) !=32);
   // Serial.println(espace5);
//test espace6 apres x2
     do
    {
      n++;
      espace6=n;
    }while (chainebrute.charAt(n) !=32);
    //Serial.println(espace6);
//test espace7 apres y2
     do
    {
      n++;
      espace7=n;
    }while (chainebrute.charAt(n) !=32);
    //Serial.println(espace7);
//test espace8 apres pixel
     do
    {
      n++;
      espace8=n;
    }while (chainebrute.charAt(n) !=32);
   // Serial.println(espace4=8);  

//EEXTRACTION ET CONVERSIONS DES CHAINES
  //extraction des chaines x et y (pourquoi y ?)

//String x = chainebrute.substring(espace1+1,espace2);
//Serial.println("chaine x");
//Serial.println(x);
String y = chainebrute.substring(espace2+1,espace3);
//Serial.println("chaine y");
//Serial.println(y);
/**extraction confidence
String confidencee = chainebrute.substring(espace8+1,chainebrute.length());// bonne fin?
Serial.println("chaine confidencee");
Serial.println(confidencee);**/
//extraction pixel
String pixel = chainebrute.substring(espace7+1,espace8);
//Serial.println("chaine pixel");
//Serial.println(pixel);
//raz des variables des espaces
    espace1=0;
    espace2=0;
    espace4=0;
    espace5=0;
    espace6=0;
    espace7=0;
    espace8=0;
    n=0;

//conversion 
   yint=atoi(y.c_str() );
   //Serial.println("xint");
   //Serial.println(xint);
   //yint=atoi(x.c_str() );
   //Serial.println("yint");
  // Serial.println(yint);
//intconfidence=atoi(confidencee.c_str() );
intpixel=atoi(pixel.c_str() );
//DETERMINATION DE LA DIRECTION
//deplacement intconfidence limav=50 limar=200 xint limb=40 limh=119 38g 39d 46av 48ar
int objet=0;
//Serial.println("objet:");
//Serial.println(objet);
if(yint==0 && intpixel==0)//aucun objet en vue xint=0 & intconfidence=0
      {
        objet=1;
        //Serial.println("aucun objet");
        //Moteurs Droite
      analogWrite(enableMAVD, vit);
      analogWrite(enableMARD, vit);
      
      digitalWrite(inMAVDA, HIGH);
      digitalWrite(inMAVDB, LOW);     
      digitalWrite(inMARDA, HIGH);
      digitalWrite(inMARDB, LOW);
      
   //Moteurs Gauche
   
      analogWrite(enableMAVG, vit);
      analogWrite(enableMARG, vit);
      
      digitalWrite(inMAVGA, HIGH);
      digitalWrite(inMAVGB, LOW);
      digitalWrite(inMARGA, LOW);
      digitalWrite(inMARGB, HIGH);
      }
if(yint>limb && yint<limh && intpixel>limav && intpixel<limar && objet==0)//0
  {
    //Serial.println("0stop");
//Moteurs Droite
      analogWrite(enableMAVD, 0);
      analogWrite(enableMARD, 0);
      
      digitalWrite(inMAVDA, LOW);
      digitalWrite(inMAVDB, HIGH);     
      digitalWrite(inMARDA, HIGH);
      digitalWrite(inMARDB, LOW);
      
   //Moteurs Gauche
   
      analogWrite(enableMAVG, 0);
      analogWrite(enableMARG, 0);
      
      digitalWrite(inMAVGA, HIGH);
      digitalWrite(inMAVGB, LOW);
      digitalWrite(inMARGA, LOW);
      digitalWrite(inMARGB, HIGH);  
  }
if((yint>limb) && (yint<limh) && (intpixel<limav) && (objet==0))//1
  {
    //Serial.println("1av");
    //Moteurs Droite
      analogWrite(enableMAVD, vit);
      analogWrite(enableMARD, vit);
      
      digitalWrite(inMAVDA, HIGH);
      digitalWrite(inMAVDB, LOW);     
      digitalWrite(inMARDA, HIGH);
      digitalWrite(inMARDB, LOW);
      
   //Moteurs Gauche
   
      analogWrite(enableMAVG, vit);
      analogWrite(enableMARG, vit);
      
      digitalWrite(inMAVGA, LOW);
      digitalWrite(inMAVGB, HIGH);
      digitalWrite(inMARGA, HIGH);
      digitalWrite(inMARGB, LOW);
  }
if((yint>limb) && (yint<limh) && (intpixel>limar) && (objet==0))//2  
  {
   // Serial.println("2ar");
      //Moteurs Droite
      analogWrite(enableMAVD, vit);
      analogWrite(enableMARD, vit);
      
      digitalWrite(inMAVDA, LOW);
      digitalWrite(inMAVDB, HIGH);    
      digitalWrite(inMARDA, LOW);
      digitalWrite(inMARDB, HIGH);
      
   //Moteurs Gauche
   
      analogWrite(enableMAVG, vit);
      analogWrite(enableMARG, vit);
      
      digitalWrite(inMAVGA, HIGH);
      digitalWrite(inMAVGB, LOW);
      digitalWrite(inMARGA, LOW);
      digitalWrite(inMARGB, HIGH);  
  } 
if(yint>limh && intpixel>limav && intpixel<limar && objet==0)//3 
  {
    //Serial.println("3g");
    //Moteurs Droite
      analogWrite(enableMAVD, vit);
      analogWrite(enableMARD, vit);
      
      digitalWrite(inMAVDA, LOW);
      digitalWrite(inMAVDB, HIGH);     
      digitalWrite(inMARDA, HIGH);
      digitalWrite(inMARDB, LOW);
      
   //Moteurs Gauche
   
      analogWrite(enableMAVG, vit);
      analogWrite(enableMARG, vit);
      
      digitalWrite(inMAVGA, HIGH);
      digitalWrite(inMAVGB, LOW);
      digitalWrite(inMARGA, LOW);
      digitalWrite(inMARGB, HIGH);
  }  
if(yint<limb && intpixel>limav && intpixel<limar && objet==0)//4  
  {
   // Serial.println("4d");
 //Moteurs Droite
      analogWrite(enableMAVD, vit);
      analogWrite(enableMARD, vit);
      
      digitalWrite(inMAVDA, HIGH);
      digitalWrite(inMAVDB, LOW);     
      digitalWrite(inMARDA, LOW);
      digitalWrite(inMARDB, HIGH);
      
   //Moteurs Gauche
   
      analogWrite(enableMAVG, vit);
      analogWrite(enableMARG, vit);
      
      digitalWrite(inMAVGA, LOW);
      digitalWrite(inMAVGB, HIGH);
      digitalWrite(inMARGA, HIGH);
      digitalWrite(inMARGB, LOW);  
  }  
if(yint>limh && intpixel<limav && objet==0)//5 
  {
   // Serial.println("5avd");
   //Moteurs Droite
      analogWrite(enableMAVD, (vit-30));
      analogWrite(enableMARD, (vit-30));
      
      digitalWrite(inMAVDA, HIGH);
      digitalWrite(inMAVDB, LOW);     
      digitalWrite(inMARDA, HIGH);
      digitalWrite(inMARDB, LOW);
      
   //Moteurs Gauche
   
      analogWrite(enableMAVG, vit+150);
      analogWrite(enableMARG, vit+150);
      
      digitalWrite(inMAVGA, LOW);
      digitalWrite(inMAVGB, HIGH);
      digitalWrite(inMARGA, HIGH);
      digitalWrite(inMARGB, LOW);
  }  
if(yint<limb && intpixel<limav && objet==0)//6
  {
    //Serial.println("6avg");
    //Moteurs Droite
      analogWrite(enableMAVD, vit+150);
      analogWrite(enableMARD, vit+150);
      
      digitalWrite(inMAVDA, HIGH);
      digitalWrite(inMAVDB, LOW);     
      digitalWrite(inMARDA, HIGH);
      digitalWrite(inMARDB, LOW);
      
   //Moteurs Gauche
   
      analogWrite(enableMAVG, (vit-30));
      analogWrite(enableMARG, (vit-30));
      
      digitalWrite(inMAVGA, LOW);
      digitalWrite(inMAVGB, HIGH);
      digitalWrite(inMARGA, HIGH);
      digitalWrite(inMARGB, LOW);
  }  
if(yint<limb && intpixel>limar && objet==0)//7    
  {
  //  Serial.println("7arg");
    //Moteurs Droite
      analogWrite(enableMAVD, vit-30);
      analogWrite(enableMARD, vit-30);
      
      digitalWrite(inMAVDA, LOW);
      digitalWrite(inMAVDB, HIGH);    
      digitalWrite(inMARDA, LOW);
      digitalWrite(inMARDB, HIGH);
      
   //Moteurs Gauche
   
      analogWrite(enableMAVG, (vit+150));
      analogWrite(enableMARG, (vit+150));
      
      digitalWrite(inMAVGA, HIGH);
      digitalWrite(inMAVGB, LOW);
      digitalWrite(inMARGA, LOW);
      digitalWrite(inMARGB, HIGH);
  }  
if(yint>limh && intpixel>limar && objet==0)//8
  {
   // Serial.println("8ard");
      //Moteurs Droite
      analogWrite(enableMAVD, (vit+150));
      analogWrite(enableMARD, (vit+150));
      
      digitalWrite(inMAVDA, LOW);
      digitalWrite(inMAVDB, HIGH);    
      digitalWrite(inMARDA, LOW);
      digitalWrite(inMARDB, HIGH);
      
   //Moteurs Gauche
   
      analogWrite(enableMAVG, vit-30);
      analogWrite(enableMARG, vit-30);
      
      digitalWrite(inMAVGA, HIGH);
      digitalWrite(inMAVGB, LOW);
      digitalWrite(inMARGA, LOW);
      digitalWrite(inMARGB, HIGH);
  }


  
 

 }//fin du test flag



}






