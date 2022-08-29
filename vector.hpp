#ifndef VECTOR_H_
#define VECTOR_H_

#include <cstddef>
#include <exception>

// vector.hpp

#define DEFAULT_SIZE 0
#define DEFAULT_CAPACITY 50
#define HEAD_INDEX 0

namespace stl {

	template<class _T>
	class vector {
		typedef _T value_type;
		typedef _T& reference;
		typedef _T* pointer;
	private:
		// 维护的数据
		value_type* m_data;
		size_t m_capacity; // 容量大小
		size_t m_size;  // 实际元素个数

	public:
		// 正向非常迭代器
		class iterator {
			typedef value_type* _iter;
		private:
			_iter m_start;  
			_iter m_cur;
			_iter m_end;

		public:
			iterator(_iter start, _iter cur, _iter end):
			m_start(start), m_cur(cur), m_end(end){}

			reference operator*() {
				if (nullptr == m_cur) {
					m_cur = m_start;
				}
				return *m_cur;
			}

			pointer operator->() {
				if (nullptr == m_cur) {
					m_cur = m_start;
				}
				return static_cast<pointer>(m_cur);
			}
			// 后置++
			iterator& operator++() {
				if (m_cur == nullptr)
					m_cur = m_start;
				++m_cur;
				return *this;
			}

			iterator& operator--() {
				if (m_cur == nullptr)
					m_cur = m_start;
				--m_cur;
				return *this;
			}

			bool operator==(const iterator& _other) {
				return m_start == _other.m_start &&
					m_cur == _other.m_cur &&
					m_end == _other.m_end;
			}

			bool operator!=(const iterator& _other) {
				return !(*this == _other);
			}
			

		public:
			friend class vector;
		};

	public:
		vector() : 
			m_size(DEFAULT_SIZE), 
			m_capacity(DEFAULT_CAPACITY)  {
			this->m_data = new value_type[m_capacity];
		}

		vector(const vector& vec) {
			this->m_capacity = vec.m_capacity;
			this->m_data = new value_type[this->m_capacity];
			for (int i = 0; i < vec.m_size; ++i) {
				this->push_back(vec.m_data[i]);
			}
		}

		// 析构
		~vector() {
			clear();
			if (this->m_data != nullptr) {
				delete[] this->m_data;
			}
		}

		// 尾插法
		void push_back(const _T& data) {
			// 先判断是否达到最大容量
			if (this->m_size == this->m_capacity) {
				// 扩容
				this->m_capacity = 2 * this->m_capacity;
				value_type* new_data = new value_type[m_capacity];
				for (int i = 0; i < this->m_size; ++i) {
					new_data[i] = this->m_data[i];
				}
				// 删除原来的空间
				delete[] this->m_data;
				// 指向新空间
				this->m_data = new_data;
			}
			// 添加新元素
			this->m_data[this->m_size] = data;
			++this->m_size;
		}
		// 获取第一个元素
		reference front() {
			if (isEmpty()) {
				throw std::exception("Empty element");
			}
			else {
				return this->m_data[HEAD_INDEX];
			}
		}
		value_type const& front () const {
			if (this->m_size == DEFAULT_SIZE) {
				throw std::exception("Empty element");
			}
			else {
				return this->m_data[HEAD_INDEX];
			}
		}

		// 获取最后一个元素
		reference back() {
			if (isEmpty()) {
				throw std::exception("Empty element");
			}
			else {
				return this->m_data[this->m_size - 1];
			}
		}
		const reference back() const {
			if (m_size == DEFAULT_SIZE) {
				throw std::exception("Empty element");
			}
			else {
				return this->m_data[this->m_size - 1];
			}
		}

		// 删除最后一个元素
		void pop_back() {
			// 逻辑删除
			if (isEmpty()) {
				throw std::exception("Empty Vector!");
			}
			else {
				//::operator delete(&this->m_data[m_size]);
				--m_size;
				if (m_size < m_capacity / 4) {
					m_capacity /= 2;
				}
			}
		}

		reference at(unsigned int index) {
			if (index < 0 || index > m_size - 1) {
				throw std::exception("Out of Array index");
			}
			return this->m_data[index];
		}

		const reference at(unsigned int index) const {
			if (index < 0 || index > m_size - 1) {
				throw std::exception("Out of Array index");
			}
			return this->m_data[index];
		}

		// 清空vector
		void clear() {
			this->m_size == 0;
		}

		size_t capacity() {
			return this->m_capacity;
		}

		size_t capacity() const {
			return this->m_capacity;
		}

		size_t size() {
			return this->m_size;
		}

		size_t size() const {
			return this->m_size;
		}

		bool isEmpty() {
			return this->m_size == DEFAULT_SIZE;
		}

		// 重载[]可以像普通数组一样使用
		value_type& operator[](unsigned int index) {
			if (index < 0 || index > m_size) {
				throw std::exception("Out of Array index");
			}
			return this->m_data[index];
		}

	public:
		iterator begin() {
			return iterator(m_data, m_data, m_data + m_size - 1);
		}
		iterator end() {
			return iterator(m_data, m_data + m_size, m_data + m_size - 1);
		}
	};

}

#endif
