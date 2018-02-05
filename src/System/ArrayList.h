#pragma once

//Esta estructura de datos esta diseñada para ser una lista enlazada
//con las propiedades de incercion, y mas que nada insertar como pila



template <class T>
class Node
{
public:

	Node() 
	{ 
		NodeID = 0;//Node ID = 0 is an error(empty)
	};
	~Node() {};

    //	char NodeName[24]; 
	T NodeData;
	Node * NextNode;
	Node * PrevNode;
	unsigned int NodeID;
};


template <class T>
class ArrayList
{
public:

	ArrayList();
	~ArrayList();

	//Insertion methods

	void Push( T DataIn);


	void InserInto( unsigned int ID);
	void Insert(unsigned int INDEX);

	//Deletion metthods
	void Delete(unsigned int ID);
	void Remove(unsigned int INDEX);
	void Pop();



	void Free();


	//Utility functions and methods
	unsigned int GetSize();
	bool IsEmpty();
 	Node<T> & operator[] (const unsigned int index);

private:
	unsigned int m_size;

	Node<T>  * Begin;
	Node<T>  * Aux;
};



template<class T>
inline ArrayList<T>::ArrayList()
{


}

template<class T>
inline ArrayList<T>::~ArrayList()
{


}

template<class T>
inline void ArrayList<T>::Push(T DataIn)
{

}

template<class T>
inline void ArrayList<T>::InserInto(unsigned int ID)
{
}

template<class T>
inline void ArrayList<T>::Insert(unsigned int INDEX)
{

}

template<class T>
inline void ArrayList<T>::Delete(unsigned int ID)
{
}

template<class T>
inline void ArrayList<T>::Remove(unsigned int INDEX)
{
}

template<class T>
inline void ArrayList<T>::Pop()
{
}

template<class T>
inline void ArrayList<T>::Free()
{

}

template<class T>
inline unsigned int ArrayList<T>::GetSize()
{
	return 0;
}

template<class T>
inline bool ArrayList<T>::IsEmpty()
{
	return false;
}

template<class T>
inline Node<T>& ArrayList<T>::operator[](const unsigned int index)
{
	// TODO: insertar una instrucción return aquí
}
