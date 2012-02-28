namespace System
{
namespace Gui
{

class GUIEXT RoutedEventArgs : public EventArgs
{
public:
	CTOR RoutedEventArgs();
	CTOR RoutedEventArgs(RoutedEvent* routedEvent);
	CTOR RoutedEventArgs(RoutedEvent* routedEvent, Object* source);

	RoutedEvent* get_RoutedEvent();
	void set_RoutedEvent(RoutedEvent* routedEvent);

	Object* get_Source();
	void set_Source(Object* source);

	Object* get_OriginalSource()
	{
		return m_originalSource;
	}

	bool get_Handled()
	{
		return m_handled;
	}

	void set_Handled(bool handled);

	virtual void InvokeEventHandler(Object* genericTarget, IFunction* genericHandler);

protected:

	virtual void OnSetSource(Object* source);	// Override this if you want

private:

	friend class UIElement;

	RoutedEvent* m_routedEvent;
	Object* m_source;
	Object* m_originalSource;
	bool m_handled;
};

#if 0
class GUIEXT CanExecuteRoutedEventArgs : public RoutedEventArgs
{
public:
	CTOR CanExecuteRoutedEventArgs(ICommand* command, Object* parameter);

	bool get_CanExecute();
	void set_CanExecute(bool canExecute);

	ICommand* get_Command();
	Object* get_Parameter();

	virtual void InvokeEventHandler(Object* genericTarget, stub_interface_base* genericHandler);

private:

	friend class RoutedCommand;

	ICommand* m_command;
	Object* m_parameter;
	bool m_canExecute;
};

class GUIEXT ExecutedRoutedEventArgs : public RoutedEventArgs
{
public:
	CTOR ExecutedRoutedEventArgs(ICommand* command, Object* parameter);
//	CTOR ExecutedRoutedEventArgs(RoutedEvent* routedEvent);
//	CTOR ExecutedRoutedEventArgs(RoutedEvent* routedEvent, Object* source);

	ICommand* get_Command();
	Object* get_Parameter();

	virtual void InvokeEventHandler(Object* genericTarget, stub_interface_base* genericHandler);

	ICommand* m_command;
	Object* m_parameter;
};
#endif

//

enum DragDropEffects
{
	DragDropEffects_None = 0,
	DragDropEffects_Copy = 1,
	DragDropEffects_Move = 2,
	DragDropEffects_Link = 4,
	DragDropEffects_Scroll = 8,
	DragDropEffects_All = 0xffffffff,
};

class GUIEXT DragEventArgs : public RoutedEventArgs
{
public:

	CTOR DragEventArgs(IDataObjectPtr data) : m_data(data)
	{
	}

	Point GetPosition(IInputElement* relativeTo);

	DragDropEffects get_AllowedEffects()
	{
		return m_allowedEffects;
	}

	DragDropEffects get_Effects()
	{
		return m_effects;
	}

	void set_Effects(DragDropEffects effects);

	IDataObjectPtr get_Data()
	{
		return m_data;
	}

	virtual void InvokeEventHandler(Object* genericTarget, IFunction* genericHandler) override;

private:

	friend class InputManager;

	double m_X;
	double m_Y;
	IDataObjectPtr m_data;
	DragDropEffects m_allowedEffects;
	DragDropEffects m_effects;
};

class GUIEXT InputEventArgs : public RoutedEventArgs
{
public:

	CTOR InputEventArgs(int timestamp);

	int get_Timestamp() const
	{
		return m_timestamp;
	}

private:

	friend class InputManager;

	int m_timestamp;
};

class GUIEXT ContextMenuEventArgs : public RoutedEventArgs
{
};

class GUIEXT QueryCursorEventArgs : public RoutedEventArgs
{
public:

	CTOR QueryCursorEventArgs(RoutedEvent* routedEvent) : RoutedEventArgs(routedEvent)
	{
	}

	CTOR QueryCursorEventArgs(RoutedEvent* routedEvent, Object* source) : RoutedEventArgs(routedEvent, source)
	{
	}

	Cursor* get_Cursor()
	{
		return m_cursor;
	}

	void set_Cursor(Cursor* cursor)
	{
		m_cursor = cursor;
	}

public:

	Cursor* m_cursor;

	float m_screenX;
	float m_screenY;
};

class GUIEXT KeyboardEventArgs : public InputEventArgs
{
public:
	CTOR KeyboardEventArgs(int timestamp);
};

class GUIEXT KeyEventArgs : public KeyboardEventArgs
{
public:

	CTOR KeyEventArgs(
		void* /*KeyboardDevice*/ keyboard,
		void* /*PresentationSource*/ inputSource,
		int timestamp,
		int/*Key*/ key);

	bool get_IsDown() const;
	bool get_IsRepeat() const;

	virtual void InvokeEventHandler(Object* genericTarget, IFunction* genericHandler);

	int m_key;
};

class GUIEXT TextCompositionEventArgs : public InputEventArgs
{
public:
	CTOR TextCompositionEventArgs(void* inputDevice, void* composition) : InputEventArgs(0)
	{
	}

//	virtual void InvokeEventHandler(Object* genericTarget, stub_interface_base* genericHandler);
	virtual void InvokeEventHandler(Object* genericTarget, IFunction* genericHandler) override;

	String get_Text()
	{
		return m_text;
	}

	String m_text;
};

#if 0
class GUIEXT DragDeltaEventArgs : public RoutedEventArgs
{
public:

	void InvokeEventHandler(Object* genericTarget, stub_interface_base* genericHandler);

	double m_HorizontalChange;
	double m_VerticalChange;
};

template<class T> class RoutedPropertyChangedEventArgs : public RoutedEventArgs
{
public:
	CTOR RoutedPropertyChangedEventArgs(T oldValue, T newValue)
	{
		m_newValue = newValue;
		m_oldValue = oldValue;
	}

	CTOR RoutedPropertyChangedEventArgs(T oldValue, T newValue, RoutedEvent* routedEvent) : RoutedEventArgs(routedEvent)
	{
		m_newValue = newValue;
		m_oldValue = oldValue;
	}

	T get_NewValue()
	{
		return m_newValue;
	}

	T get_OldValue()
	{
		return m_oldValue;
	}

	virtual void InvokeEventHandler(Object* genericTarget, stub_interface_base* genericHandler)
	{
		stub_interface2<void, Object*, RoutedPropertyChangedEventArgs<T>*>* handler = dynamic_cast<stub_interface2<void, Object*, RoutedPropertyChangedEventArgs<T>*>*>(genericHandler);
		ASSERT(handler);

		handler->invoke(genericTarget, this);
	}

	T m_newValue;
	T m_oldValue;
};
#endif

}	// Gui
}
