#include "Bitfield.h"

/*
Buttons on the GBA's controller; each bit represents a different button being pressed
*/

class Button : public BitField<unsigned short>{
	public:
		enum{A,B,Select,Start,Right,Left,Up,Down,R,L};
		bool down(int input){
            return this->flagged(input);
        }
};