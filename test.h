int(*shopPrice)(Unit* patron, Item item) = (int(*)(Unit*, Item))(0x80B5220 | 1);


template <typename Data>
class TwoVars{
    protected:
        Data data;
        int getSize(){
            return sizeof(this->data)*4;
        }
        int getMax(){
            return (1 << this->getSize()) - 1;
        }
        int getBottom(int arg){
            return arg  & this->getMax();
        }
        int getBottom(){
            return this->getBottom(this->data);
        }
        int getTop(int arg){
            return (int)arg >> this->getSize();
        }
        int getTop(){
            return this->getTop(this->data);
        }
        void setBottom(int bottom){
            bottom = this->getBottom(bottom);
            this->data = (this->getTop() << this->getSize()) | bottom;
        }
        void setTop(int top){
            int bottom = this->getBottom();
            this->data = (int)((top << this->getSize()) | bottom);
        }
        void setBoth(int top, int bottom){
            this->data = (top << this->getSize()) + bottom;
        }
        bool addTop(int uses){
            int result = this->getTop()+uses;
            if(result < 0 || result > getMax())
                return true;
            this->data += (uses << this->getSize());
            return false;
        }
        bool addBottom(int uses){
            int result = uses + getBottom();
            if(result < 0 || result > getMax())
                return true;
            this->data += uses;
            return false;
        }
    public:
        TwoVars(){
            this->data = -1;
        }
        TwoVars(int bottom, int top){
            this->setTop(top);
            this->setBottom(bottom);
        }
        TwoVars(int val){
            this->data = val;
        }
};

class Item : public TwoVars<unsigned short>{
    public:
        int getID(){
            return this->getBottom();
        }
        int getUses(){
            return this->getTop();
        }
        void setID(int id){
            this->setBottom(id);
        }
        void setUses(int uses){
            this->setTop(uses);
        }
        bool addUses(int uses){
            //this->setTop(this->getUses()+uses);
            //this->addTop(uses);
            return this->addTop(uses);
        }
        Item(int val){
            this->data = val;
        }
        Item(int id, int uses){
            setBoth(uses, id);
        }
};

/*
class Item{
    public:
        unsigned char id;
        unsigned char uses;
        void addUses(int add){
            this->uses += add;
        }
};
*/
class Inventory{
    private:
        Item items[5];
    public:
        Item getItem(int index){
            if(index > -1 && index < 5)
                return this->items[index]; 
            else
                return Item(0);
        }
        void setItem(int index, Item item){
            if(index > -1 && index < 5)
                this->items[index] = item; 
        }
};

void inInventory(Inventory* in, int id){
        Item newitem = in->getItem(0);
        if(newitem.addUses(-1))
            newitem = Item(1,46);
        in->setItem(0, newitem);
}


typedef unsigned char byte;


class ID{
    public:
    enum IDType{character, clazz, event};
    IDType type;
    byte id;
};

class ForgeItem{
    private:
        byte* output;
        byte* ingredients;
        short price;
        short displayText;
        ID* ids;
};

int s(ID* ip){
    return (ip->type == ID::event) ? 3 :1;
}