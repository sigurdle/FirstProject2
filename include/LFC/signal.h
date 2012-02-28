#ifndef System_signal_h
#define System_signal_h

#if 0
#ifndef __LERSTAD__
/*
namespace std
{
#include <wchar.h>
}
*/
#include <cwchar>
#include <list>
#endif
#endif

namespace System
{

template<class arg1_type> class signal1;
template<class arg1_type, class arg2_type> class signal2;
template<class arg1_type, class arg2_type, class arg3_type> class signal3;

class stub_interface_base : public Object
{
//	virtual void invoke_object(Object* object) = 0;
//	virtual bool Equals(stub_interface_base* other) = 0;

	/*
	virtual ~stub_interface_base()
	{
	}
	*/

	//static const Type_Info& signal_type() const = 0;
};

template<class return_type, class arg1_type> class stub_interface1 : public stub_interface_base
{
public:

	typedef signal1<arg1_type> signal_type;

	virtual return_type invoke(arg1_type arg1) = 0;
};

template<class return_type, class arg1_type, class arg2_type> class stub_interface2 : public stub_interface_base
{
public:

	typedef signal2<arg1_type, arg2_type> signal_type;

	virtual return_type invoke(arg1_type arg1, arg2_type arg2) = 0;
};

template<class return_type, class arg1_type, class arg2_type, class arg3_type> class stub_interface3 : public stub_interface_base
{
public:

	typedef signal3<arg1_type, arg2_type, arg3_type> signal_type;

	virtual return_type invoke(arg1_type arg1, arg2_type arg2, arg3_type arg3) = 0;
};

template<class return_type, class arg1_type, class arg2_type, class arg3_type, class arg4_type> class stub_interface4 : public stub_interface_base
{
public:

	//typedef signal3<arg1_type, arg2_type, arg3_type> signal_type;

	virtual return_type invoke(arg1_type arg1, arg2_type arg2, arg3_type arg3, arg4_type arg4) = 0;
};

template<class F, class return_type, class arg1_type> class stub1 : public stub_interface1<return_type, arg1_type>
{
public:
	CTOR stub1(const F& f) : m_f(f)
	{
	}

#if 0
	virtual bool Equals(stub_interface_base* other)
	{
		if (GetType(this) != GetType(other))
			return false;

		ASSERT(0);
		//return m_f == ((stub<F, arg1_type>*)other)->m_f;
		return false;
	}
#endif

	/*
	virtual void invoke_object(Object* object)
	{
		invoke(unbox_cast<arg1_type>(object));
	}
	*/

	virtual return_type invoke(arg1_type arg1)
	{
		/* TODO return */
		m_f(arg1);
	}

	F m_f;
};

template<class F, class return_type, class arg1_type, class arg2_type> class stub2 : public stub_interface2<return_type, arg1_type, arg2_type>
{
public:
	CTOR stub2(const F& f) : m_f(f)
	{
	}

	virtual return_type invoke(arg1_type arg1, arg2_type arg2)
	{
		/* TODO return */
		m_f(arg1, arg2);
	}

	F m_f;
};

template<class F, class return_type, class arg1_type, class arg2_type, class arg3_type> class stub3 : public stub_interface3<return_type, arg1_type, arg2_type, arg3_type>
{
public:
	CTOR stub3(const F& f) : m_f(f)
	{
	}

	virtual return_type invoke(arg1_type arg1, arg2_type arg2, arg3_type arg3)
	{
		/* TODO return */
		m_f(arg1, arg2, arg3);
	}

	F m_f;
};

template<class F, class return_type, class arg1_type, class arg2_type, class arg3_type, class arg4_type> class stub4 : public stub_interface4<return_type, arg1_type, arg2_type, arg3_type, arg4_type>
{
public:
	CTOR stub4(const F& f) : m_f(f)
	{
	}

	virtual return_type invoke(arg1_type arg1, arg2_type arg2, arg3_type arg3, arg4_type arg4)
	{
		/* TODO return */
		m_f(arg1, arg2, arg3, arg4);
	}

	F m_f;
};

class function_base
{
public:
	CTOR function_base(stub_interface_base* stub) : m_stub(stub)
	{
	}

	operator stub_interface_base* () const
	{
		return m_stub;
	}

	stub_interface_base* m_stub;
};

template<class arg1_type> class function1// : public function_base
{
public:

	typedef arg1_type argument1_type;

	typedef arg1_type first_argument_type;

	CTOR function1(const function1<arg1_type>& other)
	{
		m_stub = other.m_stub;
	}

	template<class F> CTOR function1(F f)
	{
		m_stub = new stub1<F, void, arg1_type>(f);
	}

	void operator () (arg1_type arg1) const
	{
		m_stub->invoke(arg1);
	}

	operator stub_interface_base* () const
	{
		return m_stub;
	}

	typedef stub_interface1<void, arg1_type> stub_type;

	stub_type* m_stub;
};

template<class arg1_type, class arg2_type> class function2// : public function_base
{
public:

	typedef arg1_type argument1_type;
	typedef arg2_type argument2_type;

	typedef arg1_type first_argument_type;
	typedef arg2_type second_argument_type;

	CTOR function2(const function2<arg1_type, arg2_type>& other)
	{
		m_stub = other.m_stub;
	}

	template<class F> CTOR function2(F f)
	{
		m_stub = new stub2<F, void, arg1_type, arg2_type>(f);
	}

	void operator () (arg1_type arg1, arg2_type arg2) const
	{
		m_stub->invoke(arg1, arg2);
	}

	operator stub_interface_base* () const
	{
		return m_stub;
	}

	typedef stub_interface2<void, arg1_type, arg2_type> stub_type;

	stub_type* m_stub;
};

template<class arg1_type, class arg2_type, class arg3_type> class function3// : public function_base
{
public:

	typedef arg1_type argument1_type;
	typedef arg2_type argument2_type;
	typedef arg3_type argument3_type;

	typedef arg1_type first_argument_type;
	typedef arg2_type second_argument_type;
	typedef arg3_type third_argument_type;

	typedef void result_type;

	CTOR function3(const function3<arg1_type, arg2_type, arg3_type>& other)
	{
		m_stub = other.m_stub;
	}

	template<class F> CTOR function3(F f)
	{
		m_stub = new stub3<F, void, arg1_type, arg2_type, arg3_type>(f);
	}

	void operator () (arg1_type arg1, arg2_type arg2, arg3_type arg3) const
	{
		m_stub->invoke(arg1, arg2, arg3);
	}

	operator stub_interface_base* () const
	{
		return m_stub;
	}

	typedef stub_interface3<void, arg1_type, arg2_type, arg3_type> stub_type;

	stub_type* m_stub;
};

template<class arg1_type, class arg2_type, class arg3_type, class arg4_type> class function4// : public function_base
{
public:

	typedef arg1_type argument1_type;
	typedef arg2_type argument2_type;
	typedef arg3_type argument3_type;
	typedef arg4_type argument4_type;

	CTOR function4(const function4<arg1_type, arg2_type, arg3_type, arg4_type>& other)
	{
		m_stub = other.m_stub;
	}

	template<class F> CTOR function4(F f)
	{
		m_stub = new stub4<F, void, arg1_type, arg2_type, arg3_type, arg4_type>(f);
	}

	void operator () (arg1_type arg1, arg2_type arg2, arg3_type arg3, arg4_type arg4) const
	{
		m_stub->invoke(arg1, arg2, arg3, arg4);
	}

	operator stub_interface_base* () const
	{
		return m_stub;
	}

	typedef stub_interface4<void, arg1_type, arg2_type, arg3_type, arg4_type> stub_type;

	stub_type* m_stub;
};

#if 0
template<class function_type> class slot
{
public:

	/*
	slot(function_type f) : func(f)
	{
	}
	*/

	template<class Slot> slot(Slot s) : func(s)
	{
	}

	/*
	slot(const function_type& f) : func(f)
	{
	}
	*/

	function_type func;
};
#endif

class LFCEXT signal_base : public Object
{
public:
	virtual unsigned int GetSlotCount() = 0;
	virtual stub_interface_base* GetSlot(unsigned int index) = 0;
	virtual void connect(stub_interface_base* slot) = 0;
	/*
	virtual Object* BeginIterator() = 0;
	virtual Object* EndIterator() = 0;
	virtual Object* Next(Object* object) = 0;
	virtual stub_interface_base* At(Object* iterator) = 0;
	*/

	virtual const Type_Info& GetHandlerType() const = 0;
};

template<class arg1_type> class signal1 : public signal_base
{
public:

	CTOR signal1()
	{
	}

	typedef function1<arg1_type> slot_function_type;

//	typedef slot<slot_function_type> slot_type;

	virtual const Type_Info& GetHandlerType() const
	{
		return typeid(slot_function_type::stub_type);
	}

//	typedef slot_function_type slot_type;

//#ifndef __LERSTAD__
	typedef typename list<slot_function_type>::iterator connection_type;
//#else
//	typedef void connection_type;
//#endif

	/*
	virtual Object* BeginIterator()
	{
		return m_slots.begin().m_ptr;
	}

	virtual Object* EndIterator()
	{
		return m_slots.end().m_ptr;
	}

	virtual Object* Next(Object* object)
	{
		(std::list<slot_function_type>::value_type*)object
	}

	virtual stub_interface_base* At(Object* iterator) = 0;
	*/

	unsigned int GetSlotCount()
	{
		return m_slots.size();
	}

	stub_interface_base* GetSlot(unsigned int index)
	{
//#ifndef __LERSTAD__
		typename list<slot_function_type>::iterator it = m_slots.begin();
		while (index--)
		{
			++it;
		}

		return *it;
//#endif
	}

	virtual void connect(stub_interface_base* slot)
	{
		connect(dynamic_cast<slot_function_type::stub_type*>(slot));
	}

	connection_type connect(const slot_function_type& s)
	{
	//	function1<arg1_type>* p = new function1<arg1_type>(s);;
		return m_slots.insert(m_slots.end(), s);
	}

	void disconnect(connection_type connection)
	{
		m_slots.erase(connection);
	}

	bool empty() const
	{
		return m_slots.empty();
	}

	void operator () (arg1_type arg1)
	{
		//m_slot.func(arg1);
//#ifndef __LERSTAD__
		typename list<slot_function_type>::iterator it = m_slots.begin();
		while (it != m_slots.end())
		{
			(*it)(arg1);

			++it;
		}
//#endif
	}

	//slot_function_type* m_slot;

	list<slot_function_type> m_slots;
#if 0
#ifndef __LERSTAD__
	std::list<slot_function_type> m_slots;
#else

	char/*__gc_allocator*/ m_list_a;
	void* m_list_p;
	int m_list_size;

#endif
#endif

//	list<slot_function_type, __gc_allocator> m_slots; 
};

template<class arg1_type, class arg2_type> class signal2 : public signal_base
{
public:

	CTOR signal2()
	{
	}

	typedef function2<arg1_type, arg2_type> slot_function_type;

	virtual const Type_Info& GetHandlerType() const
	{
		return typeid(slot_function_type::stub_type);
	}

//	typedef slot<slot_function_type> slot_type;

//	typedef slot_function_type slot_type;

//#ifndef __LERSTAD__
	typedef typename list<slot_function_type>::iterator connection_type;
//#else
//	typedef void connection_type;
//#endif

	unsigned int GetSlotCount()
	{
		return m_slots.size();
	}

	stub_interface_base* GetSlot(unsigned int index)
	{
//#ifndef __LERSTAD__
		typename list<slot_function_type>::iterator it = m_slots.begin();
		while (index--)
		{
			++it;
		}

		return *it;
//#endif
	}

	virtual void connect(stub_interface_base* slot)
	{
		connect(dynamic_cast<slot_function_type::stub_type*>(slot));
	}

//	connection_type connect(const slot_function_type& s)
	connection_type connect(const slot_function_type& s)
	{
	//	function1<arg1_type>* p = new function1<arg1_type>(s);;
		return m_slots.insert(m_slots.end(), s);
	}

	void disconnect(connection_type connection)
	{
		m_slots.erase(connection);
	}

	bool empty() const
	{
		return m_slots.empty();
	}

	void operator () (arg1_type arg1, arg2_type arg2)
	{
		//m_slot.func(arg1);
//#ifndef __LERSTAD__
		typename list<slot_function_type>::iterator it = m_slots.begin();
		while (it != m_slots.end())
		{
			(*it)(arg1, arg2);

			++it;
		}
//#endif
	}

	//slot_function_type* m_slot;

	list<slot_function_type> m_slots;

#if 0
#ifndef __LERSTAD__
	std::list<slot_function_type> m_slots;
#else

	char/*__gc_allocator*/ m_list_a;
	void* m_list_p;
	int m_list_size;

	/*
#ifndef __LERSTAD__

	class slots2
	{
	public:
		CTOR slots2(signal2& sig) : m_sig(sig)
		{
		}

		void operator () (arg1_type arg1, arg2_type arg2)
		{
			//m_slot.func(arg1);
	#ifndef __LERSTAD__
			std::list<slot_function_type>::iterator it = m_slots.begin();
			while (it != m_slots.end())
			{
				(*it)(arg1, arg2);

				++it;
			}
	#endif
		}

		signal2& m_sig;
	};

#endif
  */

#endif
#endif

//	list<slot_function_type, __gc_allocator> m_slots; 
};

/*
template<class arg1_type, class arg2_type> const Type_Info& signal_type(const stub_interface2<arg1_type, arg2_type>& stub)
{
	return typeid(signal2<arg1_type, arg2_type>);
}
*/

template<class arg1_type, class arg2_type, class arg3_type> class signal3 : public signal_base
{
public:

	CTOR signal3()
	{
	}

	typedef function3<arg1_type, arg2_type, arg3_type> slot_function_type;

	virtual const Type_Info& GetHandlerType() const
	{
		return typeid(slot_function_type::stub_type);
	}

	typedef typename list<slot_function_type>::iterator connection_type;

	unsigned int GetSlotCount()
	{
		return m_slots.size();
	}

	stub_interface_base* GetSlot(unsigned int index)
	{
		typename list<slot_function_type>::iterator it = m_slots.begin();
		while (index--)
		{
			++it;
		}

		return *it;
	}

	virtual void connect(stub_interface_base* slot)
	{
		connect(dynamic_cast<slot_function_type::stub_type*>(slot));
	}

//	connection_type connect(const slot_function_type& s)
	connection_type connect(const slot_function_type& s)
	{
	//	function1<arg1_type>* p = new function1<arg1_type>(s);;
		return m_slots.insert(m_slots.end(), s);
	}

	void disconnect(connection_type connection)
	{
		m_slots.erase(connection);
	}

	bool empty() const
	{
		return m_slots.empty();
	}

	void operator () (arg1_type arg1, arg2_type arg2, arg3_type arg3)
	{
		typename list<slot_function_type>::iterator it = m_slots.begin();
		while (it != m_slots.end())
		{
			(*it)(arg1, arg2, arg3);

			++it;
		}
	}

	list<slot_function_type> m_slots;
};

}

#endif // System_signal_h
