#include <winbgim.h> 
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <math.h>
#include <time.h>


typedef struct {
	double x;
	double y;
}Nokta;

struct Cember { 
    Nokta C; 
    double R; 
}; 

void noktaCiz(Nokta mesafe ,int ortala){
	putpixel(mesafe.x+ortala,mesafe.y+ortala,3);

}

void bsplaine(double t, const Nokta points[],int noktaSayisi,int mesafe)
{
	int i=0;
    Nokta points2[noktaSayisi-1];
    
    if(noktaSayisi==1){
    	
    	noktaCiz(points[0],mesafe); // �izdirme k�sm� 
    
	}
	else{
	//	noktaCiz(points[0],mesafe);
		noktaSayisi=noktaSayisi-1;
		for(i=0;i<noktaSayisi;i++){
    		points2[i]=points[i];	// 1 eksi�i sayida noktayi points 2 ye atama kismi	
		}
    	for ( i = 0; i < noktaSayisi ; i++){
    		
    		points2[i].x = (points[i+1].x)*t + (points[i].x)*(1.0-t);  //a��rl�k ortalamas�n� bulma
    		points2[i].y =(points[i+1].y)*t+ (points[i].y)*(1.0-t);
    	}
    	
   		bsplaine(t, points2, noktaSayisi,mesafe); // recursive
	}	    
}   

double uzaklikFarki(Nokta ilkNokta,Nokta ikinciNokta)  // �klid mesafesini d�nd�r�yoruz 
{ 
    return sqrt(pow(ilkNokta.x - ikinciNokta.x, 2) + pow(ilkNokta.y - ikinciNokta.y, 2)); 
}

Nokta ikiNoktaCember(Nokta ilkNokta, Nokta ikinciNokta ) { 	//2 noktayla kesi�en en k���k daireyi d�nd�rme i�levi , merkezi A ve B'nin orta noktas� olacak �ekilde ayarlay�yorum

	Nokta C;
 
    C.x= (ilkNokta.x + ikinciNokta.x)/2.0; 
    
    C.y=(ilkNokta.y + ikinciNokta.y)/2.0;

    return C; 
} 


bool min_cember(Cember c, Nokta P[],int NoktaSayisi) {   
    int i=0;
    bool icinde=1;
	double uzaklik;
	
    for (i=0;i<NoktaSayisi;i++){
    	
    	uzaklik=uzaklikFarki(c.C, P[i]);
    	
    	if (uzaklik > c.R){
        	icinde=0; 
		} 
	}
	
    return icinde; 
} 


double cemberMerkeziX(double koordBx, double koordBy,double koordCx, double koordCy){  
    
	//3 nokta ile tan�mlanan bir �emberi elde etmek i�in yard�mc� y�ntem
	//nokta daire merkezini al yani 3 nokta verildiginde cember merkezini bulmaya yard�mc� y�ntem
	
	double koordKare_B,koordKare_C,koord_Mix;
	
	koordKare_C = koordCx * koordCx + koordCy * koordCy; 
	
	koord_Mix = koordBx * koordCy - koordBy * koordCx; 
	
    koordKare_B = koordBx * koordBx + koordBy * koordBy; 
    
   
    
    return ((koordCy * koordKare_B - koordBy * koordKare_C) / (2 * koord_Mix)); 
} 
double cemberMerkeziY(double koordBx, double koordBy,double koordCx, double koordCy){ 

    double koordKare_B,koordKare_C,koord_Mix;
	
	koordKare_C = koordCx * koordCx + koordCy * koordCy; 
	
	koord_Mix = koordBx * koordCy - koordBy * koordCx; 
	
    koordKare_B = koordBx * koordBx + koordBy * koordBy; 
    
    return ((koordBx * koordKare_C - koordCx * koordKare_B) / (2 * koord_Mix)) ; 
} 
  
  
Nokta ucNoktaCember(Nokta A,Nokta B,Nokta C)  
{ 
    Nokta merkez;
    
	merkez.x = cemberMerkeziX(B.x - A.x, B.y - A.y,C.x - A.x, C.y - A.y);
	 
	merkez.y=cemberMerkeziY(B.x - A.x, B.y - A.y,C.x - A.x, C.y - A.y);
	
    merkez.x += A.x; 
    merkez.y += A.y;
    
    return  merkez ; 
}

  

int main(){
	
	int i,j,noktaSayisi,index=0,randx=0,randy=0;

	double temp1=0,mesafe=400;
	
	int aralik=30; // rastgele sayi alirken degerlerin negatif- poztifif / -30/+30 gibi ayarlanmas�
	
	printf("Girilecek koordinat nokta sayisini giriniz:");
	scanf("%d",&noktaSayisi);
	
	Nokta points[noktaSayisi];
	srand(time(0)); //rastgele say� �recitisini baslat�r 
	
	
	FILE *fp =fopen("program.txt", "w+");
	// dosyaya random say�lar yazd�rmak ad�na
   /* 	for(i=0;i<noktaSayisi;i++){
		
		randx=i*10;
		randy=rand()%(aralik*2)-aralik;  // rand()%60-30 [0,60] idi [0-30,60-30] = -30,30 aral�g�nda y de�erleri
		
        fprintf(fp, " %d %d ", randx,randy);    
	}
	fclose(fp); */
	
	// proje dokuman� orneg�ni gerceklestirmek icin = 0 0,0 1,1 0 koordinatlar�n� denemek i�in
	
	for(i=0;i<noktaSayisi;i++){
		printf("X ve Y koordinatlarini giriniz: ");
		scanf("%d %d",&randx,&randy);

        fprintf(fp, " %d %d ",randx,randy);    
	}
	fclose(fp); 
	

	
	fopen("program.txt", "r");
	
	initwindow( mesafe*3 , mesafe*2 );
	//setcolor(COLOR(170,170,255));

	float ciz_cember;
	
	for(i=0;i<noktaSayisi;i++){  //noktalar�m� al�p nokta koordinatlar�n� �izdirece�im

        fscanf(fp, "%lf", &points[i].x); //x ve y koordinatlar�n� dosyadan okuyorum
        fscanf(fp, "%lf", &points[i].y);
        
    	
		
	    circle(mesafe+(int)(points[i].x),mesafe+(int)(points[i].y),3);

	    // bu fonksiyonu kullanarak x ve y koordinatlar�n� girip yar�cap� 3 cm olan k�c�k pixel �eklinde �emberler olusturmaya cal�st�m , 
	 
		setcolor(COLOR(255,255,0)); // pixellerin rengi
		
		for(ciz_cember=2;ciz_cember>0;ciz_cember-=0.01){ // noktalar�n daire hallerinin i�ini doldurmak �c�n i� i�e daireler olusturdum
			
			circle(mesafe+int(points[i].x),mesafe+int(points[i].y),ciz_cember);
		}  
	} 
	

    setcolor(COLOR(170,170,255));
	fclose(fp);
	

	
	line(mesafe/2, mesafe, mesafe*3/2,mesafe); // X koordinat d�zlemi  150-300-450-300  x1,y1,x2,y2
	line(mesafe, mesafe/2, mesafe,mesafe*3/2); // Y koordinat d�zlemi	300-150-300-450
	
	
	
	Cember Middle,tmp;  //middle cember merkezini tutacag�m�z struct 
	Middle.R=mesafe*100; //burada middle adl� struct�ndan olusturdugum cemberin yar��ap�n� olabildigince b�y�k ayarl�yorum r=4000  
	//ilk min enc circle � sonsuzluk yar�cap�na sahip olacak sekilde ayarlad�m 
	Middle.C.x=mesafe;   //merkez 400,400
	Middle.C.y=mesafe;
	
	tmp.C.x=0;  //gecici olarak olusturdugum cemberin merkezi 0,0 ve r si 0 simdilik
	tmp.C.y=0;
	tmp.R=0;

	// 2 nokta ile kesi�en cember
	for ( i = 0; i < noktaSayisi; i++) {   //t�m noktalar� g�zden ge�iriyorum 
        for (j = i + 1; j < noktaSayisi; j++) { 
  
 
            tmp.C = ikiNoktaCember(points[i], points[j]);  // p[i] ve p[j] ile kesi�en en k�c�k daireyi al�yorum 
  			tmp.R = uzaklikFarki(points[i], points[j])/2.0 ;
  			//printf("x: %lf y: %lf R:%lf \n ",tmp.C.x,tmp.C.y,tmp.R);

            if (tmp.R <= Middle.R && min_cember(tmp, points,noktaSayisi)){  
			//tmp t�m noktalar� kaps�yorsa ve daha k�c�k bir yar�capa sahipse mec i g�ncelliyorum
            	Middle = tmp; 
            	index=j; 
            
			}        
        } 
    }

	printf("\n----------------------------------------------- \n");
	
	// her 3 noktan�n birbiriyle kombinasyonu 
	// 3 nokta ile kesisen �ember
	for ( i = 0; i < noktaSayisi; i++) { 
        for ( j = i + 1; j < noktaSayisi; j++) { 
            for (int k = j + 1; k < noktaSayisi; k++) { 
                
				tmp.C = ucNoktaCember(points[i], points[j], points[k]); 
  				tmp.R=uzaklikFarki(tmp.C, points[i]);
  				//printf("x: %lf y: %lf R:%lf \n ",tmp.C.x,tmp.C.y,tmp.R);

                if (tmp.R <= Middle.R && min_cember(tmp, points,noktaSayisi)){
                	Middle = tmp; 
                	index=j;
				} 
                    
            } 
        } 
    } 


	printf("Middle Point X = %lf , Middle Point Y = %lf",Middle.C.x,Middle.C.y);
	printf("\n");
	printf("Cemberin Yaricapi : %.2lf " , Middle.R);


	circle(Middle.C.x+mesafe,Middle.C.y+mesafe,Middle.R); 
	
	setcolor(COLOR(250,200,10));
	
	line(Middle.C.x+mesafe, Middle.C.y + mesafe,mesafe+points[index].x, mesafe+points[index].y); 

	setcolor(COLOR(250,0,200)); 
	
	putpixel(Middle.C.x+mesafe,-Middle.C.y+mesafe,10); // merkez noktan�n pixeli
	
	for(ciz_cember=3;ciz_cember>0;ciz_cember-=0.01){  //merkez noktan�n i�ini doldurmak �c�n 
			
		circle(Middle.C.x+mesafe,Middle.C.y+mesafe,ciz_cember);
	}
	
	setcolor(COLOR(0,0,200));
	
	double iter;
	
  	for ( iter = 0; iter < 101.0; iter++){
		bsplaine(iter / 100.0, points,noktaSayisi,mesafe);
	} 
	

	while( !kbhit() ); //ekran� tutuyor 
	closegraph();  
	getch();
	return( 0 );

}
