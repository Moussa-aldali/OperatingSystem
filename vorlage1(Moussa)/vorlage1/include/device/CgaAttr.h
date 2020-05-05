#ifndef CgaAttr_h
#define CgaAttr_h

/*
 * CgaAttr: 	Softwareprototyp fuer CGA Darstellungsattribute
 *		Hier braucht man Bitoperationen!
 *
 *		Da *alle* Operationen sehr einfach und kurz sind,
 *		duerft Ihr sie direkt in der Klasse
 *		als inline Methoden deklarieren.
 */

class CgaAttr {
private:
    char globalAtrr;

	enum AttrMaskAndShifts {
        Vordergrundfarbe = 0xf0,  // 11110000
        Hintergrundfarbe = 0x8f,  // 10001111
        Blinken = 0x7f, // 01111111
        VordergrundMask = 0xf,
        HintergrundMask = 0x70,
        BlinkenMask = 7
	};


public:
	/** 	Diese Aufz�hlung enth�lt die CGA-Farben als Farbkonstanten
	 *	Tragt hier *alle* CGA Farben mit den richtigen Werten ein
	 */
	enum Color {
        BLACK,BLUE,BROWN,CYAN,GRAY,GREEN,
        LIGHT_BLUE,LIGHT_CYAN,LIGHT_GRAY,LIGHT_GREEN,
        LIGHT_MAGENTA,LIGHT_RED,MAGENTA,RED,WHITE,YELLOW
	};


	/** Konstruktor. Erzeugt ein CgaAttr-Objekt mit den uebergebenen Werten f�r
	  * Vorder- und Hintergrundfarbe. Werden keine Parameter uebergeben,
	  * so werden die Defaultwerte (Vordergrund weiss, Hintergrund schwarz, Blinken deaktiviert)
	  * verwendet.
	  */
	CgaAttr(Color fg=WHITE, Color bg=BLACK, bool blink=false)
	{
        setForeground(fg);
        setBackground(bg);
        setBlinkState(blink);
	}

	// setzen der Schriftfarbe
	void setForeground(Color col)
	{
        globalAtrr = globalAtrr & Vordergrundfarbe ;
        globalAtrr = globalAtrr ^ col ;

	}

	// setzen der Hintergrundfarbe
	void setBackground(Color col)
	{
        globalAtrr = globalAtrr & Hintergrundfarbe ;
        globalAtrr = globalAtrr ^ (col << 4) ;
    }

	// setzen blinkender/nicht blinkender Text
	void setBlinkState(bool blink)
	{
        globalAtrr = globalAtrr & Blinken ;
        globalAtrr = globalAtrr ^ (blink << 7) ;
	}

	// setzen aller Attribute
	void setAttr(CgaAttr attr)
	{
        setBlinkState(attr.getBlinkState());
        setBackground(attr.getBackground());
        setForeground(attr.getForeground());
	}

	// ermitteln der Schriftfarbe
	Color getForeground()
	{
        return (Color) (globalAtrr & VordergrundMask);
	}

	// ermitteln der Hintergrundfarbe
	Color getBackground()
	{
        return (Color) (globalAtrr & HintergrundMask);
    }

	// ermitteln ob Blink-Flag gesetzt ist
	bool getBlinkState()
	{
        return (bool) (globalAtrr >> BlinkenMask);
	}



};

#endif
