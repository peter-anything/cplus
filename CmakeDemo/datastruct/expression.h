#ifndef CMAKEDEMO_EXPRESSION_H
#define CMAKEDEMO_EXPRESSION_H

#include<string>
#include<algorithm>
#include<vector>
#include<stack>

class Expression
{
private:
    std::vector<char> OPERATOR_LIST = { '+', '-', '*', '/', '(', ')' };

    bool is_operator(char ch)
    {
        return find(OPERATOR_LIST.begin(), OPERATOR_LIST.end(), ch) != OPERATOR_LIST.end();
    }

    int priority(char ch)
    {
        if (ch == '+')
        {
            return 0;
        }
        else if (ch == '-')
        {
            return 0;
        }
        else if (ch == '*')
        {
            return 1;
        }
        else if (ch == '/')
        {
            return 1;
        }
    }

    bool is_number(char ch)
    {
        return ch >= '0' && ch <= '9';
    }

    std::string try_read_number(const char * p)
    {
        std::string result;
        while (is_number(*p))
        {
            result += *p;
            ++p;
        }

        return result;
    }

public:
    // 10 + 1 * 25 + (1 * 45 + 8 + 10 / 5)*7
    std::string mid_to_after(std::string mid_exp)
    {
        int i = 0;
        std::string result;
        std::string num_str;
        std::stack<char> operator_stack;

        while (i < mid_exp.size())
        {
            if (is_number(mid_exp[i]))
            {
                num_str += mid_exp[i];
            }
            else
            {
                if (!num_str.empty())
                {
                    result += num_str;
                    num_str.clear();
                }

                if (is_operator(mid_exp[i]))
                {
                    if (operator_stack.empty())
                    {
                        operator_stack.push(mid_exp[i]);
                    }
                    else
                    {
                        char top = operator_stack.top();
                        if (priority(mid_exp[i]) == '(')
                        {
                            operator_stack.push(mid_exp[i]);
                        }
                        else if (priority(mid_exp[i]) == ')')
                        {
                            while (!operator_stack.empty() && operator_stack.top() != '(')
                            {
                                result += operator_stack.top();
                                operator_stack.pop();
                            }

                            if (!operator_stack.empty())
                            {
                                operator_stack.pop();
                            }
                        }
                        else if (priority(mid_exp[i]) > priority(top))
                        {
                            operator_stack.push(mid_exp[i]);
                        }
                        else
                        {
                            while (!operator_stack.empty() && operator_stack.top() != '(' && priority(operator_stack.top()) >= priority(mid_exp[i]))
                            {
                                result += operator_stack.top();
                                operator_stack.pop();
                            }

                            operator_stack.push(mid_exp[i]);
                        }
                    }
                }
            }
            ++i;
        }

        if (!num_str.empty())
        {
            result += num_str;
        }

        while (!operator_stack.empty())
        {
            result += operator_stack.top();
            operator_stack.pop();
        }

        return result;
    }
};

#endif