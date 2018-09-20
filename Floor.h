class Floor: public Drawables
{
public:
    Floor(int posx, int posy)
    {
        img = load_bmp("floors/floor1.bmp", default_palette);
        wdth = 56; 
        hgth = 46;
        x = posx;
        y = posy;
        gora = y;
        dol = y + hgth;
        lewo = x;
        prawo = x + wdth; 
        
        solid = (true);
    }

};
