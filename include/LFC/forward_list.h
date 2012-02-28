namespace System
{

template<class TYPE, class A> class forward_list
{
public:

	class node : public Object
	{
	public:

		CTOR node() : m_next(NULL)
		{
		}

		TYPE m_item;
		node* m_next;
	};

	class const_iterator
	{
	};

	class iterator
	{
	public:

		iterator& operator ++ ()
		{
			ASSERT(m_p);
			m_p = m_p->m_next;
			return *this;
		}

		iterator operator ++ (int)
		{
			ASSERT(m_p);
			iterator it(m_p);
			m_p = m_p->m_next;
			return it;
		}

		TYPE& operator * ()
		{
			return *m_p;
		}

		const TYPE& operator * () const
		{
			return *m_p;
		}

	private:

		node* m_p;
	};

	CTOR forward_list() :m_size(0)
	{
		m_head = new node;
	}

	size_t size() const
	{
		return m_size;
	}

	iterator begin()
	{
		return iterator(m_head);
	}

	iterator end()
	{
		return iterator(NULL);
	}

	void push_back(TYPE& item)
	{
		node* p = new node(item);
		m_tail->m_next = p;
		m_tail = p;
	}

	/*
	template<class Predicate> void remove_if(Predicate _Pred)
	{
		node* p = m_head;
		node* prev;
		while (p)
		{
			p = p->m_next;

			if (_Pred(prev->m_item))
			{
				prev->m_next = p;
			}
		}
	}
	*/

	/*
	const_iterator cbegin() const
	{
		return iterator(m_head);
	}

	const_iterator cend() const
	{
		return iterator(NULL);
	}
	*/

	node* m_head;
	node* m_tail;
	size_t m_size;
};

}
