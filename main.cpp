#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <time.h>
#include <cstdio>
#include <math.h>

using namespace std;

string grid[8][9]= {
{"G","  ","  ","| ","| ","| ","|","  ",""},
{"F","  ","  ","| ","| ","| ","|","  ",""},
{"E","| ","| ","| ","| ","| " ,"| ","| ","|"},
{"D","| ","| ","| ","|o","| " ,"| ","| ","|"},
{"C","|x","|x","|x","|x","|x" ,"|x","|x","|"},
{"B","  ","  ","|x","|x","|x","|"  ,"  "  ,""},
{"A","  ","  ","|x","|x","|x","|"  ,"  "  ,""},
{" "," 0"," 1"," 2"," 3"," 4" ," 5 ","6 ",""}
};

//PODPOGRAMY---------------
bool rysuj(bool &on_off, string &wygra){
    int ix = 0;
    for(int i = 0 ; i < 8; i++){ //Rysuje plansze
        for(int j=0 ; j < 9; j++){
            cout<< grid[i][j];
            if(grid[i][j] == "|x"){
                ix++;
            }
        }
            cout<< endl;
        }
        if(ix < 5){
          wygra = "PC";
          on_off = false;
          return on_off;//Sprawdza ile X jest na planszy

        }
     }
int tlumacz(char y){ // TLumaczenie Liter na cyfry
    switch(y){
     case 'A':
     case 'a':
        return 6;
        break;
     case 'B':
     case 'b':
        return 5;
        break;
    case 'C':
    case 'c':
        return 4;
        break;
    case 'D':
    case 'd':
        return 3;
        break;
    case 'E':
    case 'e':
        return 2;
        break;
    case 'F':
    case 'f':
        return 1;
        break;
    case 'G':
    case 'g':
        return 0;
        break;
    }
};

int sprawdz_ruch(int &gy,int &gx,int &tgx, int &tgy){ // Sprawdza czy mozna przeniesc x na dane pole
      char y;
      gx;
      cout << "Nie mozesz tu przemiescic piona\n podaj nowe wspolrzedne: "<<endl;
      cin >> y >> gx;
      gy = tlumacz(y);
      if((grid[gy][gx+1] == "|x" || grid[gy][gx+1] == "|o" ||  grid[gy][gx+1] == "  "|| grid[gy][gx+1] == "|" ) || ((fabs(tgy - gy) == 1 && fabs((tgx+1)-(gx+1)) == 1)||(fabs(tgy - gy) > 1 || fabs((tgx+1)-(gx+1)) > 1)))
      {
        sprawdz_ruch(gy,gx,tgx,tgy);
      }
      return gy,gx;
}
int wybierz_x(int &tgy,int &tgx){ // Sprawdza czy pion ktory wybrales ma mozliwosc ruchu
    char ty;
    //int tgx;
        cout << "Ten Pion nie moze sie ruszac lub wybrales pole bez piona\n Ktorym pionem chcesz sie poruszyc?"<< endl;
        cin >> ty >> tgx;
        tgy = tlumacz(ty);
     if((grid[tgy][tgx+1] == "| " || grid[tgy][tgx+1] == "  "|| grid[tgy][tgx+1] == "|o" || grid[tgy][tgx+1] == "|") ||
       ((grid[tgy][tgx+2] == "|x" || grid[tgy][tgx+2] == "|") && (grid[tgy][tgx] == "|x" || grid[tgy][tgx] == "  ") && grid[tgy-1][tgx+1] == "|x" && (grid[tgy+1][tgx+1] == "|x" || grid[tgy+1][tgx+1] != "|x")))
      {
        //PRAWO                                                     LEWO                                               GORA                            DOL
     wybierz_x(tgy,tgx);
    }
    return tgy,tgx;

}
int ruszaj_o(int &posy,int &posx,int &ruch,bool &on_off,string &wygra){// Poruszanie sie O
switch(rand() % 4){ // Wybiera losowo kierunek ruchu O
//Z Prawej
case 0:
 if(grid[posy][posx+1] == "| " || grid[posy][posx+1] == "| |"|| grid[posy][posx+1] == " |"){
   grid[posy][posx+1] = "|o";
   grid[posy][posx] = "| ";
   return posx = posx +1;}
else if(grid[posy][posx+1] == "|x" && grid[posy][posx+2] == "| "){
   grid[posy][posx+1] = "|o";
   grid[posy][posx] = "| ";
   grid[posy][posx+2] = "|o";
   grid[posy][posx+1] = "| ";
   return posx = posx + 2;

    }
    else {
     if(ruch == 10){ //Jezeli o nie mozez sie ruszac przegrywa
       wygra = "Gracz";
       on_off = false;
       return on_off;
     }
     ruch++; // Dodaje 1 do ruchu jesli nie moze sie ruszyc
     ruszaj_o(posy,posx,ruch,on_off,wygra);

   }
     break;
//Lewej
case 1:
    if(ruch == 10){
       wygra = "Gracz";
       on_off = false;
       return on_off;
    }
else if(grid[posy][posx-1] == "| "|| grid[posy][posx-1] == "| |"|| grid[posy][posx-1] == " |"){
   grid[posy][posx-1] = "|o";
   grid[posy][posx] = "| ";
   return posx = posx -1;}
else if(grid[posy][posx-1] == "|x" && grid[posy][posx-2] == "| "){
   grid[posy][posx-1] = "|o";
   grid[posy][posx] = "| ";
   grid[posy][posx-2] = "|o";
   grid[posy][posx-1] = "| ";
   return posx = posx -2;
    }
    else {
     if(ruch == 10){
       wygra = "Gracz";
       on_off = false;
       return on_off;
     }
     ruch++;
     ruszaj_o(posy,posx,ruch,on_off,wygra);

   }
   break;
//Gora
case 2:
if(grid[posy-1][posx] == "| "|| grid[posy-1][posx] == "| |"|| grid[posy-1][posx] == " |"){
   grid[posy-1][posx] = "|o";
   grid[posy][posx] = "| ";
   return posy = posy - 1;}
else if(grid[posy-1][posx] == "|x" && grid[posy-2][posx] == "| "){
   grid[posy-1][posx] = "|o";
   grid[posy][posx] = "| ";
   grid[posy-2][posx] = "|o";
   grid[posy-1][posx] = "| ";
   return posy = posy - 2;
    }
    else {
     if(ruch == 10){
       wygra = "Gracz";
       on_off = false;
       return on_off;
     }
     ruch++;
     ruszaj_o(posy,posx,ruch,on_off,wygra);

   }

   break;
    //Dol
case 3:
if(grid[posy+1][posx] == "| " || grid[posy+1][posx] == "| |"|| grid[posy+1][posx] == " |"){
   grid[posy+1][posx] = "|o";
   grid[posy][posx] = "| ";
   return posy = posy + 1;}
else if(grid[posy+1][posx] == "|x" && grid[posy+2][posx] == "| "){
   grid[posy+1][posx] = "|o";
   grid[posy][posx] = "| ";
   grid[posy+2][posx] = "|o";
   grid[posy+1][posx] = "| ";
   return posy = posy + 2;
    }
    else {
     if(ruch == 10){
       wygra = "Gracz";
       on_off = false;
       return on_off;

     }
     ruch++;
     ruszaj_o(posy,posx,ruch,on_off,wygra);
    }
   break;
    }

}
void ruszaj_x(){// Funkcja ktora porusza X
    char ty,y;
    int tgx,tgy,gy,gx;
            cout << "Ktorym pionem chcesz sie poruszyc?" << endl;
            cin >> ty >> tgx;
            tgy = tlumacz(ty); //tłumaczenie litery
    if((grid[tgy][tgx+1] == "| " || grid[tgy][tgx+1] == "  " ||grid[tgy][tgx+1] == "|o" || grid[tgy][tgx+1] == "|" )||
      ((grid[tgy][tgx+2] == "|x" || grid[tgy][tgx+2] == "|") && (grid[tgy][tgx] == "|x" || grid[tgy][tgx] == "  ") && grid[tgy-1][tgx+1] == "|x" && (grid[tgy+1][tgx+1] == "|x" || grid[tgy+1][tgx+1] != "|x")))
      {
        wybierz_x(tgy,tgx); //Jesli blad to Funkcja z gory
      }
            cout << "Gdzie chcesz przemiescic wybranego piona" << endl;
            cin >> y >> gx;
            gy = tlumacz(y);
    if((grid[gy][gx+1] == "|x" || grid[gy][gx+1] == "|o" ||  grid[gy][gx+1] == "  "|| grid[gy][gx+1] == "|" ) || ((fabs(tgy - gy) == 1 && fabs((tgx+1)-(gx+1)) == 1)||(fabs(tgy - gy) > 1 || fabs((tgx+1)-(gx+1)) > 1)))
        {
            sprawdz_ruch(gy,gx,tgx,tgy);
        }
     grid[tgy][tgx+1] = "| ";
     grid[gy][gx+1] = "|x";

    }
//PODPOGRAMY-----------------
int main()
{
    cout <<"Witaj w Grze napisanej przez:\n Daniel Bukowski \nProsze podawac wsporzedne od A-G \n Enter by przejsc dalej..."<<endl;
    int posx = 4;
    int posy = 3;
    bool on_off = true;
    int zmiana = 0;
    int ruch = 0;
    string wygra;
    getchar();
    rysuj(on_off,wygra);

    while(on_off == true){
            ruch = 0;
            cout<<zmiana;
            system("cls");
  //cout<<"ADFSFDS\n";
        if((zmiana %2) == 0|| zmiana == 0){
            cout << "Komputer []  -  Gracz [#]" <<endl;
            rysuj(on_off,wygra);
            ruszaj_x();
        }
        else{
            cout << "Komputer [#]  -  Gracz []" <<endl;
            ruszaj_o(posy,posx,ruch,on_off,wygra);
            rysuj(on_off,wygra);
            cout<<"Komputer rusza...\n";
            Sleep(1000);
        }
        zmiana++;
    }
    if(wygra== "PC"){
            cout<< "PRZEGRALES \n KONIEC GRY";}
        else if(wygra == "Gracz"){
            cout<<"Koniec Gry\n Wygrywasz";
    }
    return 0;
}
