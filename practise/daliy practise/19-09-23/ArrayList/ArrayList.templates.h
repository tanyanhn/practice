#include "ArrayList.h"

namespace CRAZYFISH{

  template <class TYPE>
  ArrayList<TYPE>::ArrayList(int _s)
  {
    __data = new TYPE[_s];
    __length = _s;
  };

  template <class TYPE>
  ArrayList<TYPE>::ArrayList(int _s, TYPE _d)
  {
    __data = new TYPE[_s];
    __length = _s;
    for (int i = 0; i < __length; i++)
      __data[i] = _d;
  };

  template <class TYPE>
  int ArrayList<TYPE>::printArrayList()
  {
    std::cerr << "List all items:" << std::endl;
    for (int i = 0; i < __length; i++)
      std::cout << __data[i] << "\t";
    std::cout << std::endl;
    return 0;
  };

  template <class TYPE>
  ArrayList<TYPE>::~ArrayList()
  {
    if (__data != NULL)
      delete[] __data;
    __length = 0;
  };

  template <class TYPE>
  int ArrayList<TYPE>::find(TYPE _d)
  {
    int idx = -1;
    for (int i = 0; i < __length; i++)
      if (__data[i] == _d)
	idx = i;
    return idx;
  };

  template <class TYPE>
  int ArrayList<TYPE>::fast_find(TYPE _d)
  {
    /* int return_value; */
    /* return_value = __fast_find(_d, 0, __length - 1); */
    /* return return_value; */
    return __fast_find(_d, 0, __length - 1);
  };

  template <class TYPE>
  int ArrayList<TYPE>::__fast_find(TYPE _d, int _p, int _q)
  {
    if(_q - _p < 0)
      {
	return -1;
      }
    int mid_idx = floor( (_p + _q) / 2);
    TYPE relative_d = __data[mid_idx];
    if(_q - _p >= 1)
      {
	if(_d == relative_d)
	  {
	    return mid_idx;
	  }
	if(_d < relative_d)
	  {
	    return (__fast_find(_d, _p, mid_idx-1));
	  }
	if(_d > relative_d)
	  {
	    return (__fast_find(_d, mid_idx+1, _q));
	  }
      }
    if(_q - _p == 0)
      {
	if(_d == relative_d)
	  {
	    return _q;
	  }
	else
	  {
	    return -1;
	  }
      }
  };
	   
  template <class TYPE>
  int ArrayList<TYPE>::merge_sort()
  {
    __merge_sort(0, __length - 1);
    printArrayList();
  };

  template <class TYPE>
  int ArrayList<TYPE>::__merge_sort(int _p,
				    int _r)
  {
    if (_p < _r)
      {
	int q = (_p + _r)/2;
	__merge_sort(_p, q);
	__merge_sort(q + 1, _r);
	__merge(_p, q, _r);
      }
    return 0;
  };

  template <class TYPE>
  int ArrayList<TYPE>::__merge(int _p,
			       int _q,
			       int _r)
  {
    if (_q < _p || _r <= _q || _r <= _p)
      {
	std::cerr << "Error! wrong index ranges on __merge()" << _p << _q << _r
	        << std::endl;
	std::exit(-1);
      }
    int n1 = _q - _p +1;
    int n2 = _r - _q;
    TYPE *L = new TYPE[n1 + 1];
    TYPE *R = new TYPE[n2 + 1];
    for (int i = 0; i < n1; i++)
      L[i] = __data[_p + i];
    for (int i = 0; i < n2; i++)
      R[i] = __data[_q + 1 + i];
    L[n1] = R[n2] = std::numeric_limits<TYPE>::max();
    int i = 0, j = 0;
    for (int k = _p; k <= _r; k++)
      {
	if (L[i] <= R[j])
	  {
	    __data[k] = L[i];
	    i++;
	  }
	else
	  {
	    __data[k] = R[j];
	    j++;
	  }
      }
    return 0;
  };

  template <class TYPE>
  TYPE &ArrayList<TYPE>::operator[](int _i)
  {
    return __data[_i];
  };

  template <class TYPE>
  const TYPE& ArrayList<TYPE>::operator[](int _i) const
  {
    return __data[_i];
  };

  template <class TYPE>
  std::ostream& operator<<(std::ostream& os,
			  const ArrayList<TYPE>& _obj)
  {
    for (int i = 0; i < _obj.__length; i++)
      os << _obj.__data[i] << "\t";
    return os;
  };
};
