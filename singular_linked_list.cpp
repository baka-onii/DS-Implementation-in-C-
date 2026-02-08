#include <iostream>

template <typename T>
class SinglyLinkedList
{
private:
	struct Node {
		T data;
		Node* next;
		Node(const T& value): data(value), next(nullptr) {}
	};
	Node* head;
	Node* tail;
	std::size_t size_;


public:
	SinglyLinkedList():
		head(nullptr), tail(nullptr), size_(0) {};
		
	~SinglyLinkedList(){
	    Node* curr = head;
	    while(curr != nullptr)
	    {
	        Node* next = curr->next;
	        delete curr;
	        curr = next;
	    }
	    tail = nullptr;
	};

	std::size_t size() const {
		return size_;
	};
	bool empty() const {
		return head == nullptr;
	}
	
	// Copy Constructor
    SinglyLinkedList(const SinglyLinkedList<T>& other)
    : head(nullptr), tail(nullptr), size_(0)
    {
        Node* curr = other.head;
        while (curr != nullptr) {
            // reuse our push_back to keep logic in one place
            push_back(curr->data);
            curr = curr->next;
        }
    }

    // Copy Assignment
    SinglyLinkedList<T>& operator=(const SinglyLinkedList<T>& other)
    {
        if (this == &other) {
            return *this;  // self-assignment guard
        }
    
        // 1) Clear current list
        Node* curr = head;
        while (curr != nullptr) {
            Node* next = curr->next;
            delete curr;
            curr = next;
        }
        head = tail = nullptr;
        size_ = 0;
    
        // 2) Deep-copy from other (reuse logic)
        curr = other.head;
        while (curr != nullptr) {
            push_back(curr->data);
            curr = curr->next;
        }
    
        return *this;
    }
	void push_front(const T& value)
	{
	    if (head == nullptr) // for empty list
	    {
			Node* node = new Node(value);
			node->next = head;
			head = tail = node;
	    }
	    else{
			Node* node = new Node(value);
			node->next = head;
			head = node;
	    }
	    ++size_;
	}

	void pop_front()
	{
		if (head == nullptr) return;
		
		if (head->next == nullptr) // for only 1 element
		{
    		Node* node = head; // node to be freed
    		head = tail = node->next;
    		delete node;
		}
		else{
    		Node* node = head; // node to be freed
    		head = node->next;
    		delete node;
		}
		--size_;
	}
	
	void push_back(const T& value)
	{
	    Node* node = new Node(value);
	    
	    if (head != nullptr) // for non empty list
	    {
    	    head = tail = node;
	    }
	    else{
    	    tail->next = node;
    	    tail = node;
	    }
	    ++size_;
	}
	
	void pop_back()
	{
	    if (head == nullptr) return;
	    
	    if(head == tail) // only 1 element
	    {
	        delete head;
	        head = tail = nullptr;
	    }
	    else{
	        // find node before tail
            Node* prev = head;
            while (prev->next != tail) {
                prev = prev->next;
            }
            delete tail;
            tail = prev;
            tail->next = nullptr;
	    }
	    --size_;
	}
	
	void insert_at(const T& value, std::size_t index)
	{
	    if (index > size_) return;
	    
	    if (index == 0)
	    {
	        push_front(value);
	        return;   
	    }
	    if (index == size_)
	    {
	        push_back(value);
	        return;
	    }
	    
	    Node* prev = head;
	    for (std::size_t i = 0; i < index-1; i++)
	    {
	        prev = prev->next;
	    }
	    Node* node = new Node(value);
	    node->next = prev->next;
	    prev->next = node;
	    ++size_;
	}
	void erase_at(std::size_t index)
	{
	    if (index >= size_) return;     

        if (index == 0) {               // erase head
            pop_front();
            return;
        }

        Node* prev = head;
        for (std::size_t i = 0; i < index - 1; ++i) {
            prev = prev->next;
        }
        Node* current = prev->next;     // node to delete
        prev->next = current->next;

        if (current == tail) {          // erased last element
            tail = prev;
        }

        delete current;
        --size_;
	}
	
	void const print(){
	    Node* curr = head;
	    std::cout << "SinglyLinkedList[";
	    while(curr != nullptr)
	    {
	        if(curr->next != nullptr)
    	        std::cout << curr->data << ", ";
    	    else
    	    {
    	        std::cout << curr->data;
    	    }
    	    curr = curr->next;
	    }
	    std::cout << "]" << std::endl;
	}
};

int main()
{
    SinglyLinkedList<int> list;
    std::cout << "Size of list: " << list.size() << std::endl;
    list.push_front(20);
    list.push_front(30);
    list.push_front(40);
    list.push_front(50);
    std::cout << "Size of list: " << list.size() << std::endl;
    list.pop_front();
    list.print();
    std::cout << "Size of list: " << list.size() << std::endl;
    
	return 0;
}
