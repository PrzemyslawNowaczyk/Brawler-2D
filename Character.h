#define LEFT false
#define RIGHT true
#define ANONE 0
#define ALEFT 1
#define ARIGHT 2
#define ABOTH 3
#include "Extras.h"

class Character: public Drawables
{

public:
    volatile int horizontal_speed;
    volatile int vertical_speed;
    BITMAP* imgleft;
    BITMAP* imgright;
    BITMAP* powerBar;
    BITMAP* current;
    
    BITMAP* ninja_slashl;
    BITMAP* ninja_slashr;
    int ninja_slash_w;
    int ninja_slash_h;
    int ninja_slash_state;
    bool ninja_slash_active;
    bool atk_clicked;
    
    volatile int stan;
    
    volatile bool ground_under_legs;
    bool jump_up;
    bool attack;
    bool slash;
    
    int jump_tick;
    int prev_hgth;
    int tickCS;
    unsigned int tickAtk;
    int tickSlash;
    
    int act_key_up;
    int act_key_left;
    int act_key_right;
    int act_key_slash;
    
    Extras extra;    
    
    int fails;
    char score[3];
    
    int avatar_x;
    int avatar_y;
    
    bool bot;
    bool boted;
    bool priori;
    bool make_decision;
    int currkey;
    
public:
    Character(bool p1):
        
        avatar_y(0),
        horizontal_speed(0),
        stan(0),
        jump_up(false),
        ground_under_legs(false),
        jump_tick(-20),
        prev_hgth(0),
        tickCS(0),
        tickAtk(0),
        powerBar(create_bitmap( 2600, 15 )),
        attack(false),
        slash(false),
        fails(0),
        extra(none)
        {
    
            if (p1)
            {   
                imgleft = load_bmp("chars/char1l.bmp", default_palette);
                imgright = load_bmp("chars/char1r.bmp", default_palette);
                current = imgright;
                
                x = 200;
                avatar_x = 20;
                hgth = 66;
                wdth = 114;
                
                bot = false;
                boted = false;
                
                act_key_up = KEY_W;
                act_key_left = KEY_A;
                act_key_right = KEY_D;
                act_key_slash = KEY_SPACE;
            }
            
            else
            {   
                imgleft = load_bmp("chars/char2l.bmp", default_palette);
                imgright = load_bmp("chars/char2r.bmp", default_palette);
                current = imgleft;
                
                x = 1000;
                avatar_x = 1160;
                hgth = 66;
                wdth = 114;
                
                bot = false;
                boted = true;
                priori = true;
                
                act_key_up = KEY_I;
                act_key_left = KEY_J;
                act_key_right = KEY_L;
                act_key_slash = KEY_RSHIFT;
            }
            
            y = -200;    
            gora = y + 20;
            dol = y + hgth;
            lewo = x + 45;
            prawo = x + wdth - 45;
            
            
            ninja_slashl = load_bmp("effects/ninja_slashl.bmp", default_palette);
            ninja_slashr = load_bmp("effects/ninja_slashr.bmp", default_palette);
            ninja_slash_w = 268;
            ninja_slash_h = 37;
            ninja_slash_active = false;
            
            ltoa(fails, score, 10);
            
            atk_clicked = true;
        }




public:
    void set_speed(vector<Floor>* floors, vector<Box>* boxes, BITMAP* bufor, Character* enemy)
    {
        bool any_boxes(false);
        
        
        
        
        if ( !bot )
        {
            if (extra != 4)
            {
                if (key[act_key_right] && !key[act_key_left])                       {currkey = ARIGHT;}
                if (key[act_key_left] && !key[act_key_right])                       {currkey = ALEFT;}
                if (!key[act_key_left] && !key[act_key_right])                      {currkey = ANONE;}
                if (key[act_key_left] && key[act_key_right])                        {currkey = ABOTH;}
                if (key[act_key_up] && ground_under_legs && !jump_up)               {jump_up = true;}
                if (key[act_key_slash] && !attack)                                  {attack = true;}
            }
            
            else
            {
                currkey = ANONE;
                jump_up = false;
                attack = true;
                tickAtk = 0;
                jump_tick = -20;
                tickSlash = 0;
                ninja_slash_active = false;
            }
        }
        
        
        
        
        
        else
        {
            int wanted_x(0);
            int wanted_y(0);
            
            if (priori)     { wanted_x = enemy->lewo; wanted_y = enemy->dol; }
//            else            { wanted_x = 640; wanted_y = enemy->y; }
            else
            {
                    wanted_x = (*boxes)[boxes->size()-1].lewo; 
                    wanted_y = (*boxes)[boxes->size()-1].dol;
            }
           
            if (!attack) attack = true;
            atk_clicked = true;

            if (!ground_under_legs) make_decision = true;
 
            if (dol >= wanted_y)
            {
                if (ground_under_legs && dol-wanted_y > 50) jump_up = true;
                if (lewo < wanted_x)        { currkey = ARIGHT; }
                else                        { currkey = ALEFT; }
            }
            else
            {
                if (make_decision )
                {
                    if (lewo < wanted_x)        { currkey = ARIGHT; }
                    else                        { currkey = ALEFT; }
                    make_decision = false;
                }
            }
            
            if (dol == wanted_y)
            {   int zasieg;
            
                if (extra == 7) {zasieg = 250;}
                else            {zasieg = 60;}
                
                if ( current == imgleft && lewo - wanted_x <= zasieg || current == imgright && wanted_x - lewo <= zasieg )
                {
                    
                    currkey = ANONE;
                    
                    if (tickAtk > 50)
                    {
                        atk_clicked = false;
                    }
                    
                }
            }
            
        }
        
        
        
        
        
        
        
        
        
        
        
        
        int speed_limit;
        
        if (extra == 3)     { speed_limit = 6; }
        else                { speed_limit = 30; }
        
        if (currkey == ARIGHT)
        {   
                if (current == imgleft)                     { current = imgright; }
                if (horizontal_speed < speed_limit)         { horizontal_speed++; }
                if (horizontal_speed < 0)                   { horizontal_speed++; }
        }
        
        
        if (currkey == ALEFT)
        {   
            if (current == imgright)                        { current = imgleft; }
            if (horizontal_speed > -speed_limit)            { horizontal_speed--; }
            if (horizontal_speed > 0)                       { horizontal_speed--; }
            
        }
        
        
        if (currkey == ANONE || currkey == ABOTH)
        {
            if (horizontal_speed > 0)   {horizontal_speed--;}
            if (horizontal_speed < 0)   {horizontal_speed++;}
        }
        
        
        if (!floorColl(floors) && !jump_up)
        {
            vertical_speed++;
            if (vertical_speed > 10)    
            {
                vertical_speed = 10;
            }
        }
        else
        {
            vertical_speed = 0;
        }
        
        
        if(jump_up)
        {
            int temp;
            temp = count_jump(jump_tick);
            vertical_speed = temp - prev_hgth;
            prev_hgth = temp;
            jump_tick++;
            
            
            if (jump_tick == 0)
            {
                jump_up = false;
                prev_hgth = 0;
                jump_tick = -20;
            }
            
        }
        
        if (attack)
        {
            
            if (!bot)   { atk_clicked = key[act_key_slash]; }
            
            
            if(atk_clicked)
            {
                if (extra != 4)
                {
                    int counter;
                    
                    if (extra == 5)         { counter = 25; }
                    else                    { counter = 2; }
                    
                    
                    int limit;
                    if (extra == 6)         { limit = 2600; }
                    else                    { limit = 125; }
                    
                    
                    if (tickAtk < limit)
                    {
                        tickAtk += counter;
                    }
                    clear_to_color( powerBar, makecol(tickAtk*2, 0, 0 ) );
                    blit (powerBar, bufor, 0, 0, ( (x + wdth/2) - (tickAtk/2) ), (y - 20), tickAtk, 15);
                }
            }
            
            else
            {
                attack = false;
                slash = true;
                if (extra == 7)         { ninja_slash_active = true; }
                tickSlash = 0;
                tickCS = 0;
                hit_enemy(enemy);
                hit_box(boxes);
                tickAtk = 0;
            }
        
        }
        
        if (key[KEY_TAB] && boted && tickCS == 33)               { bot = !bot; }
        
        if ( bot && ( extra == 0 || extra == 3 ) && boxes->size() > 0 )       { priori = false; }
        else                                                                { priori = true; }
    }
    
    
    
    
    
    
    
    
    
    void hit_enemy(Character* enemy)
    {
        if (enemy->gora - gora < hgth && enemy->gora - gora > (-hgth) && extra != 4)
        {
            int punch = tickAtk;
            int range;
            if (extra == 7)             { range = ninja_slash_w;}
            else                        { range = 75;}
            if (enemy->extra == 1)      { punch = punch/3; }
            
            if (current == imgright 
            && enemy->prawo - prawo > 10
            && enemy->prawo - prawo < range)
            {
                if (extra == 2)     { enemy->horizontal_speed = punch; }
                else                { enemy->horizontal_speed = punch/2; }
            }
            
            if (current == imgleft
            && lewo - enemy->lewo > 10
            && lewo - enemy->lewo < range)
            {
                if (extra == 2)     { enemy->horizontal_speed = -(punch); }
                else                { enemy->horizontal_speed = -(punch/2); }
            }
        
        }
        
    }
    
    
    
    
    
    void hit_box(vector<Box>* boxes)
    {
        for (int i(0); i < boxes->size(); i++)
        {
            if ((*boxes)[i].gora - gora < hgth && (*boxes)[i].gora - gora > (-hgth))
            {
                
                int punch = tickAtk;
                if (extra != 2)         { punch = punch/2; }
                
                int range;
                if (extra == 7)             { range = ninja_slash_w;}
                else                        { range = 90;}
                
                if 
                (      (current == imgright 
                    && (*boxes)[i].prawo - prawo > 10
                    && (*boxes)[i].prawo - prawo < range)
                    ||  
                    (current == imgleft
                    && (*boxes)[i].lewo - lewo < 10
                    && lewo - (*boxes)[i].lewo < range)    )
                    
                {
                    (*boxes)[i].hp -= punch;
                }
                
            }
        }
        
        for (int i(0); i < boxes->size(); i++)
        {
            if ( (*boxes)[i].hp <=0 && !(*boxes)[i].empty )
            {
                extra = (Extras) (*boxes)[i].inside;
                (*boxes)[i].empty = true;
                priori = true;
            }
        }
        
    }
    
    
    
    
    
    
    void move()
    {
        x = x + horizontal_speed/2;
        y = y + vertical_speed*2;
        gora = y + 20;
		dol = y + hgth;
		lewo = x + 45;
		prawo = x + wdth - 45;
        
        if (x > 1200)
        {
            if (horizontal_speed > 35)
            {
                horizontal_speed = -horizontal_speed;
                current = imgleft;
            }
            
            else
            {
                horizontal_speed = 0; 
                x = 1200;
            }
            
        }
        
        if (x < 0)
        {
            if (horizontal_speed < -35)
            {
                horizontal_speed = -horizontal_speed;
                current = imgright;
            }
            else
            {
                horizontal_speed = 0; 
                x = 0;
            }
        }

        if (y >= 1000)
        {
            horizontal_speed = 0;
			stan = 0;
			jump_up = false;
			ground_under_legs = (false);
			jump_tick = (-20);
			prev_hgth = (0);
			tickCS = (0);
			tickAtk = (0);
			attack = (false);
			slash = (false);
			y = 0;
			x = 500;
			fails++;
			extra = none;
			ltoa(fails, score, 10);
        }
    }
    
    
    
    
    
    
    bool floorColl (vector<Floor>* floors)
    {
        
        for(int a(0); a < floors->size(); a++)
        {
            if(!jump_up && ( y+hgth >= (*floors)[a].gora-11 && y+hgth <= (*floors)[a].gora+11 ) )
            {    
                if (prawo >= (*floors)[a].lewo && prawo <= (*floors)[a].prawo
                ||  lewo >= (*floors)[a].lewo && lewo <= (*floors)[a].prawo
                ||  lewo >= (*floors)[a].lewo && prawo <= (*floors)[a].prawo)
                {
                        y = (*floors)[a].gora - hgth;
                        ground_under_legs = true;
                        return true;
                }
            }
        }
        
        ground_under_legs = false;
        return false;
    }   
    
    
    
    
    
    void changeState()
    {
        if (extra != 4)     { tickCS++; }
     
        if (tickCS > 34)    { tickCS = 0; }
        
        if (slash)
        {
            if (tickSlash == 0)     { stan = 342; }
            
            tickSlash++;
            
            if (ninja_slash_active)     {ninja_slash_state = ( (tickSlash/4) + 1) * ninja_slash_w; }
            
            if (tickSlash == 10)       { slash = false; ninja_slash_active = false;}
        }
        else
        {
            if(attack)              { stan = 228; }
            else
            {
                if (!ground_under_legs)     { stan = 114; }
                else
                {
                    
                    if (horizontal_speed == 0)      { stan = 0; }
                    else
                    {
                        if (tickCS == 0 || tickCS == 16)         { stan = 0; }
                        if (tickCS == 8 || tickCS == 24)       { stan = 114; }
                        
                    }
                    
                }
            
            }
        }
        
    }
    
    
    
    
    void draw(BITMAP* bufor)
    {
        masked_blit( current, bufor, stan,0, x,y, wdth, hgth);
        if(!bot) masked_blit( current, bufor, stan,0, avatar_x, avatar_y, wdth, hgth);
        if( ninja_slash_active )        
        {   
            if (current == imgleft)
            {
                masked_blit( ninja_slashl, bufor, 
                             ninja_slash_state, 0, 
                             prawo - ninja_slash_w - tickSlash * 2, dol-45, 
                             ninja_slash_w, ninja_slash_h );
            }
            else
            {
                masked_blit( ninja_slashr, bufor,
                             ninja_slash_state, 0,
                             prawo + tickSlash * 4, dol-45,
                             ninja_slash_w, ninja_slash_h );
            }
        }
    
 
    }
    
    
    
    
    int count_jump(int X)
    {
        return ( ((X/2) * (X/2)) - 100 );
    }
    
    
    LOCK_VARIABLE( horizontal_speed);
    LOCK_VARIABLE( vertical_speed );
    LOCK_VARIABLE( stan );
    LOCK_VARIABLE( ground_under_legs );
    LOCK_FUNCTION( set_speed );
    LOCK_FUNCTION( move );
    LOCK_FUNCTION( changeState );
    LOCK_FUNCTION( draw );
};
