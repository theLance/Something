#ifndef SINGLETON_HPP_INCLUDED
#define SINGLETON_HPP_INCLUDED


template<typename T> class Singleton
{
  public:
    static T* getinstance();
    virtual ~Singleton() { if( m_data ) delete m_data; }
  private:
    Singleton();
    Singleton<T>( const Singleton<T>& );
    Singleton<T>& operator=( const Singleton<T>& );
    static T* m_data;
};

template< typename T > T* Singleton<T>::m_data = NULL;

template< typename T > T* Singleton<T>::getinstance()
{
  if( !m_data )
  {
    m_data = new T;
  }
  return m_data;
}


#endif // SINGLETON_HPP_INCLUDED
