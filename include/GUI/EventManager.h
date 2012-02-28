namespace System
{
namespace Gui
{

class GUIEXT EventManager
{
public:

	class PerClass : public Object
	{
	public:
		CTOR PerClass();

		vector<list<IFunction*> > m_handlers;
	};

	static RoutedEvent* RegisterRoutedEvent(StringIn name, RoutingStrategy routingStrategy, const Type_Info& handlerType, ClassType* ownerType);

	static void RegisterClassHandler(ClassType* classType, RoutedEvent* pEvent, IFunction* handler);
	static void RegisterClassHandler(ClassType* classType, RoutedEvent* pEvent, IFunction* handler, bool handledEventsToo);

	static void InvokeClassHandlers(ClassType* classType, Object* instance, RoutedEventArgs* args);

public:

	friend class UIElement;

private:

	class Private : public Object
	{
	public:
		vector<RoutedEvent*> m_routedEvents;
		map<String,PerClass*> s_perclass;
	};

	static Private* s_private;

//	static unsigned int s_count;
//	static RoutedEvent* s_events[512];	// TODO
};

}	// UI
}
