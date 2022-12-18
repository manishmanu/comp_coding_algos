#include <iostream>

template <typename T>
class MyUniquePtr{
public:
    // Default constructor.
    MyUniquePtr(): ptr_(nullptr){}

    // Constructor.
    MyUniquePtr(T* ptr): ptr_(ptr){}

    // Copy Constructor.
    MyUniquePtr(const MyUniquePtr& other) = delete;

    // Assignment operator.
    MyUniquePtr& operator=(const MyUniquePtr& other) = delete;

    // Move constructor.
    MyUniquePtr(MyUniquePtr&& dying_obj){
        ptr_ = dying_obj.ptr_;
        dying_obj.ptr_ = nullptr;
    }

    // Move assignment operator.
    MyUniquePtr& operator=(MyUniquePtr&& dying_obj){
        // same unique_ptr is passed for move assignment. Hence ignore.
        if(ptr_ == dying_obj.ptr_){
            return *this;
        }

        __cleanup__();
        ptr_ = dying_obj.ptr_;
        dying_obj.ptr_ = nullptr;
        return *this;
    }

    // Destructor.
    ~MyUniquePtr(){
        __cleanup__();
    }

    // Overload -> operator.
    T* operator->() const{
        return ptr_;
    }

    // Overload * operator.
    T& operator*() const{
        return *ptr_;
    }

    // Get ptr.
    T* get_ptr() const{
        return ptr_;
    }

private:
    T* ptr_;

    void __cleanup__(){
        if(ptr_){
            delete ptr_;
            ptr_ = nullptr;
        }
    }
};

int main(){
    // Test default constructor.
    MyUniquePtr<int> p;
    std::cout << p.get_ptr() << std::endl; /* 0 */

    // Test normal constructor.
    MyUniquePtr<int> q(new int(5));
    std::cout << q.get_ptr() << std::endl; /* non-zero */
    std::cout << *q << std::endl; /* 5 */

    // Test copy constructor.
    // MyUniquePtr<int> r(q); //should throw error

    // Test move constructor.
    MyUniquePtr<int> s = std::move(q);
    std::cout << s.get_ptr() << std::endl; /* should match with previous q ptr*/
    std::cout << q.get_ptr() << std::endl; /* 0 */
    std::cout << *s << std::endl; /* 5 */

    // Test move assignment operator.
    MyUniquePtr<int> t(new int(10));
    s = std::move(t);
    std::cout << t.get_ptr() << std::endl; /* 0 */
    std::cout << *s << std::endl; /* 10 */
    std::cout << s.get_ptr() << std::endl; /* non-zero */

    // Test passing same unique_ptr to move assignment
    s = std::move(s);
    std::cout << s.get_ptr() << std::endl; /* should match previous s ptr */
    std::cout << *s << std::endl; /* 10 */

    // Test copy assignment.
    // MyUniquePtr<int> u(new int(15));
    // s = u; // should throw error
}