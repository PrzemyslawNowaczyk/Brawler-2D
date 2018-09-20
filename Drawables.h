class Drawables
{
public: 
    volatile int x; 
    volatile int y; 
    int hgth; 
    int wdth;
    
    volatile int gora;            //krawêdzie bundingboxa;
    volatile int dol;
    volatile int lewo;
    volatile int prawo;

    BITMAP* img; 
    bool solid;
    
public:
    virtual void draw(BITMAP* bufor)
    {
        masked_blit( img, bufor, 0,0, x,y, wdth, hgth);
    }
    
};

LOCK_VARIABLE( x );
LOCK_VARIABLE( y );
LOCK_VARIABLE( gora );
LOCK_VARIABLE( dol );
LOCK_VARIABLE( prawo );
LOCK_VARIABLE( lewo );
