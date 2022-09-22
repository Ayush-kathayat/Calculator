#include <iostream>
#include <stack>
#include <string>
#include <vector>



std::string Remove_spaces(std::string input)
{
    std::string ans;
    for(const auto i : input)
    {
        if(i != ' ')
        {
            ans.push_back(i);
        }
    }
    return ans;
}

std::string Take_input()       
{
    std::string input;
    getline(std::cin , input);
    return input;
}


int Precendence(char prec)
{
    switch(prec)
    {
        case '+' : return 2;

        case '-' : return 2;

        case '*' : return 3;

        case '/' : return 4;

        case '^' : return 4;

        case '(' : return 0;

    }

    return -1;
}


std::string Infix_to_postfix(std::string infix)
{
    std::vector <char> str;

    std::stack <char> stack;

    for(int i = 0 ; i < infix.size() ; i++)
    {
        if((int)infix[i] >= 48 && (int)infix[i] <= 57 || (int)infix[i] == 46)      // it will show the operands only 
        {
            str.push_back(infix[i]) ;
        }
        
        if(infix[i] == '(')
        {
            stack.push(infix[i]);          // if you encounter the ( opening bracket just push in to the stack
        }
        
        
        if(infix[i] == ')')           // remove all the operand from the stack till the opening bracket
        {
            while(true)
            {
                if(stack.top() == '(') 
                {
                    stack.pop(); // at last pop the opening bracket from the stack
                    break;
                }
                str.push_back(stack.top()) ;
                stack.pop();
                
            }
            
             
        }
        
        // // now we will here enter the operand according to there precendence and all 
        
        
        if(infix[i] == '+' || infix[i] == '-' || infix[i] == '*' || infix[i] == '/' || infix[i] == '^') 
        {
            if(stack.empty())                     // first when stack is just push
            {
                stack.push(infix[i]);
                   
            }
            else if (Precendence(infix[i])<= Precendence(stack.top()))     
            {
                while (!stack.empty())                      // it will pop till the 
                {
                    str.push_back(stack.top());
                    stack.pop();
                    if(stack.empty())                   // double safety
                    {
                        break;
                    }
                    else if(Precendence(infix[i]) > Precendence(stack.top()))
                    {
                        break;
                    }

                }
                
                stack.push(infix[i]);     

            }
            else
            {
                stack.push(infix[i]);  // just push
            }
            
            
        }
    
        
    }
    
    while(!stack.empty())
    {
        str.push_back(stack.top());
        stack.pop();
    }

    std::string postfix(str.begin(),str.end());
    return postfix;

}

int main()
{
    std::string infix_str = Remove_spaces(Take_input());

    std::string postfix_str = Infix_to_postfix(infix_str);

    std::cout << "SO here is your postfix string : ";

    std::cout << postfix_str << std::endl;
}