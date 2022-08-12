// 这个实现自己的算法库
#ifndef ALGORITHM_H_
#define ALGORITHM_H_

#include <iostream>

namespace stl {

	template<class _iter, class _T>
	_iter find(const _iter& begin, const _iter& end, const _T& val) {
		for (_iter it = begin; it != end; ++it) {
			if (*it == val) {
				return it;
			}
		}
		return end;
	}

	// 利用快速排序
	// 1 2 4 1 5 2
	// p
	// i
	//           j
	// p和谁相同，谁不能动
	// p和谁交换，p和谁相同
	// 当p i j 都相同时，递归调用

	// 此处适合基本数据类型
	template<class _iter>
	void sort(const _iter& begin, const _iter& end) {
		_iter p = begin;
		_iter last = end;
		--last;
		for (_iter i = begin, j = last; i != j; ) {
			while (i != p && *i < *p)
				++i;
			if (i != p) {
				std::swap(*i, *p);
				p = i;
			}
			while (j != p && *p < *j)
				--j;
			if (j != p) {
				std::swap(*p, *j);
				p = j;
			}
		}
		_iter it = begin;
		++it;
		if (p != it && p != begin)
			sort(begin, p);
		it = p;
		++it;
		if (it != end && it != last)
			sort(it, end);
	}

	// 以下用比较器实现
	// _Pre 代表谓词 predicate
	template<class _iter, class _Pre>
	void sort(_iter begin, _iter end, _Pre cmp) {
		_iter p = begin;
		_iter last = end;
		--last;
		for (_iter i = begin, j = last; i != j; ) {
			while (i != p && cmp(*i, *p))
				++i;
			if (i != p) {
				std::swap(*i, *p);
				p = i;
			}
			while (j != p && cmp(*p, *j))
				--j;
			if (j != p) {
				std::swap(*p, *j);
				p = j;
			}
		}
		_iter it = begin;
		++it;
		if (p != it && p != begin)
			sort(begin, p, cmp);
		it = p;
		++it;
		if (it != end && it != last)
			sort(it, end, cmp);
	}
}
#endif
