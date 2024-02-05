
#include <iostream>
#include <memory>
#include <vector>
#include <map>
#include <array>
#include <type_traits>
#include <list>

static constexpr uint8_t kSize = 10;

template <class T>
struct pool_allocator {
    typedef T value_type;

    static int pos;
    static constexpr int size = sizeof(T) * kSize;
    static uint8_t data[size];
    static constexpr int alloc_size_ = 1;
    static constexpr bool allow_extra_dynamic_alloc_ = true;

    pool_allocator() = default;
    ~pool_allocator() { pos = 0; }

    template <class U> pool_allocator  (const pool_allocator <U>&) noexcept {}

    T* allocate (std::size_t n_elem_of_T) {
        if (n_elem_of_T != alloc_size_) {
            std::cerr << "Wrong alloc size=" << n_elem_of_T << " elem; expected=" << alloc_size_ << " elem." << std::endl;
            throw std::bad_alloc();
        }
        if ((pos + n_elem_of_T) * sizeof(T) > size){
            if (!allow_extra_dynamic_alloc_) {
                std::cerr << "Allocator overflow (max alloc size=" << size << " bytes); required=" 
                << (pos + n_elem_of_T) * sizeof(T) << " bytes" << std::endl;
                throw std::bad_alloc();
            }
            std::cout << "extra allocation from heap" << std::endl;
            return reinterpret_cast<T*>(::operator new (n_elem_of_T * sizeof(T)));
        }
        
        int cur = pos;
        pos += n_elem_of_T;
        return reinterpret_cast<T*>(data) + cur;
    }

    void deallocate (T*, std::size_t /*n*/) {
        // std::cout << "deallocate() n=" << n << std::endl;
    }

    template< class U >
    struct rebind
    {
        typedef pool_allocator<U> other;
    };
};

template <typename T>
uint8_t pool_allocator<T>::data[size];

template <typename T>
int pool_allocator<T>::pos = 0;


template <class T, class U>
constexpr bool operator== (const pool_allocator<T>&, const pool_allocator<U>&) noexcept
{
    return true;
}

template <class T, class U>
constexpr bool operator!= (const pool_allocator<T>&, const pool_allocator<U>&) noexcept
{
    return false;
}


template <typename T, typename Alloc>
class MyList
{
    struct Node
    {
        Node* next;
        T val;
    };

    class iterator {
        private:
        Node* node;
    public:
        iterator(Node* arg) noexcept : node{arg} {}

        iterator& operator=(Node* arg) {
            node = arg;
            return *this;
        }

        iterator operator++() {
            if (node)
                node = node->next;
            return *this;
        }

        iterator operator++(int) {
            iterator iter = *this;
            ++(*this);
            return iter;
        }

        bool operator==(const iterator& other) {
            return (node == other.node);
        }

        bool operator!=(const iterator& other) {
            return (node != other.node);
        }

        T& operator*() {
            return node->val;
        }
    };
    public:
    iterator begin() {
        return iterator{head};
    }

    iterator end() {
        return iterator{nullptr};
    }

    void push_back(const T& val)
    {
        static typename Alloc::template rebind<Node>::other nodeAlloc;
        Node* newNode = nodeAlloc.allocate(1);

        newNode->val = val;
        newNode->next = nullptr;
        if (!head) {
            head = newNode;
            tail = head;
            return;
        }
        tail->next = newNode;
        tail = newNode;
        size_++;
    }

    size_t size() { return size_; }
    bool empty() { return size_ == 0; }

private:
    Node* head = nullptr;
    Node* tail = head;
    size_t size_{};
};

int main(int, char *[]) {

    // Usual map:
    std::map<int, int> usual_map;
    for (int i = 0; i < kSize; i++) {
        if (i == 0) {
            usual_map[i] = 1;
            continue;
        }
        usual_map[i] = i * usual_map[i - 1];
    }
    std::cout << "usual_map: ";
    for (int i = 0; i < kSize; i++) {
        std::cout << i << " " << usual_map[i] << "  |  ";
    }
    std::cout << std::endl;

    // Custom allocator map:
    std::map<int, int, std::less<int>, pool_allocator<std::pair<const int, int>>> 
        custom_allocator_map;
    for (int i = 0; i < kSize; i++) {
        if (i == 0) {
            custom_allocator_map[i] = 1;
            continue;
        }
        custom_allocator_map[i] = i * custom_allocator_map[i - 1];
    }
    std::cout << "custom_allocator_map: ";
    for (int i = 0; i < kSize; i++) {
        std::cout << i << " " << custom_allocator_map[i] << "  |  ";
    }
    std::cout << std::endl;

    // Custom list:
    MyList<int, std::allocator<int>> my_list;
    int prev = 1;
    for (int i = 0; i < kSize; i++) {
        if (i == 0) {
            my_list.push_back(1);
            continue;
        }
        my_list.push_back(i * prev);
        prev = i * prev;
    }
    std::cout << "my_list: ";
    for (auto& elem: my_list) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;

    // Custom allocator custom list:
    MyList<int, pool_allocator<int>> custom_allocator_my_list;
    int prev_ca = 1;
    for (int i = 0; i < kSize; i++) {
        if (i == 0) {
            custom_allocator_my_list.push_back(1);
            continue;
        }
        custom_allocator_my_list.push_back(i * prev_ca);
        prev_ca = i * prev_ca;
    }
    std::cout << "custom_allocator_my_list: ";
    for (auto& elem: custom_allocator_my_list) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;


	return 0;
}
