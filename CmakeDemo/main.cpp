#include <threadsafe_stack.h>

int main()
{
    threadsafe_stack<int> stack;
    stack.push(1);
    stack.push(2);
    stack.push(3);
    stack.push(4);
    stack.push(5);

    stack.tranverse();
}
