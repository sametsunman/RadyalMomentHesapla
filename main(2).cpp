#include<iostream>
#include<math.h>
#include <sstream>
#include <string>
using namespace std;


class Direk
{
public:
  double r = 850; //Kurp yaricapi
  double h_batma = 1.60; //Temel icindeki batma
  double e = 65; //Temel ustu ray arasi mesafe
  double i = 3.25; //Emplantasyon
  double sty = 5.75; //Seyir teli yuksekligi
  double sy = 1.40; //Sistem yuksekligi
  double h_hoban_ustu = 2.60; //Hoban seviyesinden diregin uc kismina olan mesafe
  double h_hoban_fider = 2.15; //Hoban seviyesi fider teli arasi mesafe
  double lf = 1.40; //Fider traversi boyu
  double f; //cekiye yada basiya calisan direk
  double h; //Diregin temel ustunde kalan kismi
  double db; //Diregin boyu
  double a = 45; //Aksi belirtilmedigi icin iki taraftaki acikliklar esit
  double d = 0.32; //B3 ve B4 Beton direk capi olarak ortalama deger
  double dz = 0.28; //Fider izolatori capi olarak ortalama deger
  double hz = 0.70; //Fider izolatori boyu olarak ortalama deger
};

double DirekBoyuHesapla (double h_batma, double e, double sty, double sy,
                                               double h_hoban_ustu);
double DirekMomentHesapla (Direk direk, string direkCalismaTuru,
                                                  string fiderAsilmaYonu,
                                                  string ruzgarRadyalGerilme);



int
main ()
{
  Direk direk;
    string direkCalismaTuru;
  string fiderAsilmaYonu;
  string ruzgarRadyalGerilme;
  string input;

  cout << "Bu program direk momentumunu hesaplar" 
    << endl;
  cout << "Lutfen sizden istenilen bilgileri giriniz" 
    << endl;
  cout <<"Alanlari varsayilan degerleri kullanmak icin enter tusuna basabilirsiniz."
    << endl << endl;

  cout << "Kurp yaricapi(m):  ";
    
    getline( cin, input );
    if ( !input.empty()) {
        istringstream stream( input );
        stream >> direk.r;
    }
    
  cout << "Temel icindeki batma(m):  ";
  
      getline( cin, input );
    if ( !input.empty()) {
        istringstream stream( input );
        stream >> direk.h_batma;
    }
    

  cout << "Temel ustu ray arasi mesafe(cm):  ";
  
      getline( cin, input );
    if ( !input.empty()) {
        istringstream stream( input );
        stream >> direk.e;
    }

  cout << "Emplantasyon(m):  ";
  
      getline( cin, input );
    if ( !input.empty()) {
        istringstream stream( input );
        stream >> direk.i;
    }

  cout << "Seyir teli yuksekligi(m):  ";
  
      getline( cin, input );
    if ( !input.empty()) {
        istringstream stream( input );
        stream >> direk.sty;
    }

  cout << "Sistem yuksekligi(m):  ";
  
      getline( cin, input );
    if ( !input.empty()) {
        istringstream stream( input );
        stream >> direk.sy;
    }

  cout << "Hoban seviyesinden diregin uc kismina olan mesafe(m):  ";
  
      getline( cin, input );
    if ( !input.empty()) {
        istringstream stream( input );
        stream >> direk.h_hoban_ustu;
    }

  cout << "Hoban seviyesi fider teli arasi mesafe(m):  ";
  
      getline( cin, input );
    if ( !input.empty()) {
        istringstream stream( input );
        stream >> direk.h_hoban_fider;
    }

  cout << "Fider traversi boyu(m):  ";
  
      getline( cin, input );
    if ( !input.empty()) {
        istringstream stream( input );
        stream >> direk.lf;
    }

  cout << "Direk calisma turu(ceki,basi):  ";
  cin >> direkCalismaTuru;
  if(direkCalismaTuru=="basi")
  {
  	direk.f=20;
  }
  else
  {
    direk.f=24;
  }
  cout << "Fider asilma yonu(hat,aksi):  ";
  cin >> fiderAsilmaYonu;
  cout << "Ruzgar etkisi ve radyal gerilme yonu(ayni,ters):  ";
  cin >> ruzgarRadyalGerilme;
    cout << endl;
  direk.db =
    DirekBoyuHesapla (direk.h_batma, direk.e, direk.sty, direk.sy,
                                     direk.h_hoban_ustu);
direk.h=direk.db-direk.h_batma;

  cout << "Verilen Uzunluklara Gore Direk boyu = " << direk.db << endl;
  cout << endl;
  cout << "Katener diregine etki eden toplam moment = " <<
    DirekMomentHesapla (direk, direkCalismaTuru, fiderAsilmaYonu,
                                               ruzgarRadyalGerilme) << endl;


  cin.get ();
  cin.get ();
  return 0;
}

double
DirekBoyuHesapla (double h_batma, double e, double sty, double sy,
                                 double h_hoban_ustu)
{
  return h_batma + (e/100) + sty + sy + h_hoban_ustu;
}

double
DirekMomentHesapla (Direk direk, string direkCalismaTuru,
                                   string fiderAsilmaYonu, string ruzgarRadyalGerilme)
{
    
    //Tellerin ankastraman noktasindan yukseklikleri
    double hs = direk.sty+(direk.e/100); //Seyir teli yuksekligi
    double hp = hs+direk.sy; //Portor teli yuksekligi
    double ht = (direk.e/100)+direk.sty+direk.sy-0.25; //Toprak teli-GDI yuksekligi
    double hf = hp+direk.h_hoban_fider; //Fider teli yuksekligi)
    double hpn = hs+(direk.sy/2); //Pandul teli ortalama yuksekligi
    
    double trf = (direk.a*1500)/direk.r; //Fider iletkenindeki radyal gerilme
    double trt = (direk.a*1100)/direk.r; //Geri Donus iletkenindeki radyal gerilme
    double trp = (direk.a*1200)/direk.r; //Portordeki radyal gerilme
    double trs = (direk.a*1200)/direk.r; //Seyir telindeki radyal gerilme
    
    //Teller uzerindeki radyal gerilmelerden dolayi olusan moment
    double mr = (hf*trf)+(ht*trt)+(hp*trp)+(hs*trs);
    
    //Iletkenler uzerindeki, metre basina ruzgar yukleri
    double wf = 0.9592; 
    double wt = 0.7700;
    double wp = 0.5544;
    double ws = 0.6460;
    double wpn = 0.3170;
    
    double tfw = wf*direk.a; //fider iletkeni
    double ttw = wt*direk.a; //geri donus iletkeni
    double tpw = wp*direk.a; //portor
    double tsw = ws*direk.a; //seyir teli
    double tpnw = wpn*0.25*direk.a; //pandul
    
    double wd = 23.1*direk.d*direk.h; //Direge gelen ruzgar yuku
    double wfk = 23.1*direk.dz*direk.hz; //(Fider izolatorune gelen ruzgar yuku
    
    //Teller, direk ve izolator uzerinde olusan ruzgar momenti
    double mw = (tfw*hf)+(ttw*ht)+(tpw*hp)+(tsw*hs)+(tpnw*hpn)+(wd*(direk.h/2))+(wfk*(hf+(direk.hz/2)));
    
    //Direk uzerinde yer alan tellerin metre basina agirliklari
    double qf = 0.9750; //LA280 Fider iletkeni
    double qp = 0.5770; //65 mm2 tasiyici
    double qs = 0.9500; //107 mm2 seyir teli
    double qpn = 0.1030; //Pandul
    double qt = 0.6760; //LA180 Geri donig iletkeni
    double qk = 1.553;
    double qbt = 0.053+0.047+0.036+0.040+0.007;
    
    int gfit = 22; //fider traversi ve izolatorinin toplam agirligi
    double gtb = 1.6; //toprak teli bağlantı parcasinin agirligi
    int gd = 60; //Konsol Hoban donatisinin agirligi
    
    double gk = qk*direk.a; //Katener telleri
    double gf = qf*direk.a+22; //Fider ve parcalari
    double gt = qt*direk.a+gtb; //GDI ve parcalari
    double gb = qbt*direk.a+120; //Buz yuku
    
    //Dusey yuklerden dolayi olusan momenti hesaplayalim
    double mp;
    if(fiderAsilmaYonu=="aksi" && direkCalismaTuru=="ceki")
    {
        mp = (gk*(direk.i+(direk.f/100))) + (gd*(direk.i/2)) - (gf*direk.lf) + (gt*direk.d) + (gb*direk.i);
    }
    else if(fiderAsilmaYonu=="aksi"  && direkCalismaTuru=="basi")
    {
          mp = (gk*(direk.i-(direk.f/100))) + (gd*(direk.i/2)) - (gf*direk.lf) + (gt*direk.d) + (gb*direk.i);
    }
    else if(fiderAsilmaYonu=="hat"  && direkCalismaTuru=="basi")
    {
          mp = (gk*(direk.i-(direk.f/100))) + (gd*(direk.i/2)) + (gf*direk.lf) + (gt*direk.d) + (gb*direk.i);
    }
    else
    {
          mp = (gk*(direk.i-(direk.f/100))) + (gd*(direk.i/2)) + (gf*direk.lf) + (gt*direk.d) + (gb*direk.i);
    }
    
    //Katener diregine etki eden toplam moment hesabi
    double mt;
    if(ruzgarRadyalGerilme=="ters")
    {
       mt = ((mr+mp)*1.5)-(mw*1.3);
    }
    else
    {
       mt = ((mr+mp)*1.5)+(mw*1.3);
    }
    
    
  return mt;
}


