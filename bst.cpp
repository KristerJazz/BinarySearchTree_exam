#include <iostream>
#include <memory>


template <typename key_type, typename value_type>
struct Node{
	key_type key{};
	value_type value{};

	std::unique_ptr<Node> left = nullptr;
	std::unique_ptr<Node> right = nullptr;

	Node* up = nullptr;
	
	Node() noexcept = default;
};

template < typename key_type, typename value_type, typename cmp = std::less<key_type> >
class BSTiterator {
	private:
		using node = struct Node<key_type, value_type>;
		node *current;
	public:
		BSTiterator() noexcept = default;
		BSTiterator(node n) : current(n){}

		//PRE INCREMENT
		/*
		BSTiterator<key_type, value_type, cmp>& operator++(){
			curr = cmp
		};
		*/
};


	
template < typename key_type, typename value_type, typename cmp = std::less<key_type> >
class BST{
	using node = struct Node<key_type, value_type>;
	std::unique_ptr<node> root;
	cmp lesser;

	private:
		//Some less important private variables
		int tree_size;

	public:
		BST() noexcept = default;
		//BST(BST&& b) noexcept = default;
		//insert more constructor codes//

				/////////////////////ITERATOR//////////////
		//template <typename I>
		//class __iterator;

		//using iterator = __iterator<key_type>;
		//using const_iterator = __iterator<const key_type>;
		using iterator = class BSTiterator<key_type, value_type, cmp>;
		
		//iterator begin() noexcept {};
		//iterator end();

		//const_iterator begin const;
		//const_iterator end const;

		//const_iterator cbegin const;
		//const_iterator cend() const;

		//Auxillary functions
		void print();
		void clear();
		void balance();


		//'INSERT' FUNCTION
		//std::pair<iterator, bool> insert(const std::pair<const key_type, value_type>& x);

		/*
		std::pair<iterator, bool> insert(const pair_type& x);
		std::pair<iterator, bool> insert(pair_type&& x);

		iterator begin();
		const_iterator cbegin() const;
		const_iterator begin() const;

		iterator end();
		const_iterator end() const;
		const_iterator cend() const;

		iterator find(const key_type& x);
		const_iterator find(const key_type& x) const;
		*/
		
		//INDEXING OPERATORS
		value_type& operator[](const key_type& x);
		value_type& operator[](key_type&& x);
};

/*
template < typename key_type, typename value_type, typename cmp = std::less<key_type> >
void BST<key_type,value_type,cmp>::clear()
{
	std::cout<<"Resetting the tree" << std::endl;	
}

*/
int main(){
	BST<int, char> tree;
}
