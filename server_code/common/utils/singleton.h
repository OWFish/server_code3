#pragma  once
template< typename T >
struct Singleton
{
	typedef T value_type;
	typedef Singleton self_type;

private:// not to be implemented
	Singleton(const self_type&){}
	self_type& operator = (const self_type&){}
	Singleton(){}

	friend T;
private:// this struct promises thread safty    
	struct creator
	{
		creator()
		{   // ensure that instance() called before main() starts
			self_type::instance();
		}
		inline void null_action() const
		{
			//empty
		}
	};

	static creator creator_;

public:
	static value_type& instance()
	{   // the object to be returned
		static value_type instance_;
		// force the initialization of creator_
		creator_.null_action();
		return instance_;
	}
};

template<typename T>
typename Singleton<T>::creator Singleton<T>::creator_;