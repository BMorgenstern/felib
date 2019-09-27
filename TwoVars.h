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