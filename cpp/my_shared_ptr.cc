#include <iostream>

// Reference:
// https://medium.com/analytics-vidhya/c-shared-ptr-and-how-to-write-your-own-d0d385c118ad

template <typename T>
class MySharedPtr{
public:
    // Default constructor.
    MySharedPtr(): ptr_(nullptr), ref_count_(new uint32_t(0)){}

    // Constructor.
    MySharedPtr(T* ptr): ptr_(ptr), ref_count_(new uint32_t(1)){}

    // Copy constructor.
    MySharedPtr(const MySharedPtr<T>& other){
        ptr_ = other.ptr_;
        ref_count_ = other.ref_count_;
        if(ptr_){
            (*ref_count_)++;
        }
    }

    // Copy assignment.
    MySharedPtr& operator=(const MySharedPtr<T>& other){
        // same shared_ptr is passed to copy assignment. Hence ignore.
        if(ptr_ == other.ptr_){
            return *this;
        }

        __cleanup__();

        ptr_ = other.ptr_;
        ref_count_ = other.ref_count_;
        if(ptr_){
            (*ref_count_)++;
        }
        return *this;
    }

    // Move constructor.
    MySharedPtr(MySharedPtr<T>&& dying_obj){
        ptr_ = dying_obj.ptr_;
        ref_count_ = dying_obj.ref_count_;

        dying_obj.ptr_ = nullptr;
        dying_obj.ref_count_ = nullptr;
    }

    // Move assignment.
    MySharedPtr& operator=(MySharedPtr&& dying_obj){
        // same shared_ptr is passed to move assignment. Hence ignore.
        if(ptr_ == dying_obj.ptr_){
            return *this;
        }

        __cleanup__();

        ptr_ = dying_obj.ptr_;
        ref_count_ = dying_obj.ref_count_;

        dying_obj.ptr_ = nullptr;
        dying_obj.ref_count_ = nullptr;

        return *this;
    }

    // destructor.
    ~MySharedPtr(){
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

    // Get ref count.
    uint32_t get_ref_count() const{
        return ref_count_ ? *ref_count_ : 0;
    }
    
private:
    void __cleanup__(){
        if(ptr_){
            (*ref_count_)--;
            if(*ref_count_ == 0){
                delete ptr_;
                delete ref_count_;
            }
        }
    }

    T *ptr_;
    uint32_t *ref_count_;
};

int main(){
    // Test default constructor.
    MySharedPtr<int> p;
    std::cout << p.get_ref_count() << std::endl; /* 0 */
    std::cout << p.get_ptr() << std::endl; /* 0 */

    // Test constructor.
    MySharedPtr<int> q(new int(3));
    std::cout << q.get_ref_count() << std::endl; /* 1 */
    std::cout << q.get_ptr() << std::endl; /* non-zero */

    // Test copy constructor.
    MySharedPtr<int> r = q;
    std::cout << q.get_ref_count() << std::endl; /* 2 */
    std::cout << r.get_ref_count() << std::endl; /* 2 */

    // Test assign operator.
    r = p;
    std::cout << r.get_ref_count() << std::endl; /* 0 */
    std::cout << r.get_ptr() << std::endl; /* 0 */
    std::cout << q.get_ref_count() << std::endl; /* 1 */

    // Test move contructor.
    MySharedPtr<int> s = std::move(q);
    std::cout << s.get_ref_count() << std::endl; /* 1 */
    std::cout << s.get_ptr() << std::endl; /* should match with previous q ptr */
    std::cout << q.get_ptr() << std::endl; /* 0 */
    std::cout << q.get_ref_count() << std::endl; /* 0 */

    // Test move assignment operator.
    MySharedPtr<int> t(new int(3));
    std::cout << t.get_ptr() << std::endl; /* non-zero */
    t = std::move(s);
    std::cout << t.get_ptr() << std::endl; /* should match with previous q ptr */
    std::cout << s.get_ptr() << std::endl; /* 0 */

    // Test passing same shared_ptr to move assignment
    MySharedPtr<int> u(new int(5));
    u = std::move(u);
    std::cout << u.get_ref_count() << std::endl; /* 1 */

    // Test passing same shared_ptr to copy assignment
    MySharedPtr<int> v(new int(5));
    v = v;
    std::cout << v.get_ref_count() << std::endl; /* 1 */
}
