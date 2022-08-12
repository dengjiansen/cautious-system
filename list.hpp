#ifndef LIST_H_
#define LIST_H_

#include <exception>

// 我自己实现的stl都放在命名空间stl中

#define DEFAULT_SIZE 0

namespace stl {

	template<class _T>
	class list {
		typedef _T value_type;

	private:
		// 链表的节点类
		typedef class NODE {
		public:
			class NODE* m_next;
			class NODE* m_prev;
			value_type m_data;

		public:
			NODE(NODE* prev, value_type data, NODE* next)
			: m_prev(prev), m_data(data), m_next(next){}

		}node;


	private:
		node* m_head; // 指向头节点
		node* m_tail; // 指向尾节点
		unsigned int node_num; // 节点的数量

	public:
		// 正向非常迭代类
		class ITERATOR {
		private:
			node* m_start;
			node* m_cur;
			node* m_end;
		public:
			ITERATOR(node* start, node* cur, node* end) :
				m_start(start), m_cur(cur), m_end(end) {}
			/*
				重载各种操作符
			*/

			value_type& operator*() {
				if (m_cur == nullptr) {
					throw std::exception("null node");
				}
				return m_cur->m_data;
			}

			// 前置++
			ITERATOR& operator++() {
				if (m_cur == nullptr) {
					m_cur = m_start;
				}
				else {
					m_cur = m_cur->m_next;
				}
				return *this;
			}

			// 后置++
			ITERATOR operator++(int) {
				ITERATOR _iter = *this;
				++(*this);
				return _iter;
			}

			// 前置--
			ITERATOR& operator--() {
				if (m_cur == nullptr) {
					m_cur = m_end;
				}
				else {
					m_cur = m_cur->m_prev;
				}
				return *this;
			}

			// 后置--
			ITERATOR operator--(int) {
				ITERATOR _iter = *(this);
				--(*this);
				return _iter;
			}

			bool operator==(ITERATOR const& _other) const {
				return this->m_start == _other.m_start &&
					this->m_end == _other.m_end &&
					this->m_cur == _other.m_cur;
			}

			bool operator!=(const ITERATOR& _other) const {
				return !(*this == _other);
			}

			value_type* operator->() {
				if (m_cur == nullptr) {
					throw std::exception("null node");
				}
				return &(m_cur->m_data);
			}
			// 声明为友元类
			friend class list;
			friend class REVERSE_ITERATOR;
		};

	public:
		// 正向常迭代器
		class CONST_ITERATOR {
		private:
			ITERATOR m_it;
		public:

			CONST_ITERATOR(const ITERATOR&  _iter):m_it(_iter) {}

			const value_type& operator*() {
				return const_cast<value_type&>(*m_it);
			}

			CONST_ITERATOR& operator++() {
				++m_it;
				return *this;
			}

			CONST_ITERATOR operator++(int) {
				CONST_ITERATOR const_iter = *this;
				++(*this);
				return const_iter;
			}

			CONST_ITERATOR& operator--() {
				--m_it;
				return *this;
			}

			CONST_ITERATOR operator--(int) {
				CONST_ITERATOR const_iter = *this;
				--(*this);
				return const_iter;
			}

			bool operator==(const CONST_ITERATOR& _other) {
				return m_it == _other.m_it;
			}

			bool operator!= (const CONST_ITERATOR& _other) {
				return m_it != _other.m_it;
			}

			const value_type* operator->() {
				return &(*m_it);
			}

		};

	public:
		// 反向非常迭代器
		class REVERSE_ITERATOR {

		private:
			ITERATOR m_it;
		public:
			REVERSE_ITERATOR(const ITERATOR& _other): m_it(_other) {}

			value_type& operator*() {
				return static_cast<value_type&>(*m_it);
			}

			// 前置++
			REVERSE_ITERATOR& operator++() {
				--m_it;
				return *this;
			}

			// 后置++
			REVERSE_ITERATOR operator++(int) {
				REVERSE_ITERATOR reverse_iter = *this;
				++(*this);
				return reverse_iter;
			}

			// 前置--
			REVERSE_ITERATOR& operator--() {
				++m_it;
				return *this;
			}

			// 后置--
			REVERSE_ITERATOR operator--(int) {
				REVERSE_ITERATOR reverse_iter = *this;
				--(*this);
				return reverse_iter;
			}

			bool operator==(const REVERSE_ITERATOR& _other) {
				return m_it == _other.m_it;
			}

			bool operator!=(const REVERSE_ITERATOR& _other) {
				return m_it != _other.m_it;
			}

			value_type* operator->() {
				return const_cast<value_type*>(&(*m_it));
			}

		};

	public:
		// 反向常迭代器
		class REVERSE_CONST_ITERATOR {
		private:
			REVERSE_ITERATOR m_reverse_it;
		public:
			REVERSE_CONST_ITERATOR(const REVERSE_ITERATOR& _other): 
				m_reverse_it(_other) {}

			const value_type& operator*() {
				return *m_reverse_it;
			}

			REVERSE_CONST_ITERATOR& operator++() {
				++m_reverse_it;
				return *this;
			}
			REVERSE_CONST_ITERATOR operator++(int) {
				REVERSE_CONST_ITERATOR r_const_iter = *this;
				++(*this);
				return r_const_iter;
			}

			REVERSE_CONST_ITERATOR& operator--() {
				--m_reverse_it;
				return *this;
			}

			REVERSE_CONST_ITERATOR operator--(int) {
				REVERSE_CONST_ITERATOR r_const_iter = *this;
				--(*this);
				return r_const_iter;
			}

			const value_type* operator->() {
				return const_cast<value_type*>(&(*m_reverse_it));
			}

			bool operator==(const REVERSE_CONST_ITERATOR& _other) {
				return m_reverse_it == _other.m_reverse_it;
			}

			bool operator!= (const REVERSE_CONST_ITERATOR& _other) {
				return m_reverse_it != _other.m_reverse_it;
			}
		};

	public:
		// 默认构造
		list():m_head(nullptr), m_tail(nullptr), node_num(DEFAULT_SIZE) {}
		// 拷贝构造
		list(const list& _other) : m_head(nullptr), m_tail(nullptr) {
			for (node* pCurr = _other.m_head; pCurr != nullptr; pCurr = pCurr->m_next) {
				this->push_back(pCurr->m_data);
			}
		}
		// 析构函数
		~list() {
			this->clear();
		}
		// 链表判断是否为空
		bool isEmpty() {
			return this->m_head == nullptr &&
				this->m_tail == nullptr;
		}
		//  添加头节点
		void push_front(const value_type& data) {
			this->m_head = new node(nullptr, data, m_head);
			if (this->m_head->m_next)
				this->m_head->m_next->m_prev = this->m_head;
			else
				this->m_tail = this->m_head;
			++node_num;
		}

		// 删除链表头节点
		void pop_front() {
			if (this->isEmpty()) {
				return;
			}
			node* pCurr = m_head->m_next;
			delete m_head;
			if (pCurr) {
				pCurr->m_prev = nullptr;
			}
			else {
				m_tail = nullptr;
			}
			m_head = pCurr;
			--node_num;
		}

		// 获取头节点数据
		value_type& front() {
			if (this->isEmpty()) {
				throw std::exception("null node");
			}
			return this->m_head->m_data;
		}

		// 重载版本
		value_type const& front() const {
			return const_cast<list*>(this)->front();
		}

		// 添加尾节点
		void push_back(const value_type& data) {

			m_tail = new node(m_tail, data, nullptr);
			if (m_tail->m_prev) {
				m_tail->m_prev->m_next = m_tail;
			}
			else {
				m_head = m_tail;
			}
			++node_num;
		}

		// 删除尾节点
		void pop_back() {
			if (this->isEmpty()) {
				return;
			}
			node* pCurr = m_tail->m_prev;
			delete m_tail;
			if (pCurr) {
				pCurr->m_next = nullptr;
			}
			else {
				m_head = nullptr;
			}
			m_tail = pCurr;
			--node_num;
		}

		// 获取尾节点
		value_type& back() {
			if (this->isEmpty()) {
				throw std::exception("null node");
			}
			return this->m_tail->m_data;
		}

		// 重载版本
		value_type const& back() const {
			return const_cast<list*>(this)->back();
		}

		// 清空链表
		void clear() {
			while (!isEmpty()) {
				this->pop_front();
			}
			node_num = DEFAULT_SIZE;
		}

		// 链表大小
		unsigned int size() {
			return this->node_num;
		}

		unsigned int size() const {
			return this->node_num;
		}

	public:
		using iterator = ITERATOR;
		using const_iterator = CONST_ITERATOR;
		using reverse_iterator = REVERSE_ITERATOR;
		using reverse_const_iterator = REVERSE_CONST_ITERATOR;
		
		// 获取起始迭代器
		iterator begin() {
			return iterator(m_head, m_head, m_tail);
		}

		iterator end() {
			return iterator(m_head, nullptr, m_tail);
		}

		const_iterator begin() const {
			return iterator(m_head, m_head, m_tail);
		}

		const_iterator end() const {
			return iterator(m_head, nullptr, m_tail);
		}

		reverse_iterator rbegin() {
			return iterator(m_tail, m_tail, m_head);
		}

		reverse_iterator rend() {
			return iterator(m_tail, nullptr, m_head);
		}

		reverse_const_iterator rbegin() const {
			return reverse_iterator(iterator(m_tail, m_tail, m_head));
		}

		reverse_const_iterator rend() const {
			return reverse_iterator(iterator(m_tail, nullptr, m_head));
		}

		// 在指定位置插入节点
		void insert(const iterator& loc, value_type& data) {
			if (loc == this->end()) {
				this->push_back(data);
			}
			else {
				node* newNode = new node(loc.m_cur->m_prev, data, loc.m_cur);
				if (newNode->m_prev) {
					newNode->m_prev->m_next = newNode;
				}
				else {
					m_head = newNode;
				}
				newNode->m_next->m_prev = newNode;

			}
			++node_num;
		}

		// 移除节点
		void erase(const iterator& loc) {
			if (loc == end()) {
				return;
			}
			--node_num;
			node* pCurr = loc.m_cur;
			if (pCurr->m_prev) {
				pCurr->m_prev->m_next = pCurr->m_next;
			}
			else {
				this->m_head = pCurr->m_next;
			}
			if (pCurr->m_next) {
				pCurr->m_next->m_prev = pCurr->m_prev;
			}
			else {
				this->m_tail = pCurr->m_prev;
			}
			delete pCurr;
		}
	};
}

#endif 
