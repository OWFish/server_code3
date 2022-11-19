/*
 * 一个用来把固定大小的数组封装成类stl::vector的类
 * 适用于不想用动态数组（自动扩充内存）的地方，封装了add、insert、remove等方法，易于使用（仅此目的）
 * 缺点是数组是固定大小的（当然是在定义模板类的时候指定），不能自动根据需要扩展内存
*/


#ifndef _STATIC_ARRAY_LIST_H_
#define _STATIC_ARRAY_LIST_H_

namespace container 
{
	template<typename T,int MAX_NUM>
	class StaticArrayList 
	{

	protected:
		T data_ptr_[MAX_NUM];
		int count_;
	public:
		StaticArrayList(){
			count_ = 0;
		}
		virtual ~StaticArrayList(){
			count_ = 0;
		}

		inline operator T* () { return data_ptr_; }
		inline operator T* () const { return const_cast<T*>(data_ptr_); }

		int size() const { return count_; }
		int count() const { return count_; }
		int max_size() const { return MAX_NUM; }

		int add(const T& data)
		{
			assert( count_ + 1 <= MAX_NUM );

			memcpy(&data_ptr_[count_], &data, sizeof(data));
			count_++;
			return count_-1;
		}

		int push_back(const T& data)
		{
			return add(data);
		}

		void insert(const int index, const T& data)
		{
			assert( index > -1 && index <= count_ );
			if ( index < count_ )
			{
				memmove(data_ptr_ + index + 1, data_ptr_ + index, sizeof(T) * (count_ - index) );
			}

			data_ptr_[index] = data;
			count_++;
		}

		inline const T& get(const int index) const
		{
			assert( index > -1 && index < count_ );
			return data_ptr_[index];
		}

		inline void set(const int index, const T &item)
		{
			assert( index > -1 && index < count_ );
			data_ptr_[index] = item;
		}


		void remove(const int index)
		{
			assert( index > -1 && index < count_ );

			remove( index, 1 );
		}

		void remove(const int index, const int num)
		{
			assert( index + num <= count_ );

			if ( num > 0 )
			{
				memmove( data_ptr_ + index, data_ptr_ + index + num, sizeof(data_ptr_[0]) * (count_ - index - num) );
				count_ -= num;
			}
		}

		inline void clear()
		{
			count_ = 0;
		}
		inline void trunc(const int num)
		{
			assert( num > -1 && num <= MAX_NUM );
			count_ = num;
		}
		inline void addArray(const T* data, int length)
		{
			assert ( count_ + length <= MAX_NUM );
			memcpy(data_ptr_ + count_, data, length * sizeof(T));
			count_ += length;
		}
		inline void addList(const Vector<T> &list)
		{
			addArray((T*)list, list.count_);
		}
		int index(const T& data) const
		{
			for ( int i = count_ - 1; i > -1; --i )
			{
				if ( data_ptr_[i] == data )
				{
					return i;
				}
			}

			return -1;
		}
	};//end class StaticArrayList

}//end namespace container

#endif


