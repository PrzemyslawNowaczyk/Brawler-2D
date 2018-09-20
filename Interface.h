class Interface
{
public:
    
    struct Pow_txt
    {
        BITMAP* img;
        int x,y,w,h;
        int lewo,prawo;
    };
    
    Character* hero1;
    Character* hero2;
    Pow_txt hero1_txt[8];
    Pow_txt hero2_txt[8];
    char i;
    
    int freq;
    int how_many_boxes;
    BITMAP* ltl_box;
    int box_h, box_w;
    
public:
    Interface(Character* h1, Character* h2)
    {
        hero1 = h1;
        hero2 = h2;
        
        hero1_txt[0].w = hero2_txt[0].w = 20;
        hero1_txt[1].w = hero2_txt[1].w = 275;
        hero1_txt[2].w = hero2_txt[2].w = 259;
        hero1_txt[3].w = hero2_txt[3].w = 308;
        hero1_txt[4].w = hero2_txt[4].w = 193;
        hero1_txt[5].w = hero2_txt[5].w = 392;
        hero1_txt[6].w = hero2_txt[6].w = 227;
        hero1_txt[7].w = hero2_txt[7].w = 326;
        
        for (i = 0; i < 8; i++)
        {
            hero1_txt[i].y = 20;
            hero1_txt[i].x = 100;
            hero1_txt[i].h = 27;
            hero1_txt[i].lewo = 100;
            hero1_txt[i].prawo = hero1_txt[i].lewo + hero1_txt[i].w;
            
            hero2_txt[i].h = 27;
            hero2_txt[i].prawo = 1190;
            hero2_txt[i].lewo = hero2_txt[i].prawo - hero2_txt[i].w;
            hero2_txt[i].y = 20;
            hero2_txt[i].x = hero2_txt[i].lewo;
        }
            


        hero1_txt[0].img = hero2_txt[0].img = create_bitmap( 2, 2 );
        clear_to_color( hero1_txt[0].img, makecol(0,0,0) );
        clear_to_color( hero2_txt[0].img, makecol(0,0,0) );
        
        hero1_txt[1].img = hero2_txt[1].img = load_bmp("int/immortal.bmp", default_palette);
        hero1_txt[2].img = hero2_txt[2].img = load_bmp("int/power_up.bmp", default_palette);
        hero1_txt[3].img = hero2_txt[3].img = load_bmp("int/slow_down.bmp", default_palette);
        hero1_txt[4].img = hero2_txt[4].img = load_bmp("int/freeze.bmp", default_palette);
        hero1_txt[5].img = hero2_txt[5].img = load_bmp("int/instant_slash.bmp", default_palette);
        hero1_txt[6].img = hero2_txt[6].img = load_bmp("int/no_limit.bmp", default_palette);
        hero1_txt[7].img = hero2_txt[7].img = load_bmp("int/ninja_slash.bmp", default_palette);
        
        
        
        freq = 600;
        how_many_boxes = 18;
        ltl_box = load_bmp("int/box.bmp", default_palette);
        box_h = box_w = 30;
    
    }
    
    
    
    void draw(BITMAP* bufor)
    {
        masked_blit( hero1_txt[hero1->extra].img, 
        bufor, 0,0 , 
        hero1_txt[hero1->extra].x, 
        hero1_txt[hero1->extra].y, 
        hero1_txt[hero1->extra].w, 
        hero1_txt[hero1->extra].h );
        
        masked_blit( hero2_txt[hero2->extra].img, 
        bufor, 0,0 , 
        hero2_txt[hero2->extra].x, 
        hero2_txt[hero2->extra].y, 
        hero2_txt[hero2->extra].w, 
        hero2_txt[hero2->extra].h );
        
        for (int w(0); w < how_many_boxes; w++)
        {
            masked_blit( 
            ltl_box, bufor, 0, 0, 
            (w*box_w), 766, 
            box_w, box_h );
        }
    }
};
