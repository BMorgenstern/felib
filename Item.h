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
            return this->addTop(uses);
        }
		Item (){
			this->data = 0;
		}
        Item(int val){
            this->data = val;
        }
        Item(int id, int uses){
            setBoth(uses, id);
        }
};