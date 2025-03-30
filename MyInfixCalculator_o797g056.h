#ifndef __MYINFIXCALCULATOR_H__
#define __MYINFIXCALCULATOR_H__

#include <iostream>
#include <algorithm>
#include <string>

#include "MyStack_o797g056.h"
#include "MyVector_o797g056.h"

class MyInfixCalculator{

  public:
    
    MyInfixCalculator()
    {

    }

    ~MyInfixCalculator()
    {
     
    }

    double calculate(const std::string& s) {
    
    
    MyVector<std::string> inf_tokens;
    MyVector<std::string> post_tokens;
    
   
    tokenize(s, inf_tokens);
    
   
    infixToPostfix(inf_tokens, post_tokens);
    
    
    double final_result = calPostfix(post_tokens);
    
    
    return final_result;
}

  private:

    // returns operator precedance; the smaller the number the higher precedence
    // returns -1 if the operator is invalid
    // does not consider parenthesis
    int operatorPrec(const char c) const
    {
        switch(c)
        {
            case '*':
                return 2;
            case '/':
                return 2;
            case '+':
                return 3;
            case '-':
                return 3;
            default:
                return -1;
        }
    }

    // checks if a character corresponds to a valid parenthesis
    bool isValidParenthesis(const char c) const
    {
        switch(c)
        {
            case '(':
                return true;
            case ')':
                return true;
            default:
                return false;
        }
    }

    // checks if a character corresponds to a valid digit
    bool isDigit(const char c) const
    {
        if(c >= '0' && c <= '9')
            return true;
        return false;
    }

    // computes binary operation given the two operands and the operator in their string form
    double computeBinaryOperation(const std::string& ornd1, const std::string& ornd2, const std::string& opt) const
    {
        double o1 = std::stod(ornd1);
        double o2 = std::stod(ornd2);
        switch(opt[0])
        {
            case '+':
                return o1 + o2;
            case '-':
                return o1 - o2;
            case '*':
                return o1 * o2;
            case '/':
                return o1 / o2;
            default:
                std::cout << "Error: unrecognized operator: " << opt << std::endl;
                return 0.0;
        }
    }


    void tokenize(const std::string& s, MyVector<std::string>& tokens)
{
    std::string token;

    for (size_t i = 0; i < s.length(); ++i) {
        if (isDigit(s[i]) || (s[i] == '.' && i + 1 < s.length() && isDigit(s[i + 1]))) {
            token += s[i];

            while (i + 1 < s.length() && (isDigit(s[i + 1]) || s[i + 1] == '.')) {
                token += s[++i];
            }

            tokens.push_back(token);
            token.clear();
        } 
        else if (s[i] == '-' && i + 1 < s.length() && s[i + 1] == '-') {
            // Handle double negatives as addition
            tokens.push_back("+");
            ++i;  // Skip the second '-'
        }
        else if (s[i] == '+' && i + 1 < s.length() && s[i + 1] == '-') {
            // Handle plus followed by minus as a single minus
            tokens.push_back("-");
            ++i;  // Skip the minus
        }
        else {
            tokens.push_back(std::string(1, s[i]));
        }
    }
}


    // converts a set of infix tokens to a set of postfix tokens
    void infixToPostfix(MyVector<std::string>& infix_tokens, MyVector<std::string>& postfix_tokens) {
   
    MyStack<std::string> stack;

    for (size_t i = 0; i < infix_tokens.size(); ++i) {
        const std::string& token = infix_tokens[i];
        

        if (isValidParenthesis(token[0])) {
           
            if (token == "(") {
            
                stack.push(token);
            } else {
 
                while (!stack.empty() && stack.top() != "(") {
                  
                    postfix_tokens.push_back(stack.top());
                    stack.pop();
                }

                if (!stack.empty()) {
                  
                    stack.pop();  
                } 
            }
        } 
        else if (operatorPrec(token[0]) != -1) {
          
            while (!stack.empty() && stack.top() != "(" && operatorPrec(stack.top()[0]) <= operatorPrec(token[0])) {
        
                postfix_tokens.push_back(stack.top());
                stack.pop();
            }
       
            stack.push(token);
        } 
        else {
    
            postfix_tokens.push_back(token);
        }
    
    }

   
    // Pop remaining operators
    while (!stack.empty()) {
        postfix_tokens.push_back(stack.top());
        stack.pop();
    }
    

}
    // calculates the final result from postfix tokens
    double calPostfix(const MyVector<std::string>& postfix_tokens) const {
    MyStack<std::string> stack;

    for (size_t i = 0; i < postfix_tokens.size(); ++i) {
        const std::string& token = postfix_tokens[i];

        if (operatorPrec(token[0]) != -1) {
            

            // Pop operands (in correct order)
            std::string secondnum = stack.top();
            stack.pop();
    

            std::string firstnum = stack.top();
            stack.pop();
           

            double result = computeBinaryOperation(firstnum, secondnum, token);
           
            
            stack.push(std::to_string(result));
        
        } 
        else {
            // It's an operand
           
            stack.push(token);
        }
        
    }

    double final_result = std::stod(stack.top());
    return final_result;
}
};

#endif // __MYINFIXCALCULATOR_H__