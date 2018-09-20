class Background: public Drawables
{
public:
    Background()
    {
        x = 0;
        y = 0;
        wdth = 1280;
        hgth = 800;
        img = load_bmp("bck/bck_1.bmp", default_palette);
    }
};
