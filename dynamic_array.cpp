#include <iostream>
#include <cstddef>  // std::size_t
#include <utility> // std::move

template <typename T>
class Vector{
    private:
    T* data;
    std::size_t size_;
    std::size_t capacity_;
    
    public:
    
    std::size_t size() const {return size_;};
    std::size_t capacity() const {return capacity_;};
    bool empty() const {return size_ == 0;};
    
    void reallocate()
    {
        capacity_ *= 2;
        T* new_data = new T[capacity_];
        
        for(std::size_t i = 0; i < size_; i++)
        {
            new_data[i] = std::move(data[i]);
        }
        
        delete[] data;
        data = new_data;
    };
    
    Vector(std::size_t init_capacity = 4)
    {
        size_ = 0;
        capacity_ = init_capacity;
        data = new T[capacity_];
    };
    
    ~Vector()
    {
        delete[] data;
    };
    
    T& operator[](std::size_t index) { 
        return data[index]; 
    }
    const T& operator[](std::size_t index) const { 
        return data[index]; 
    }
    
    void push_back(const T& value)
    {
        if (size_ == capacity_) reallocate();
        data[size_] = value;
        ++size_;
    }
    
    void push_back(T&& value)
    {
        if (size_ == capacity_) reallocate();
        data[size_] = value;
        ++size_;
    }
    
    void pop_back()
    {
        --size_;
    }
    
    void insert(std::size_t index, const T& value)
    {
        if(index > size_) return;
        
        if(size_ == capacity_) reallocate();
        
        for(std::size_t i = size_; i > index; i--)
        {
            data[i] = std::move(data[i-1]);
        }
        data[index] = value;
        ++size_;
    }
    
    void erase(std::size_t index, const T& value)
    {
        if (index > size_) return;
        
        for(std::size_t i = index; i < size_ - 1; ++i)
        {
            data[i] = std::move(data[i+1]);
        }
        --size_;
    }
    
    void clear()
    {
        size_ = 0;
    }
    
    // copy constructor
    Vector(const Vector& other)
        :(size_(other.size_), capacity_(other.capacity_))
    {
        T* data = new T*[capacity_];
        
        for(std::size_t i = 0; i < size_t; ++i)
        {
            data[i] = other.data[i];
        }
        
    }
};

int main()
{
    Vector<int> v;
    v.push_back(10);
    v.push_back(20);
    v.push_back(20);
    v.push_back(20);
    v.push_back(20);
    v.push_back(20);
    
    for(int i = 0; i < v.size(); i++)
    {
        std::cout << v[i] << std::endl;
    }
    v.insert(1, 40);
    for(int i = 0; i < v.size(); i++)
    {
        std::cout << v[i] << std::endl;
    }
    
    std::cout << "capacity of v: " << v.capacity() << std::endl;
    std::cout << v.size();
    return 0;
}
