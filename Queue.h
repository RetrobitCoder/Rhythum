#ifndef queue_h
#define queue_h

template <typename T>
struct Node
{
  T object;
  struct Node* next;
};

template <typename T>
class Queue
{ 
  public:
    Queue<T>(){};
    ~Queue<T>() = default;

    // Get item at end of queue
    T& back()
    {
      return m_tail->object;
    }

    // Check if queue is empty
    bool empty()
    {
      return m_size == 0;
    }

    // Get item at front of queue
    T& front()
    {
      return m_head->object;  
    }

    // Get item from front of queue and remove it from queue
    T& pop()
    {
      struct Node<T> node;
      struct Node<T>* oldHead;
      
      node = *m_head;

      m_head = node.next;

      node.next = nullptr;
      
      m_size--;

      return node.object;
    }

    // @param Add item to queue
    void push(T item)
    {
      struct Node<T> node;
      node.next = nullptr;
      node.object = item;
  
      if(!m_head)
      {
        m_head = &node;
        m_tail = m_head->next;
      }
      else
      {
        *(m_tail->next) = node;
        m_tail = &node;
      }

      m_size++;
    }

    // Get size of queue
    int size()
    {
      return m_size;
    }
    
  private:
     struct Node<T>* m_head = nullptr;
     struct Node<T>* m_tail = nullptr;
  
    int m_size = 0;
};

#endif // queue_h
