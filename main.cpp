using namespace std;


#include <vector>
#include <allegro.h> 
#include "Drawables.h"
#include "Floor.h"
#include "Box.h"
#include "Character.h"
#include "Background.h"
#include "Interface.h"

int usable_boxes(0);
volatile int frame;                                                             //zmienna licnzikowa

void increment_speed()                                                          // funkcja zwiêkszaj¹ca licznik
{
    frame++;
}
END_OF_FUNCTION( increment_speed );

LOCK_VARIABLE( frame );                                                         //nadanie zmiennej i funkcji sta³ych 
LOCK_FUNCTION( increment_speed );                                               //pozycji w pamiêci


void release(Character* p1, Character* p2)
{
    
    if ( (p1->extra == 1 || p1->extra == 4) && p1->extra == p2->extra )
    {
        BITMAP* txt1 = load_bmp("int/release1.bmp", default_palette);
        BITMAP* txt2 = load_bmp("int/release2.bmp", default_palette);
        {
            int counter(0);
            
            while (counter < 20)
            {
                frame = 0;
                masked_blit( txt1, screen, 0, 0, 308, 350, 663, 80 );
                
                while(frame < 2)    {continue;}
                
                frame = 0;
                masked_blit( txt2, screen, 0, 0, 308, 350, 663, 80 );
                
                while(frame < 2)    {continue;}
                
                counter++;
            }
        }
        
        delete txt1;
        delete txt2;
        
        p1->extra = none;
        p2->extra = none;
        
        frame = 1;
    
    }
}





int main()
{   
    srand(time(NULL));
            
    allegro_init();                                                             //inicjalizacje allegro
    
    install_keyboard();
    
    


    set_color_depth( 32 );

    
    if (set_gfx_mode(GFX_AUTODETECT_FULLSCREEN, 1280, 800, 0, 0) != 0)
    {
        if (set_gfx_mode(GFX_AUTODETECT_WINDOWED, 1280, 800, 0, 0) != 0)
        {
            if (set_gfx_mode(GFX_AUTODETECT, 1280, 800, 0, 0) != 0)
            {
                if (set_gfx_mode(GFX_SAFE, 1280, 800, 0, 0) != 0)
                {
                    allegro_exit();
                }   
            }
        }
    }
    set_palette( default_palette );
    
    install_timer();                                                            //instalacja licznika
    install_int_ex( increment_speed, BPS_TO_TIMER( 60 ) );                      //funkcja increment_speed bêdzie wywo³ywana 60 razy na sekundê
    
    
    
    
    
    vector<Floor>* vector_floors = new vector<Floor>;                           //wektor obiektów typu floor (pod³oga)
    for (int z(7); z < 13; z++)      vector_floors->push_back(Floor(54*z,170)); //dodawanie pod³óg
    for (int z(3); z < 9; z++)       vector_floors->push_back(Floor(54*z,350)); // (przerobiæ na czytanie z pliku)
    for (int z(14); z < 21; z++)     vector_floors->push_back(Floor(54*z,350));
    for (int z(7); z < 16; z++)      vector_floors->push_back(Floor(54*z,520));
    for (int z(3); z < 9; z++)       vector_floors->push_back(Floor(54*z,700));
    for (int z(11); z < 19; z++)     vector_floors->push_back(Floor(54*z,700));
    
    vector<Box>* vector_boxes = new vector<Box>;                                //wektor obiektów typu box (pud³o)
    
    Background bck;                                                             // obiekt t³o
    
    Character postac1(1);                                                       //dodanie postaci
    Character postac2(0);
    
    Interface intfc(&postac1, &postac2);
    
    int randBox;                                                                //zmienna odpowiedzialna za pojawianie siê boxów
    
    BITMAP* bufor = create_bitmap( 1280, 800 );                                 //tworzenie bufora obrazu
    
    bool quit(false);                                                           // CZY ZAKOÑCZYÆ?
    
    int temp_timer(0);
    
// G£ÓWNA PÊTLA PROGRAMU    
    
    while(!quit)
    {   
        temp_timer++;
        
        if (key[KEY_ESC])       { quit = true; }
        if(temp_timer % 5 == 0)
        {
            if (key[KEY_PGUP] && intfc.freq > 50)      { intfc.freq -= 50; intfc.how_many_boxes++; }
            if (key[KEY_PGDN] && intfc.freq < 1500)      { intfc.freq += 50; intfc.how_many_boxes--; }
        }
        
        frame = 0;                                                              //zerwanie licznika
    
    
        randBox = rand()%intfc.freq;                                            //szansa 1:freq na pojawienie siê boxa
        if (randBox == 0)   { vector_boxes->push_back( Box(vector_floors) ); usable_boxes++;}
        
        
        clear_to_color( bufor, makecol( 0, 0, 0 ) );                            //czyszczenie bufora
        
        
        bck.draw(bufor);                                                        //rysowanie t³a
        
        
        for(int x(0); x<vector_floors->size(); x++)
        {
            (*vector_floors)[x].draw(bufor);
        }
        
        while ( vector_boxes->size() > 0 
        &&    (*vector_boxes)[vector_boxes->size() - 1].ready_to_die )
        {
            vector_boxes->pop_back();
        }
        
        for(int x(0); x<vector_boxes->size(); x++)
        {
            (*vector_boxes)[x].check_state(vector_floors, &usable_boxes);
            (*vector_boxes)[x].draw(bufor);
        }
        
        
        
		postac1.set_speed(vector_floors, vector_boxes, bufor, &postac2);
		postac1.move();
        postac1.changeState();
        postac1.draw(bufor);
        
        
        postac2.set_speed(vector_floors, vector_boxes, bufor, &postac1);
		postac2.move();
        postac2.changeState();
        postac2.draw(bufor);
        
        intfc.draw(bufor);
        
        
        textout_ex(bufor, font, postac2.score, 20, 20, makecol(255, 0, 0), -1);
        textout_ex(bufor, font, postac1.score, 1260, 20, makecol(0, 50, 255), -1);

        blit( bufor, screen, 0,0,    0,0,    1280, 800 );
        
        release (&postac1, &postac2);
        
        
        
        while( frame < 1 ) {continue;}
    }
    
 
 
    allegro_exit();
    
    delete vector_floors;
    delete vector_boxes;
    delete bufor;
    
    return 0;
}
END_OF_MAIN();

