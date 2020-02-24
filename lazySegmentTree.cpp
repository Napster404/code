#include <iostream>
#include <vector>
#include <functional>
#include <bitset>

using namespace std;

template <class T>
class SegmentTree{
	
	int arr_size;
	
	T default_return;

	std::vector<T> seg;
	std::std::vector <T> update_seg; 
	std::bitset <int(1e6 + 5)> lazy;
	std::function <T(T, T)> decide_fun;
	std::function <T(T, T)> update_fun;

	inline int left(int pos){
		return 2*pos + 1;
	}

	inline int right(int pos){
		return 2*pos + 2;
	}

	inline int mid(int l, int r){
		return (l + ((r-l) >> 1));
	}

public:

	SegmentTree(){}

	SegmentTree(int size_of_array, std::function <T(T, T)> decide_fun, std::function <T(T, T)> update_fun, T default_return){

		// size_of_array: size of array on which want to build tree
		// fun: funtion min, max, addition etc
		// default_retrun: default return when argument false in queary function


		/* 

		SegmentTree <int> seg(n, __min, INT_MAX);
		
		where __min is 

		T __min(T a, T b){
			return std::min(a, b);
		}
		
		seg.build(arr);
		arr is array -> you want to build tree

		*/


		this -> arr_size = size_of_array;
		seg.resize(4*arr_size + 5);
		update_seg.resize(4*arr_size + 5);
		lazy.reset()

		this -> update_fun = update_fun;
		this -> decide_fun = decide_fun;
		this -> default_return = default_return;
	}

	void build(std::vector<T> &a){

		// it will build segment tree 

		build(a, 0, arr_size-1, 0);
	}

	void build(std::vector<T> &a, int l, int r, int pos){
		if(l == r){
			seg[pos] = a[r];
			return;
		}

		int m = mid(l, r);

		build(a, l, m, left(pos));
		build(a, m+1, r, right(pos));

		seg[pos] = decide_fun(seg[left(pos)], seg[right(pos)]);
	}

	T query(int l, int r){
		return query(l, r, 0, arr_size-1, 0);
	}

	T query(int ql, int qr, int l, int r, int pos){

		if(qr < l or r < ql){
			return default_return;
		}

		if(ql <= l and r <= qr){
			return seg[pos];
		}

		int m = mid(l, r);
		return fun(query(ql, qr, l, m, left(pos)), query(ql, qr, m+1, r, right(pos)));
	}

	void update(int l, int r, int value){
		update(l, r, 0, arr_size-1, 0, value);
	}

	void update(int loc, T value){
		update(loc, loc, 0, arr_size-1, 0, value);
	}

	void update(int ul, int ur, int l, int r, int pos, T value){
		
		if(l > r)
			return;

		if(lazy[pos]){
			
			seg[pos] = fun(seg[pos], update_seg[pos]);
			lazy[pos] = 0;

			if(l != r){
				lazy[left(pos)] = 1;
				lazy[right(pos)] = 1;
				update_seg[left(pos)] = update_fun(update_seg[pos], value);
				update_seg[right(pos)] = update_fun(update_seg[pos], value);
			}

		}

		if(l == r){
			seg[pos] = value;
			return; 
		}

		int m = mid(l, r);

		if(loc <= m){
			update(l, m, loc, left(pos), value);
			seg[pos] = fun(seg[left(pos)], seg[right(pos)]);
		}else{	
			update(m+1, r, loc, right(pos), value);
			seg[pos] = fun(seg[left(pos)], seg[right(pos)]);
		}

	}

	void print(){
		for(int i = 0; i < seg.size(); ++i)
			cout << i  << " " << seg[i] << "\n";
	}

};

int main(){

	return 0;
}