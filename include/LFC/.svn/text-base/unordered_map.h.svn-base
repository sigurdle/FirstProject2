namespace System
{

inline size_t hash_value(bool val)
{
	return val;
}

inline size_t hash_value(char val)
{
	return val;
}

inline size_t hash_value(signed char val)
{
	return val;
}

inline size_t hash_value(unsigned char val)
{
	return val;
}

inline size_t hash_value(wchar_t val)
{
	return val;
}

inline size_t hash_value(short val)
{
	return val;
}

inline size_t hash_value(unsigned short val)
{
	return val;
}

inline size_t hash_value(int val)
{
	return val;
}

inline size_t hash_value(unsigned int val)
{
	return val;
}

inline size_t hash_value(long val)
{
	return val;
}

inline size_t hash_value(unsigned long val)
{
	return val;
}

/*
size_t hash_value(long long val);
size_t hash_value(unsigned long long val);
*/

inline size_t hash_value(float val)
{
	return *(int*)&val;
}

/*
size_t hash_value(double val);
size_t hash_value(long double val);
*/

template<class T1, class T2 = T1> struct equal_to : public binary_function<T1, T2, bool>
{
	bool operator() (const T1& x, const T2& y) const
	{
		return x == y;
	}
};

template<class T> struct deref_equal_to : public binary_function<T, T, bool>
{
	bool operator() (T x, T y) const
	{
		return *x == *y;
	}
};

template<
	class key_t,
	class value_t,
	class Hash = hash<key_t>,
	class Pred = equal_to<key_t> >

class unordered_map
{
public:

	typedef unsigned int size_type;

	typedef pair<key_t,value_t> key_value_t;
	typedef pair<key_t,value_t> value_type;

	typedef typename list<key_value_t>::iterator iterator;

	typedef typename list<key_value_t>::iterator local_iterator;
	typedef typename list<key_value_t>::const_iterator const_local_iterator;

	CTOR unordered_map()
	{
		m_size = 0;

		m_buckets.resize(17);	// Default size
	}

	size_type size() const
	{
		return m_size;
	}

	iterator end()
	{
		return m_buckets[0].end();
	}

	size_t bucket_count() const
	{
		return m_buckets.size();
	}

	size_t bucket_size(unsigned int n) const
	{
		return m_buckets[n].size();
	}

	local_iterator begin(size_type n)
	{
		return m_buckets[n].begin();
	}

	const_local_iterator begin(size_type n) const
	{
		return m_buckets[n].begin();
	}

	local_iterator end(size_type n)
	{
		return m_buckets[n].end();
	}

	const_local_iterator end(size_type n) const
	{
		return m_buckets[n].end();
	}

	/*
	void Add(const key_t& key, const value_t& value)
	{
		size_t hashcode = GetHashCode(key);
		unsigned int index = hashcode % m_hashSize;

		m_table[index].push_back(value);

		++m_size;
	}
	*/

	template<class key_type> value_t& operator [](key_type& key)
	{
		size_t hashcode = m_hasher(key);
		unsigned int index = (unsigned int)(hashcode % m_buckets.size());

		typename list<key_value_t>::iterator it = m_buckets[index].begin();
		while (it != m_buckets[index].end())
		{
			if (m_predicator(it->first, key))
				return it->second;

			++it;
		}

		++m_size;
		return m_buckets[index].insert(m_buckets[index].end(), key_value_t(key, value_t()))->second;
	}

	template<class key_type> iterator find(key_type& key)
	{
		size_t hashcode = m_hasher(key);
		unsigned int index = hashcode % m_buckets.size();

		typename list<key_value_t>::iterator it = m_buckets[index].begin();
		while (it != m_buckets[index].end())
		{
			if (m_predicator(it->first, key))
				return it;

			++it;
		}

		return end();
	}

	void clear()
	{
		for (unsigned int i = 0; i < m_buckets.size(); i++)
		{
			m_buckets[i].clear();
		}
		m_size = 0;
	}

	vector<list<key_value_t>, __gc_allocator> m_buckets;
	Hash m_hasher;
	Pred m_predicator;
	size_type m_size;
};

}	// System
