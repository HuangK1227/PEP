#ifndef STACK_H
#define STACK_H

#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>

#include <vector>
using std::vector;

// TODO: Your code goes here
class Stack{
    
    private:
        vector<double> stack; 
    public:
    
    Stack():
        stack()
    {}
    
    bool empty(){
       return stack.empty();
    }

    double pop(){
        double popedElement = stack.back();
        stack.pop_back();
        return popedElement;
    }

    void push(double pushedElement){
        stack.push_back(pushedElement);
    }
};
    
    double evaluate(std::string content){
        std::vector<std::string> result;
        std::istringstream iss(content);
        for(std::string content; iss >> content; ){
            result.push_back(content);
        }
        //split the string content
        
        Stack hyp;
        double a;
        double b;
        for(std::string & content: result){
            if(content == "+"){
                a = hyp.pop();
                b = hyp.pop();
                hyp.push(a+b);
            }
            else if (content == "-"){
                a = hyp.pop();
                b = hyp.pop();
                hyp.push(b-a);
            }
            else if(content == "*"){
                a = hyp.pop();
                b = hyp.pop();
                hyp.push(a*b);
            }
            else if(content == "/"){
                a = hyp.pop();
                b = hyp.pop();
                hyp.push(b/a);
            }
            else if(content != "+" || content != "-" || content != "*" || content != "/"){
                double number = std:: stod(content);
                hyp.push(number);
            }
        }
        return hyp.pop();
    }    


// Do not write anything below this line

#endif
