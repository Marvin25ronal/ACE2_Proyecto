
import meter.*;
import processing.serial.*;
PImage imagen_gota;
PImage fondo;

Serial port;
Meter meter_temperatura;
Meter meter_Aire;
Meter meter_Agua;
Meter meter_Peso;

int opcion=1;

void setup(){
size(1200,600);

imagen_gota=loadImage("gotas.jpeg");
fondo=loadImage("calor.jpg");

port = new Serial(this,"COM13",9600);


Meter_sensor_Temperatura();
Meter_sensor_Aire();
Meter_sensor_Agua();
Meter_sensor_Peso();
}
 int [] temp = new int[10];
 int [] agua = new int[10];
 int [] aire = new int[10];
 int [] peso = new int[10];
 int a=0;
 int b=0;
 int c =0;
 int e =0;
 
 String fecha= "";
 String hora ="";
 String latitud = "";
 String longitud = "";
 String uso ="";
 String lleno="";
 String [] list = new String [10];

void draw(){
//background(fondo);
//image(fondo,0,0);
image (fondo, 0,0, 1200,600);

 menu();

  if(port.available()>0){
     
    String valor = port.readStringUntil('\n');
    
    if(valor==null){
      if(list[0]!=null){
        pintar_todo();
      }
      return;
   
    }
    String [] temp_list1 = split(valor,','); 
    if(temp_list1.length!=10){
      if(list[0]!=null){
       pintar_todo();
      }
       
    }else{
      list=temp_list1;
       pintar_todo();
    }
   
    print(valor);
   
  
   }
   if(list[0]!=null){
      pintar_todo();
      }
    

  /*
  if(opcion==1){   
      int value = (int)random(-50,50);
        if(value<=0){
       value=0;
      }
        graficando_temperatura(value);
       // delay(1000);
     
   }
   else if(opcion==2){
      int value = (int)random(0,100);
       if(value<=0){
         value=0;
      }
      graficando_Agua(value);
        //delay(1000);

   }
   else if(opcion==3){
    int value = (int)random(200,1000); 
    if(value<=200){
         value=200;
      }
      graficando_Aire(value);
       // delay(1000);
   
   }
   else if(opcion==4){
      int value = (int)random(0,2000);
      if(value <=0 ){
        value =0;
      }else if( value>=2000){
      value =2000;
      }
       graficando_Peso(value);
        //delay(1000);
   
   }
   */ 
   // delay(2000);
}

void pintar_todo(){
  latitud = list[0];
    longitud = list[1];
    fecha = list[2];
    hora = list[3];
    uso =list[8];
    lleno =list[9];
    
if(opcion==1){   
     int value = int(float(list[4]));
      if(value<=0){
       value=0;
      }else if( value>=50){
      value =50;
      }
        graficando_temperatura(value);
        //delay(100);

   }
   else if(opcion==2){
         int value = int(float(list[5]));
        if(value<=0){
         value=0;
      }else if( value>=100){
      value =100;
      }
      graficando_Agua(value);
        //delay(100);

   }
   else if(opcion==3){
        int value = int(float(list[6]));
      if(value<=200){
         value=200;
      }else if( value>=1000){
      value =1000;
      }
      graficando_Aire(value);
       // delay(100);
 
   }
   else if(opcion==4){
     int value = int(float(list[7]));
 
      if(value <=0 ){
        value =0;
      }else if( value>=2000){
      value =2000;
      }
       graficando_Peso(value);
       // delay(100);
   
   }
  



}

   void graficando_temperatura(int value){
   fondo=loadImage("calor.jpg");
   image (fondo, 0,0, 1200,600);
   menu();
   
   fill (255); // relleno Blanco
   rect (400,68,630,-35);//rectángulo
   rect (800,154,181,-20);//rectángulo
     
    textSize(32); 
    fill(200,0,0);
    text(" DASHBOARD SENSOR DE TEMPERATURA", 400, 65);
    textSize(15);
    fill(0);
    text(" Temperatura vs Tiempo", 800, 150);
    
    fill (255); // relleno Blanco
     rect (195,495,300,-25);//rectángulo
     rect (195,525,300,-25);//rectángulo
     rect (900,495,200,-25);//rectángulo
     rect (900,525,200,-25);//rectángulo
     rect (900,584,100,-25);//rectángulo
   

     
     fill(0);
     textSize(20);
     text("longitud :"+longitud , 200, 490);
     text("Latitud: "+latitud, 200, 520);
     text(" Fecha: "+fecha, 900, 490);
     text(" Hora: "+hora, 900, 520);
    
    text(" Uso: "+uso, 900, 580);
    
   
    if(lleno=="true"){
      fill (255);
       rect (100,67,210,-25);//rectángulo
       fill(225,0,0);
       textSize(20);
     text(" ALERTA BOTE LLENO", 100, 65);
    }
   
    meter_temperatura.updateMeter(value);
   
    temp[a]=value;
   
    strokeWeight (5);
     stroke (255);
    line (685,195,685,450);
    
    strokeWeight (5);
     stroke (255);
    line (685,450,985,450);
    
    for(int d=0; d<a;d++){
       fill (200,0,0);
       stroke (0);
        strokeWeight (2);
        rect(690+d*(31), 450, 30, -temp[d]*5);
         //rect(temp[d], 30, 300, 650+d*(31)); temp[d]*5
        
    
    }
    if(a==9){
       int i = 0;
          for (; i < a; i++) {
              temp[i] = temp[i + 1];
          }
          temp[i] = 0;
          a--;
    }
   a++;


}


void graficando_Agua(int value){
  fondo=loadImage("gota_f.jpg");
image (fondo, 0,0, 1200,600);
 menu();
 
     fill (255); // relleno Blanco
     rect (400,70,494,-35);//rectángulo
     rect (800,154,157,-20);//rectángulo
    
    
    fill(0,0,200);
    textSize(15); 
    fill(0);
    text(" Humedad vs Tiempo", 800, 150);

    textSize(32); 
    fill(0,0,200);
    text(" DASHBOARD SENSOR DE AGUA", 400, 65);
    
    fill (255); // relleno Blanco
     rect (195,495,300,-25);//rectángulo
     rect (195,525,300,-25);//rectángulo
     rect (900,495,200,-25);//rectángulo
     rect (900,525,200,-25);//rectángulo
    rect (900,584,100,-25);//rectángulo
    rect (100,67,210,-25);//rectángulo
    
    fill(0);
     textSize(20);
     text("longitud :"+longitud , 200, 490);
     text("Latitud: "+latitud, 200, 520);
     text(" Fecha: "+fecha, 900, 490);
     text(" Hora: "+hora, 900, 520);
    
       text(" Uso: "+uso, 900, 580);
    

    if(lleno=="true"){
      fill (255);
       rect (100,67,210,-25);//rectángulo
       fill(225,0,0);
       textSize(20);
    text(" ALERTA BOTE LLENO", 100, 65);
    }  
     
    if(value >5){
        fill (255); // relleno Blanco
     rect (980,22,83,-20);//rectángulo
      textSize(15); 
    fill(0);
    text(" Bote lleno", 980, 20);
    image(imagen_gota,980,30,150,200);
    }
   
    meter_Agua.updateMeter(value);
   
    
   stroke (0); //sin borde
   fill (0,0,200);
   rect(700, 450, 200, -value*2.6);
    
   line (700,195,700,450);// linea izquierda
   line (900,195,900,450);/// linea derecha
    
   stroke (0); //sin borde
   fill (0,0,200); // relleno azul
   ellipse (800,450,200,-50);//elipse abajo
   
   if(value<95)
   {
     noFill();
     ellipse (800,195,200,-50);//elipse arriba
   
   }else{
     fill(0,0,200);
     ellipse (800,195,200,-50);//elipse arriba
   
   }
 
   
   
  
 

}

void graficando_Aire(int value){
  if(value<400){
   fondo=loadImage("nube.jpeg");
  }else{
   fondo=loadImage("nube_gris.jpg");
  }
 
image (fondo, 0,0, 1200,600);
 menu();
 
     fill (255); // relleno Blanco
     rect (400,70,480,-35);//rectángulo
     rect (800,155,200,-20);//rectángulo
    textSize(32); 
    fill(0,225,225);
    text(" DASHBOARD SENSOR DE AIRE", 400, 65);
  
    textSize(15); 
    fill(0);
    text(" Calidad de Aire vs Tiempo", 800, 150);
    meter_Aire.updateMeter(value);
    
    fill (255); // relleno Blanco
     rect (195,495,300,-25);//rectángulo
     rect (195,525,300,-25);//rectángulo
     rect (900,495,200,-25);//rectángulo
     rect (900,525,200,-25);//rectángulo
    rect (900,584,100,-25);//rectángulo
    
     
    fill(0);
     textSize(20);
     text("longitud :"+longitud , 200, 490);
     text("Latitud: "+latitud, 200, 520);
     text(" Fecha: "+fecha, 900, 490);
     text(" Hora: "+hora, 900, 520);
    
    text(" Uso: "+uso, 900, 580);
    
     


    if(lleno=="true"){
        fill (255); // relleno Blanco
       rect (100,67,210,-25);//rectángulo
       fill(225,0,0);
       textSize(20);
    text(" ALERTA BOTE LLENO", 100, 65);
    }  
     
   
    aire[c]=value;
    stroke(255);
    strokeWeight (5);
    line (685,195,685,450);
    stroke(255);
    strokeWeight (5);
    line (685,450,985,450);
    
    for(int d=0; d<c;d++){
       fill (0,225,225);
        strokeWeight (2);
        stroke (0);
        rect(690+d*(31), 450, 30,-aire[d]/4);
        
        
    
    }
    if(c==9){
       int i = 0;
          for (; i < c; i++) {
              aire[i] = aire[i + 1];
          }
          aire[i] = 0;
          c--;
    }
   c++;


}


void graficando_Peso(int value){
  fondo=loadImage("peso.jpg");
image (fondo, 0,0, 1200,600);
 menu();
 
     fill (255); // relleno Blanco
     rect (400,70,480,-35);//rectángulo
     rect (800,155,120,-20);//rectángulo
     
textSize(32); 
    fill(0);
    text(" DASHBOARD SENSOR DE PESO", 400, 65);
  
  textSize(15); 
    fill(0);
    text(" Peso vs Tiempo", 800, 150);
    
     fill (255); // relleno Blanco
     rect (195,495,300,-25);//rectángulo
     rect (195,525,300,-25);//rectángulo
     rect (900,495,200,-25);//rectángulo
     rect (900,525,200,-25);//rectángulo
    rect (900,584,100,-25);//rectángulo
    
     
     fill(0);
     textSize(20);
     text("Longitud :"+longitud , 200, 490);
     text("Latitud: "+latitud, 200, 520);
     text(" Fecha: "+fecha, 900, 490);
     text(" Hora: "+hora, 900, 520);
    
    text(" Uso: "+uso, 900, 580);
    
    

    if(lleno=="true"){
       fill (255); 
       rect (100,67,210,-25);//rectángulo
       fill(225,0,0);
       textSize(20);
    text(" ALERTA BOTE LLENO", 100, 65);
    }    
    meter_Peso.updateMeter(value);
   
    peso[e]=value;
    stroke(255);
    strokeWeight (5);
    line (685,195,685,450);
    stroke(255);
    strokeWeight (5);
    line (685,450,985,450);
    
    for(int d=0; d<e;d++){
       fill (225,225,0);
        strokeWeight (2);
        stroke (0);
        rect(690+d*(31), 450, 30,-peso[d]/8);
        
        
    
    }
    if(e==9){
       int i = 0;
          for (; i < e; i++) {
              peso[i] = peso[i + 1];
          }
          peso[i] = 0;
          e--;
    }
   e++;


}


void Meter_sensor_Temperatura(){
  meter_temperatura = new Meter(this,75,175);
  meter_temperatura.setTitleFontSize(20);
  //meter_temperatura.setTitleFontName("Arial bold");
  meter_temperatura.setTitle("Temperatura (°C)");
  String [] escala={"0","5","10","15","20","25","30","35","40","45","50"};
  meter_temperatura.setScaleLabels(escala);
  meter_temperatura.setScaleFontSize(18);
 // meter_temperatura.setScaleFontName("Times newr roman bold");
  meter_temperatura.setScaleFontColor(color(255,80,70));
  
  meter_temperatura.setDisplayDigitalMeterValue(true);
  
  // estilo
  meter_temperatura.setArcColor(color (200,0,0));
  meter_temperatura.setArcThickness(15);
  
  meter_temperatura.setMaxScaleValue(50);
  meter_temperatura.setMinInputSignal(0);
  meter_temperatura.setMaxInputSignal(50);
}

void Meter_sensor_Aire(){
  
  meter_Aire = new Meter(this,75,175);
  meter_Aire.setTitleFontSize(20);
  //meter_Aire.setTitleFontName("Arial bold");
  meter_Aire.setTitle("Calidad del Arie (ppm)");
  String [] escala={"0","100","200","300","400","500","600","700","800","900","1000"};
  meter_Aire.setScaleLabels(escala);
  meter_Aire.setScaleFontSize(18);
  //meter_Aire.setScaleFontName("Times newr roman bold");
  meter_Aire.setScaleFontColor(color(200,30,70));
  
  meter_Aire.setDisplayDigitalMeterValue(true);
  
  // estilo
  meter_Aire.setArcColor(color(0,225,225));
  meter_Aire.setArcThickness(15);
  
  meter_Aire.setMaxScaleValue(1000);
  meter_Aire.setMinInputSignal(0);
  meter_Aire.setMaxInputSignal(1000);
}


void Meter_sensor_Agua(){
  
  meter_Agua = new Meter(this,75,175);
  meter_Agua.setTitleFontSize(20);
  //meter_Agua.setTitleFontName("Arial bold");
  meter_Agua.setTitle("Humedad (%)");
  String [] escala={"0","10","20","30","40","50","60","70","80","90","100"};
  meter_Agua.setScaleLabels(escala);
  meter_Agua.setScaleFontSize(18);
 // meter_Agua.setScaleFontName("Times newr roman bold");
  meter_Agua.setScaleFontColor(color(200,30,70));
  
  meter_Agua.setDisplayDigitalMeterValue(true);
  
  // estilo
  meter_Agua.setArcColor(color(0,0,200));
  meter_Agua.setArcThickness(15);
  
  meter_Agua.setMaxScaleValue(100);
  meter_Agua.setMinInputSignal(0);
  meter_Agua.setMaxInputSignal(100);
}


void Meter_sensor_Peso(){
  
  meter_Peso = new Meter(this,75,175);
  meter_Peso.setTitleFontSize(20);
  //meter_Peso.setTitleFontName("Arial bold");
  meter_Peso.setTitle("Peso (g)");
  String [] escala={"0","100","200","300","400","500","600","700","800","900","1000","1100","1200","1300","1400","1500","1600","1700","1800","1900","2000"};
  meter_Peso.setScaleLabels(escala);
  meter_Peso.setScaleFontSize(10);
  //meter_Peso.setScaleFontName("Times newr roman bold");
  meter_Peso.setScaleFontColor(color(200,30,70));
  
  meter_Peso.setDisplayDigitalMeterValue(true);
  
  // estilo
  meter_Peso.setArcColor(color(225,225,0));
  meter_Peso.setArcThickness(15);
  
  meter_Peso.setMaxScaleValue(2000);
  meter_Peso.setMinInputSignal(0);
  meter_Peso.setMaxInputSignal(2000);
  
}


 void mouseClicked() {
   
  if((mouseX>50)&& (mouseX<150)&& (mouseY>530)&&(mouseY< 580 )) //presiono boton rojo
  {
    opcion=1;
 
  }
  else if((mouseX>200)&& (mouseX<300)&& (mouseY>530)&&(mouseY< 580 )) //presiono boton verde
  {
  opcion=2;
  }
   else if((mouseX>350)&& (mouseX<450)&& (mouseY>530)&&(mouseY< 580 )) //presiono boton verde
  {
 opcion=3;
  }
  
  else if((mouseX>500)&& (mouseX<600)&& (mouseY>530)&&(mouseY< 580 )) //presiono boton verde
  {
    opcion=4;
  
  }

}




void menu(){

  
fill (200,0,0); // relleno rojo
rect (50,530,100,50);//rectángulo

fill (0,0,225); // relleno verde
rect (200,530,100,50);//rectángulo

fill (0,225,225); // relleno azul
rect (350,530,100,50);//rectángulo

fill (225,225,0); // relleno amarillo
rect (500,530,100,50);//rectángulo

textSize(15);
fill(0);
text("Temperatura", 55, 560); 

textSize(15);
fill(0);
text("Agua", 230, 560); 
textSize(15);
fill(0);
text("Aire", 380, 560); 
textSize(15);
fill(0);
text("Peso", 530, 560); 



}
