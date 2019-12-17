#ifndef QUEUE_H
#define QUEUE_H

template <typename T>
class Queue {
public:
   Queue() { m_add = m_remove = m_size = 0; }
   void enque( T* c ) {
      m_array[m_add] = c;
      m_add = (m_add + 1) % SIZE;
	  m_size++;
   }
   T* deque() {
      int temp = m_remove;
      m_remove = (m_remove + 1) % SIZE;
	  m_size--;
      return m_array[temp];
   }
   unsigned int size(){
	   return m_size;
   }
   unsigned int maxSize(){
	   return SIZE;
   }
private:
   enum { SIZE = 6 };
   T*  m_array[SIZE];
   int m_add, m_remove, m_size;
};

#endif