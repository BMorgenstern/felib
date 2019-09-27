/*
Represents a standard bitmap of variable length, though usually 32 bits. 
*/

template <typename T>
class BitField{
    private:
        T field;
        bool valid(int bit){
			return bit < (sizeof(field)*8);
		}
    public:
        bool flagged(int bit){
            if(valid(bit))
                return this->field & (1<<bit);
            else 
                return false;
        }
        void toggleOn(int bit){
            if(valid(bit))
                this->field |= (1<<bit);
        }
        void toggleOff(int bit){
            if(valid(bit))
                this->field &= ~(1<<bit);
        }
};
