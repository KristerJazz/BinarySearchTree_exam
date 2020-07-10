#include <iostream>
#include <memory>
#include <vector>
#include <math.h>
#include <algorithm>
#include <random>
#include <map>
#include <chrono>

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
		key_type& operator*() {return current->key;}
		node* operator->() const {return current;}


		//PRE INCREMENT
		BSTiterator& operator++() noexcept{
			node* itr = current;
			if(itr->right){
				itr = itr->right.get();
				while(itr->left) itr = itr->left.get();
				current = itr;
			}
			else{
				itr = current->parent;
				while(itr and current == itr->right.get()){
						current = itr;
						itr = itr->parent;
				}
				current = itr;
			}
			return *this;
		}

		BSTiterator operator++(int) noexcept{
			BSTiterator itr{*this};
			++(*this);

			return itr;
		}
		friend bool operator==(const BSTiterator& a, const BSTiterator& b){
			return a.current==b.current;
		}
		friend bool operator!=(const BSTiterator& a, const BSTiterator& b){
			return a.current!=b.current;
		}
		
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
		//COPY
		BST(const BST &other_tree);
		//copy-assignment
		BST& operator= (const BST &other_tree){
			this->clear();
			auto tmp= other_tree;
			(*this) = std::move(tmp);

			return *this;
		}
		//////////////////////MOVE////////////////
  		BST(BST&& other_tree) noexcept = default;
		//List(const List& l);
		//List& operator=(const List& l);


		/*
		BST ( BST&& other_tree ) : root{ std::move( other_tree.root ) },
			    tail{ std::move( T_other.tail ) } {}

		/// move-assignment operator
		Tree& operator= ( Tree&& T_other ) {

		root = std::move( T_other.root );
			tail = std::move( T_other.tail );

			return *this;
			}
		*/
		/////////////////////ITERATOR//////////////
		using iterator = class BSTiterator<key_type, value_type>;
		using const_iterator = class BSTiterator<const key_type, value_type>;

		iterator begin() noexcept {
			node* tmp = root.get();
			if(!tmp) return iterator{nullptr};

			while (tmp->left){
				tmp = tmp->left.get();
			}
			return iterator{tmp};
		}
		//const_iterator begin	()
		//const_iterator cbegin const;
		iterator end(){ return iterator{nullptr};}
		//const_iterator end() { return const_iterator{nullptr};}

		const_iterator cend() { return const_iterator{nullptr};}

		//Auxillary functions
		
		void print();
		void clear(){ root.reset();}
		int size(){
			iterator itr = begin();
			iterator stop = end();
			int count = 0;
			while(itr!=stop){
				++count;
				++itr;
			}
			return count;
		}
		//using ex = struct MyExceptions();
		void balance(){
			//if (!root.get()) throw ex{"WATCH OUT! Empty tree cannot be balanced"};
			std::vector<node*> nodes;
			iterator itr = begin();
			iterator stop = end();
			while(itr!=stop){
				nodes.push_back(new node{itr->key, itr->value});
				++itr;
			}
			clear();

			for (unsigned int i=0; i<nodes.size(); i++) std::cout<<nodes[i]->key<<" ";
			std::cout<<std::endl;

			int bins = log2(nodes.size())/2+1;
			int div = nodes.size()/(2*bins);
			int root_id = nodes.size()/2;
			
			//root at midpoint
			insert({nodes[root_id]->key, nodes[root_id]->value});
			for(int i=1; i<div; i++){
				insert({nodes[root_id+bins*i]->key, nodes[root_id+bins*i]->value});
				insert({nodes[root_id-bins*i]->key, nodes[root_id-bins*i]->value});
			}
			insert({nodes[root_id-div*bins]->key, nodes[root_id-div*bins]->value});
			if (root_id+div*bins < int(nodes.size())) insert({nodes[root_id+div*bins]->key, nodes[root_id+div*bins]->value});

			for (unsigned int i=0; i<nodes.size(); i++) insert({nodes[i]->key, nodes[i]->value});

		}


		//'INSERT' FUNCTION
		//std::pair<iterator, bool> insert(const pair_type& x);
		std::pair<iterator, bool> insert(std::pair<const key_type, value_type>&& x){
			bool is_added = false;
			node* itr = root.get();
			if (!root.get()){
				root.reset(new node(x.first, x.second));
				is_added = true;
				std::pair<iterator, bool> result(iterator(root.get()), is_added);
				return result;
			}

			while(itr){
				if (x.first!=itr->key){
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
				else{ 
					break;
				}
			}
			std::pair<iterator, bool> result(iterator(itr), is_added);
			return result;
		}

		iterator find(const key_type& x){
			node* itr = root.get();
			//if(itr->key == x) return 
			while(itr->key != x){
				if(lesser(x, itr->key)){
					itr = itr->left.get();
				}
				else{
					itr = itr->right.get();
				}
			}

			if(!itr) std::cout<<"Key not found"<<std::endl;
			return iterator(itr);
		}

		//const_iterator find(const key_type& x) const{
		//	return const_iterator{find(x)};
		//};
		
		//INDEXING OPERATORS
		/*
		value_type& operator[](const key_type& x){
			iterator found{find(x)}; 
			value_type random;
			if(found != cend()) return found->value;
			else return random;

		}
		*/
		value_type& operator[](key_type&& x){
			iterator found = find(x); 
			if(found != end()) return found->key;
			else {
				auto itr = insert({x,0});
				//std::cout<<itr.first<<std::endl;
				//return itr.first;
			}
		}

		friend std::ostream& operator<<(std::ostream& os, BST<key_type, value_type, cmp>& x){
			iterator itr = x.begin();
			if(itr.operator->()){
				iterator stop = x.end(); 
				while (itr != stop){
					os << itr->key<< ": " << itr->value << std::endl;
					++itr;
				}
			}
			else{
				os << "Tree is empty" << std::endl;
			}
			return os;
		}

};

struct MyExceptions {
	std::string message;
	MyExceptions(const std::string &s): message{s} {};
};

int main(int argc, char **argv){
	/* TESTING BST FUNCTIONS

	std::cout<<"Testing binary search tree basic functions"<< std::endl;

	std::cout<<"Initializing tree..."<< std::endl;
	BST<int, int> tree;

	int N=100;
	std::cout<<"Inserting "<< N<< " random key value pairs"<< std::endl;
	for (int i=0; i<N; i++) tree.insert({i,5});
	auto a = std::make_pair(101,101);
	tree.insert(a);
	std::cout<<"Tree size after multiple insert function is " << tree.size()<<std::endl;
	//tree.balance();
	//std::cout<<tree<<std::endl;


	*/ // <---- Move this line to silence this testing section or press dd15jp

	int N = 5;
	/* BENCHMARKING CODES 
	*/
	//STRAIGHT LINE
	BST<int, int> tree;

	std::vector<int> digits{};
	for(int i=0; i<N; i++) digits.push_back(i);

	for(int i=0; i<N; i++) tree.insert({digits[i],digits[i]});//std::cout<<digits[i]<< " ";
	//std::cout<<tree<<std::endl;
	//straight timing
	double total_elapsed; 
	for(int i=0; i<N; i++){
		auto t0 = std::chrono::high_resolution_clock::now();
		tree.find(i);
		auto t1 = std::chrono::high_resolution_clock::now();
		auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(t1-t0);
		total_elapsed+=elapsed.count();
	}
	std::cout << "Total elapsed " << total_elapsed<< " [nanoseconds]" << std::endl;
	
	//RANDOM ORDER	
	//BST<int, int> random_tree;
	tree.clear();
	//randomized order
	std::random_device rd;
    std::mt19937 g(rd());
	std::shuffle(digits.begin(), digits.end(),g);
	for(int i=0; i<N; i++) tree.insert({digits[i],digits[i]});//std::cout<<digits[i]<< " ";
	for(int i=0; i<N; i++) std::cout<<digits[i]<< " ";
	//std::cout<<random_tree<<std::endl;

	//random : timing
	total_elapsed=0;
	for(int i=0; i<N; i++){
		auto t0 = std::chrono::high_resolution_clock::now();
		tree.find(i);
		auto t1 = std::chrono::high_resolution_clock::now();
		auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(t1-t0);
		total_elapsed+=elapsed.count();
	}
	std::cout << "Total elapsed " << total_elapsed<< " [nanoseconds]" << std::endl;
	
	//BALANCE
	tree.balance();

	total_elapsed=0;
	for(int i=0; i<N; i++){
		auto t0 = std::chrono::high_resolution_clock::now();
		tree.find(i);
		auto t1 = std::chrono::high_resolution_clock::now();
		auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(t1-t0);
		total_elapsed+=elapsed.count();
	}
	std::cout << "Total elapsed " << total_elapsed<< " [nanoseconds]" << std::endl;
	


	//MAP
	std::map<int,int> std_map{};
	for(int i=0; i<N; i++) std::cout<<digits[i]<< " ";
	std::cout<<std::endl;

	return 0;
}
