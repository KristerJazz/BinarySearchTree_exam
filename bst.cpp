#include <iostream>
#include <memory>
#include <vector>


template <typename key_type, typename value_type>
struct Node{
	key_type key{};
	value_type value{};

	std::unique_ptr<Node> left = nullptr;
	std::unique_ptr<Node> right = nullptr;

	Node* parent = nullptr;
	
	Node() noexcept = default;
	Node(const key_type k, value_type v): key{k}, value{v}{}
	Node(const key_type k, value_type v, Node* p): key{k}, value{v}, parent{p}{}

};

template < typename key_type, typename value_type>
class BSTiterator {
	private:
		using node = struct Node<key_type, value_type>;
		node *current;

	public:
		explicit BSTiterator(node *n) : current{n}{}

		using iterator_category = std::forward_iterator_tag;
		node& operator*() {return *current;}
		node* operator->() const {return current;}

		//PRE INCREMENT
		/*
		BSTiterator& operator++() noexcept {
			if(current->right){
				current = current->right
			}
			else{
				current = current->parent
			}
			return *this;
		}
		*/
		
};


	
template < typename key_type, typename value_type, typename cmp = std::less<key_type> >
class BST{
	using node = struct Node<key_type, value_type>;
	std::unique_ptr<node> root{};
	cmp lesser;

	private:
		//Some less important private variables
		int tree_size;
		std::vector<int> keylist;

	public:
		BST() noexcept = default;
		//BST(BST&& b) noexcept = default;
		//insert more constructor codes//

		/////////////////////ITERATOR//////////////
		using iterator = class BSTiterator<key_type, value_type>;
		using const_iterator = class BSTiterator<const key_type, value_type>;

		iterator begin() noexcept {
			node* tmp = root.get();
			if(!tmp) return iterator{nullptr};

			while (tmp->left){
				tmp = tmp->left.get();
			}
			std::cout<< tmp << std::endl;
			return iterator{tmp};
		}
		
		iterator end(){ return iterator{nullptr};}

		//const_iterator begin const;
		//const_iterator end const;

		//const_iterator cbegin const;
		//const_iterator cend() const;

		//Auxillary functions
		void print();
		void clear();
		void balance();


		//'INSERT' FUNCTION
		std::pair<iterator, bool> insert(const std::pair<const key_type, value_type>& x){
			bool is_added = false;
			node* itr = root.get();

			//if key in key_list find() itr
			//return std::pair<itr, false>;
			if (!root.get()){
				std::cout<<"Adding the first root"<<std::endl;
				root.reset(new node(x.first, x.second));
				is_added = true;
				std::pair<iterator, bool> result(iterator(root.get()), is_added);
				return result;
			}

			std::cout<<"Let's see where to put it"<<std::endl;
			while(itr){
				if (lesser(x.first, itr->key)){
					if(itr->left){
						itr = itr->left.get();
					}
					else{
						//std::cout<<x.second<<std::endl;
						itr->left.reset(new node(x.first, x.second, itr));
						itr = itr->left.get();
						break;
					}
				}

				else{
					if(itr->right){
						itr = itr->right.get();
					}
					else{
						itr->right.reset(new node(x.first, x.second, itr));
						itr = itr->right.get();
						break;
					}

				}
			}
			std::pair<iterator, bool> result(iterator(itr), is_added);
			return result;
		}

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
		value_type& operator[](const key_type& x){
		
		}
		value_type& operator[](key_type&& x);
};

int main(){
	BST<int, char> tree;
	tree.insert({5,4});
	tree.insert({2,1});
	tree.insert({3,5});
	tree.insert({1,4});
	auto first = tree.begin();
	std::cout << first->key <<std::endl;
	//std::cout<< tree[2] <<std::endl;
}
