#ifndef COLOR_H
#define COLOR_H

#define RGBA8(r,g,b,a) ((((a)&0xFF)<<24) | (((b)&0xFF)<<16) | (((g)&0xFF)<<8) | (((r)&0xFF)<<0))

class Color
{
	public:
		Color (void);
		Color (int r, int g, int b);
		Color (int r, int g, int b, int a);
		Color (const Color & rhs);
		
		~Color (void);

		void setRed (int value);
		void setGreen (int value);
		void setBlue (int value);
		void setAlpha (int value);
		
		int getRed (void) const;
		int getGreen (void) const;
		int getBlue (void) const;
		int getAlpha (void) const;
		
		unsigned int convert_to_vita2d (void) const;

		const Color & operator = (const Color & rhs);
		

	private:
		void check (int & value);

		unsigned char red_;
		unsigned char green_;
		unsigned char blue_;
		unsigned char alpha_;
};

#endif
