#include "Button.h"

class Controller{
	private:
		const byte framesTilHeld;
		const byte inputDelay;
		byte frameCounter;
		byte unused;
		Button directInput;
		Button held;
		Button pressed;
		static Controller* getGameController(){
			return (Controller*)GAMECONTROLLER;
		}
	public:
		static bool Pressed(int input){
			return getGameController()->pressed.down(input);
		}
        static bool Held(int input){
			return getGameController()->held.down(input);
		}
};