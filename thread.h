#ifndef __THREAD__
#define __THREAD__

/**
This thread class exists in the game already, this is simply my best imitation of it
*/


#define BUILD_BUG_ON(condition) (void)(sizeof(char[1 - 2*!!(condition)]))

#define MaxThreadSize 0x6C

#define INITADDRESS 0x8002C7D
#define KILLADDRESS 0x80030E9
#define SEARCH 0x8002E9D
#define SCAN 0x8002F25

template<typename T>
class Thread{ 
public:
    enum Action
    {
        Kill, SetText, ExecuteOnce, Execute, 
        SetDestructor, SubThread, SubThreadWithArgs, SubThread2,
        ThreadSearch, KillAll, AdvanceAll, Skip, 
        SkipUntil, SetPosition, Buffer, Set26, 
        Nothing, KillIfDupExists 
    };
    typedef void(*Threadfunc)(Thread*);
    class ThreadData{
    public:
        Action action;
        Threadfunc tfunc;
        Thread* ThreadInit(Action action=Execute){
            Thread*(*func)(ThreadData* d, Action a) = (Thread*(*)(ThreadData*, Action))(INITADDRESS);
            return func(this, action);
        }
        Thread* Search(){
        	Thread*(*func)(ThreadData* d) = (Thread*(*)(ThreadData*))(SEARCH);
        	return func(this);
        }
    };
    Thread(){
        BUILD_BUG_ON((sizeof(T) > MaxThreadSize) ? 1 : 0);
		//ensures all subclasses will be at most 0x6C bytes
    }
    private:
        ThreadData* origin;
        ThreadData* current;
        Threadfunc destructor;
        Threadfunc currfunc;
        char* threaddesc; // probably a debug relic
        Thread* parent;
        Thread* child;
        Thread* parent2;
        Thread* child2;
        short buffer; //number of frames to sleep for
        short unk;

};
