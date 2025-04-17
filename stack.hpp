#ifndef STACK_HPP
#define STACK_HPP

using namespace cop4530;

template <typename T>
Stack<T>::Stack() : elements() {}

template <typename T>
Stack<T>::~Stack() {}

template <typename T>
std::vector<T> Stack<T>::getElements() const
{
    return elements;
}

template <typename T>
Stack<T>::Stack(const Stack<T>& other) : elements(other.elements) {} 

template <typename T>
Stack<T>::Stack(Stack<T>&&) : elements(std:: move(elements)) {} 

template <typename T>
Stack<T>& Stack<T>::operator=(const Stack<T> other)
{

    if (this != &other)
    {
        elements = other.elements;
    }
    return *this;
} 

template <typename T>
Stack<T>& Stack<T>::operator=(Stack<T> && other)
{
    if (this != &other)
    {
        elements = std::move(other.elements);
    }
    return *this;
}

template <typename T>
bool Stack<T>::empty() const
{    
// returns true if the Stack contains no elements, and false otherwise
    if (elements.size() == 0)
    {
        return true;
    }
    else 
    {
    return false;
    }
}

template <typename T>
void Stack<T>::clear()
{
    elements.clear();
}

template <typename T>
void Stack<T>::push(const T& x)
{
    elements.push_back(x);
}

template <typename T>
void Stack<T>::push(T && x)
{
    elements.push_back(std::move(x));
}

template <typename T>
void Stack<T>::pop()
{
    if (empty())
    {
        std::cout << "Stack is empty" << std::endl;
    }   
    elements.pop_back();
}

template <typename T>
T& Stack<T>::top()
{
    return elements.back();
}

template <typename T>
const T& Stack<T>::top() const
{
   return elements.back();
}

template <typename T>
int Stack<T>::size() const
{
    return elements.size();
} 

// non-member functions
template <typename T>
std::ostream& operator<<(std::ostream& os, const Stack<T>& a) {
    Stack<T> temp;
    Stack<T> copy = a;

    while (!copy.empty())
    {
        temp.push(copy.top());
        copy.pop();
    }
    while (!temp.empty())
    {
        os << temp.top();
        temp.pop();
        os << " ";
    }
    return os; // Return the output stream
}

template <typename T>
bool operator==(const Stack<T>& a, const Stack<T>& b) {
    if (a.size() != b.size()) {
        return false; 
    }
    const auto& aElements = a.getElements();
    const auto& bElements = b.getElements();

    for (int i = 0; i < a.size(); ++i) {
        if (aElements[i] != bElements[i]) {
            return false; // Elements differ
        }
    }
    return true; // Stacks are equal
}

template <typename T>
bool operator!=(const Stack<T>& a, const Stack<T>& b) {
    return !(a == b); 
}

template <typename T>
bool operator<=(const Stack<T>& a, const Stack<T>& b) {
    Stack<T> copyA = a; 
    Stack<T> copyB = b;

    while (!copyA.empty() && !copyB.empty()) {
        if (copyA.top() > copyB.top()) {
            return false;
        }
        copyA.pop(); // Remove the top element from A
        copyB.pop(); // Remove the top element from B
    }

    return true; 
}

#endif