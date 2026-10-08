/* -----------------------------------------------------------------------
 * GGPO.net (http://ggpo.net)  -  Copyright 2009 GroundStorm Studios, LLC.
 *
 * Use of this software is governed by the MIT license that can be found
 * in the LICENSE file.
 */

#ifndef _RING_BUFFER_H
#define _RING_BUFFER_H

#include <types.h>

template<class T, int N> class RingBuffer
{
public:
   RingBuffer<T, N>() : 
      _head(0),
      _tail(0),
      _size(0) {
  } 

   T &front() {
      if (_size == 0) {
         return _elements[0];
      }
      return _elements[_tail];
   }
   
   T &item(int i) {
      if (i < 0 || i >= _size) {
         return _elements[_tail];
      }
      return _elements[(_tail + i) % N];
   }

   void pop() {
      if (_size <= 0) {
         return;
      }
      _tail = (_tail + 1) % N;
      _size--;
   }

   void push(const T &t) {
      if (_size >= N) {
         _tail = (_tail + 1) % N;
         _size--;
      }
      _elements[_head] = t;
      _head = (_head + 1) % N;
      _size++;
   }

   int size() {
      return _size;
   }

   bool empty() {
      return _size == 0;
   }

protected:
   T        _elements[N];
   int      _head;
   int      _tail;
   int      _size;
};

#endif
