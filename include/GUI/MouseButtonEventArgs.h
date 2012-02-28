namespace System
{
namespace Gui
{

class GUIEXT MouseButtonEventArgs : public MouseEventArgs
{
public:
	CTOR MouseButtonEventArgs(void* mouseDevice, int timestamp);

	virtual void InvokeEventHandler(Object* genericTarget, IFunction* genericHandler);
};

}	// UI
}
