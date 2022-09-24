#include <iostream>
#include <stack>
#include <string>
#include <vector>
#include <cmath>



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


int Set_Precendence(char prec)
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
            else if (Set_Precendence(infix[i])<= Set_Precendence(stack.top()))     
            {
                while (!stack.empty())                      // it will pop till the 
                {
                    str.push_back(stack.top());
                    stack.pop();
                    if(stack.empty())                   // double safety
                    {
                        break;
                    }
                    else if(Set_Precendence(infix[i]) > Set_Precendence(stack.top()))
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


std::vector <std::string> Handling_digits_floats(std::string infix)    
{
    std::vector<std::string> str;

    std::string temp;
    bool init = false;
    
    for(int i = 0 ; i < infix.length(); )
    {
        if((int)infix[i] >= 48 && (int)infix[i] <= 57)
        {
            temp += infix[i];
        }
        else if(infix[i] == '.')
        {
            init = true;
            temp += infix[i];
        }
        else
        {
            if (infix[i] == '(' || infix[i] == ')' )
            {
                i++;
                continue;
            }
            
            if(init)
            {
                //stof the string cuz its having a . and clear the temp;
                // std::cout << temp << std::endl;
                str.push_back(temp);
                temp.clear();
            }
            else
            {
                // stoi the string cuz its not having the . and clear the temp
                // std::cout << temp << std::endl;
                str.push_back(temp);
                temp.clear();
            }
        
            
            init = false;
        }
        
        if(i == infix.length() -1)
        {
            // std::cout << temp << std::endl;
            str.push_back(temp);
            temp.clear();
        }
        i++;
        
    }


    return str;
}


std::string Postfix_Evaluation(std::string postfix, std::string infix )
{
    
   

    std::vector <std::string> str_vector = Handling_digits_floats(infix); // our vector with digits and double values
    
    
    std::stack <std::string> stack;
    
    for(int i = 0 ; i < str_vector.size(); i++)
    {
        std::cout <<str_vector[i].size() <<" size of = " << str_vector[i] <<std::endl;
    }
    
    int cnt = 0 ;
    for(int i = 0 ; i < postfix.size(); )
    {
        if((int)postfix[i] >= 48 && (int)postfix[i] <= 57 )
        {
            i = i + str_vector[cnt].size();
            stack.push(str_vector[cnt++]);                  // just push
            // std::cout << str_vector[cnt++] << std::endl;
        }
        else
        {
            // std::cout << postfix[i] << std::endl;
            
            double a , b , c;
            switch(postfix[i])
            {
                case '+':
                b = std::stod(stack.top());
                stack.pop();
                a = std::stod(stack.top());
                stack.pop();
                c = a + b;
                stack.push(std::to_string(c));
                // std::cout << "its plus" << std::endl;
                break;
                
                case '-':
                b = std::stod(stack.top());
                stack.pop();
                a = std::stod(stack.top());
                stack.pop();
                c = a - b;
                stack.push(std::to_string(c));
                // std::cout << "its sub" << std::endl;
                break;
                
                
                case '*':
                b = std::stod(stack.top());
                stack.pop();
                a = std::stod(stack.top());
                stack.pop();
                c = a * b;
                stack.push(std::to_string(c));
                // std::cout << "its multi" << std::endl;
                break;
                
                
                case '/':
                b = std::stod(stack.top());
                stack.pop();
                if(b == 0 )
                {
                    std::cout << "Can't divide by zero " << std::endl;
                    return 0;
                }
                a = std::stod(stack.top());
                stack.pop();
                c = a / b;
                stack.push(std::to_string(c));
                // std::cout << "its divide" << std::endl;
                break;
                
                
                case '^':
                b = std::stod(stack.top());
                stack.pop();
                a = std::stod(stack.top());
                stack.pop();
                c = std::pow(a , b);
                stack.push(std::to_string(c));
                // std::cout << "its power" << std::endl;
                break;
                
                
            };
            
            i++;
           
        }
    }
    
    return stack.top();
}

int main()
{
    std::string infix_str = Remove_spaces(Take_input());
    std::cout << "SO here is your infix string : ";
    std::cout << infix_str << std::endl;

    std::string postfix_str = Infix_to_postfix(infix_str);

    std::cout << "SO here is your postfix string : ";

    std::cout << postfix_str << std::endl;                  // now i have this postfix expression we have to evaluate it 

    std::string Total_ans =  Postfix_Evaluation(postfix_str,infix_str);

    std::cout << "Your answer is : " << Total_ans << std::endl;
    
    return 0 ;
}





