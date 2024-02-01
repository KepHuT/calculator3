#include <iostream>
#include <stack>

using namespace std;
struct Leksema
{
    char type;
    double value;
};

bool Maths(stack < Leksema >& stack_number, stack < Leksema >& stack_operations, Leksema& item)
{
    double a, b, c;
    a = stack_number.top().value;
    stack_number.pop();
    switch (stack_operations.top().type)
    {
    case '+':
        b = stack_number.top().value;
        stack_number.pop();
        c = a + b;
        item.type = '0';
        item.value = c;
        stack_number.push(item);
        stack_operations.pop();
        break;
    case '-':
        b = stack_number.top().value;
        stack_number.pop();
        c = b - a;
        item.type = '0';
        item.value = c;
        stack_number.push(item);
        stack_operations.pop();
        break;
    case '*':
        b = stack_number.top().value;
        stack_number.pop();
        c = a * b;
        item.type = '0';
        item.value = c;
        stack_number.push(item);
        stack_operations.pop();
        break;
    case '/':
        b = stack_number.top().value;
        if (a == 0)
        {
            cerr << "На 0 делить нельзя!\n";
            return false;
        }
        else
        {
            stack_number.pop();
            c = b / a;
            item.type = '0';
            item.value = c;
            stack_number.push(item);
            stack_operations.pop();
            break;
        }
    default:
        cerr << "На 0 делить нельзя!\n";
        return false;
        break;
    }
    return true;
};

int Rang(char primer)
{
    if (primer == '+' || primer == '-')
        return 1;
    if (primer == '*' || primer == '/')
        return 2;
    return 0;

};

int main()
{
    setlocale(LC_ALL, "rus");

    char primer;
    double value;
    bool flag = 1;
    stack < Leksema > stack_number;
    stack < Leksema > stack_operations;
    Leksema item;
    while (1)
    {
        primer = cin.peek();
        if (primer == '\n')
            break;
        if (primer >= '0' && primer <= '9' || primer == '-' && flag == 1)
        {
            cin >> value;
            item.type = '0';
            item.value = value;
            stack_number.push(item);
            flag = 0;
            continue;
        }
        if (primer == '+' || primer == '-' && flag == 0 || primer == '*' || primer == '/')
        {
            if (stack_operations.size() == 0)
            {
                item.type = primer;
                item.value = 0;
                stack_operations.push(item);
                cin.ignore();
                continue;
            }
            if (stack_operations.size() != 0 && Rang(primer) > Rang(stack_operations.top().type))
            {
                item.type = primer;
                item.value = 0;
                stack_operations.push(item);
                cin.ignore();
                continue;
            }
            if (stack_operations.size() != 0 && Rang(primer) <= Rang(stack_operations.top().type))
            {
                if (Maths(stack_number, stack_operations, item) == false)
                {
                    system("pause");
                    return 0;
                }
                continue;
            }
        }
    }
    while (stack_operations.size() != 0)
    {
        if (Maths(stack_number, stack_operations, item) == false)
        {
            system("pause");
            return 0;
        }
        else
        {
            continue;
        }
    }
    cout << "Ответ: " << stack_number.top().value << endl;
    return 0;
}

