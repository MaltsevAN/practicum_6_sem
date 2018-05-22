#include <iostream>
#include <map>
#include <vector>
#include <set>

template <class T1, class T2>
class Bijection {
    std::map<T1, typename std::set<T2>::iterator> _data;
    typename std::set<T2> _image_set;

public:
    using image_type = T2;
    using prototype_type = T1;
    using reference_image = T2&;
    using reference_prototype = T1&;
    using const_reference_image = const T2&;
    using const_reference_prototype = const T1&;
    using data_type = std::map<T1, typename std::set<T2>::iterator>;
    using image_set_type = typename std::set<T2>;
    class Iterator {
        typename std::map<T1, typename std::set<T2>::iterator>::iterator _my_iterator;
    public:
        using iterator_type = typename std::map<T1, typename std::set<T2>::iterator>::iterator;
        explicit Iterator(iterator_type iterator): _my_iterator(iterator){ }
        std::pair<T1, T2> operator*(){
            return std::make_pair(_my_iterator->first, *(_my_iterator->second));
        }
        Iterator& operator++()
        {
            ++_my_iterator;
            return *this;
        }

        bool operator ==(const Iterator& other)
        {
            return _my_iterator == other._my_iterator;
        }
        bool operator !=(const Iterator& other)
        {
            return !(*this == other);
        }
    };

    Iterator begin(){
        return Iterator(_data.begin());
    }
    Iterator end(){
        return Iterator(_data.end());
    }
    explicit Bijection()
    {
        _data = data_type{};
        _image_set = image_set_type{};
    }
    void add(const_reference_prototype x, const_reference_image & y){
        if(_image_set.find(y) != _image_set.end()){
            return;
        }
        auto iter= _image_set.insert(y).first;
        _data[x] = iter;
    }
    Bijection<image_type , prototype_type > reverese() const
    {
        Bijection<image_type, prototype_type> res;
        for (auto &&item : _data) {
            res.add(*(item.second), item.first);
        }
        return res;
    };
    size_t size() const
    {
        return _data.size();
    }
    friend std::ostream &operator<<(std::ostream &os, Bijection &bijection) {
        os << "Size: " << bijection.size() << std::endl;
        if (bijection.size() != 0) {
            for (auto iterator = bijection.begin(); iterator != bijection.end(); ++iterator) {
                os << "prototype = " << (*iterator).first
                   << " image = " << (*iterator).second << std::endl;
            }
        }
        return  os;
    }
};

int main() {
    Bijection<int, std::string> bijection;
    bijection.add(1, "qwe");
    bijection.add(2, "qwe");
    bijection.add(1, "erty");
    bijection.add(2, "erty");
    bijection.add(23, "q");
    bijection.add(5, "w");
    bijection.add(6, "e");
    bijection.add(7, "et");
    std::cout << bijection;
    Bijection<std::string, int> bijection1 = bijection.reverese();
    std::cout << bijection1;
    return 0;
}