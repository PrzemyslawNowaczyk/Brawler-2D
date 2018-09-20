class Box: public Drawables
{
public:
    bool falling;
    int dest;
    long long int hp;
    char stan;
    bool locked;
    int inside;
    bool empty;
    int how_long;
    bool ready_to_die;
    
    static int usables;
          
public:        
    Box(vector<Floor>* floors)
    {
        x = rand() % 1200;
        ready_to_die = false;
        how_long = 0;
        locked = true;
        hp = 100;
        stan = 0;
        y = -200;
        hgth = 40;
        wdth = 40;
        lewo = x;
        prawo = x+wdth;
        gora = y;
        dol = y+hgth;
        falling = true;
        img = load_bmp("boxes/box.bmp", default_palette);
        
        while(!checkFloor(floors))
        {
            x = rand() % 1280;
            lewo = x;
            prawo = x+wdth;
        }
        
        inside = (rand() % 7) + 1;
        empty = false;

    }
    
    
    
    void check_state(vector<Floor>* floors, int* boxes)
    {
        if (falling)
        {
            if (dol > dest)
            {
                falling = false;
                y = dest-hgth;
                gora = y;
                dol = y+hgth;
            }
            
            else
            {
                y += 4;
                dol = y+hgth;
                gora = y;
                dol = y+hgth;
            }
        }

        if (locked)
        {
            if (hp < 100 && hp >= 50)       { stan = 40; }
            if (hp < 50 && hp > 0)          { stan = 80; }
            if (hp <= 0)                    { stan = 120; locked = false; }
        }
        
        else
        {
            if (hp < 0)     { hp = 0; }
            how_long++;
            if (how_long == 500)   {ready_to_die = true; boxes--;}
        }
        
    }
    
    
    
    
    bool checkFloor (vector<Floor>* floors)
    {
        int tick(0);
        while (tick != 50)
        {   
            tick++;
            int a = rand() % floors->size();
            if (prawo >= (*floors)[a].lewo && prawo <= (*floors)[a].prawo
            ||  lewo >= (*floors)[a].lewo && lewo <= (*floors)[a].prawo
            ||  lewo >= (*floors)[a].lewo && prawo <= (*floors)[a].prawo )
            {
                    dest = (*floors)[a].gora;
                    return true;
            }
        }
        return false;
    }
    
    
    void draw(BITMAP* bufor)
    {
        if (!ready_to_die) masked_blit( img, bufor, stan,0, x,y, wdth, hgth);
    }   
            
};
