#include <iostream>
#include <utility>
using namespace std;

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
    T* operator->(){
        return ptr_;
    }

    // Overload * operator.
    T& operator*(){
        return *ptr_;
    }

    // Get ptr.
    T* get_ptr(){
        return ptr_;
    }

    // Get ref count.
    uint32_t get_ref_count(){
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
    cout << p.get_ref_count() << endl; /* 0 */
    cout << p.get_ptr() << endl; /* 0 */

    // Test constructor.
    MySharedPtr<int> q(new int(3));
    cout << q.get_ref_count() << endl; /* 1 */
    cout << q.get_ptr() << endl; /* non-zero */

    // Test copy constructor.
    MySharedPtr<int> r = q;
    cout << q.get_ref_count() << endl; /* 2 */
    cout << r.get_ref_count() << endl; /* 2 */

    // Test assign operator.
    r = p;
    cout << r.get_ref_count() << endl; /* 0 */
    cout << r.get_ptr() << endl; /* 0 */
    cout << q.get_ref_count() << endl; /* 1 */

    // Test move contructor.
    MySharedPtr<int> s = move(q);
    cout << s.get_ref_count() << endl; /* 1 */
    cout << s.get_ptr() << endl; /* should match with previous q ptr */
    cout << q.get_ptr() << endl; /* 0 */
    cout << q.get_ref_count() << endl;

    // Test move assignment operator.
    MySharedPtr<int> t(new int(3));
    cout << t.get_ptr() << endl; /* non-zero */
    t = move(s);
    cout << t.get_ptr() << endl; /* should match with previous q ptr */
    cout << s.get_ptr() << endl; /* 0 */
}
