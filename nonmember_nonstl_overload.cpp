
#include <iostream> // cout, endl
#include <cstddef>  // size_t

// This class was provided by someone else. It is a container, and its
// author could have made it iterable, but failed to do so.
class STLUnawareContainer {
public:

  STLUnawareContainer(size_t s) : size_datum(s), data(new int[s]) {
    for (size_t n=0; n<size_datum; ++n)
      data[n] = n;
  }

  STLUnawareContainer(const STLUnawareContainer& other) : size_datum(other.size_datum), data(new int[other.size_datum]) {
    for (size_t n=0; n<size_datum; ++n) {
      data[n] = other.data[n];
    }
  }

  size_t size() const { return size_datum; }

  int&  operator[](size_t n) { return data[n]; }

private:
  size_t size_datum;
  int* data;
};


// So we hack up our own iterator
class SUC_iterator {
public:

  static SUC_iterator begin(STLUnawareContainer& s) {
    SUC_iterator it(s);
    it.pos = 0;
    return it;
  }

  static SUC_iterator end(STLUnawareContainer& s) {
    SUC_iterator it(s);
    it.pos = s.size();
    return it;
  }

  SUC_iterator(STLUnawareContainer& s) : suc(s), pos(0) { }

  SUC_iterator& operator++() { // prefix
    pos++; 
    return *this;
  }

  SUC_iterator operator++(int) { // postfix
    SUC_iterator result(*this);
    ++(*this);
    return result;
  }

  bool operator !=(const SUC_iterator& other) const { return pos != other.pos; }

  int& operator*() const { return suc[pos]; }

private:
  STLUnawareContainer& suc;
  size_t pos;
};

// By overloading begin and end, we can make STLUnawareContainer
// usable with the STL algorithms and range-based for loops.

///////////////////////////////////////////////////
// Your implementations of begin and end go here //
///////////////////////////////////////////////////

SUC_iterator begin(STLUnawareContainer& c){
  return SUC_iterator::begin(c);
}

SUC_iterator end(STLUnawareContainer& c){
  return SUC_iterator::end(c);
}



int main() {
  STLUnawareContainer suc(10);
  for (int x : suc)
    std::cout << x << std::endl;
}
